#include "eggcubator/server.hpp"

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiServer.h"
#include "eggcubator/egg_factory.h"
#include "esp32-hal-log.h"
#include "esp32-hal.h"
#include "freertos/portmacro.h"

namespace eggcubator {

Server::Server(Heater *heater, Humidifier *humidifier, IncubationRoutine *incubation)
    : server(80) {
    this->heater = heater;
    this->humidifier = humidifier;
    this->incubation = incubation;
}

bool Server::init(char *ssid, char *password, int port) {
    server = WiFiServer(port);
    if (!_connect_wifi(ssid, password)) {
        log_e("Failed to connect to WiFi");
        return false;
    }

    server.begin();
    log_i("Connected to WiFi. IP = %s", WiFi.localIP().toString().c_str());
    log_i("Server is Up and Running");
    return true;
}

bool Server::_connect_wifi(char *ssid, char *password) {
    WiFi.begin(ssid, password);
    unsigned long wait_time = millis();
    bool success = true;

    while (!WiFi.isConnected()) {
        log_i("Trying to connect to WiFi...");

        if (millis() - wait_time >= timeout) {
            success = false;
            break;
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    if (!success) {
        return false;
    }

    return true;
}

void Server::handle_client() {
    WiFiClient client = server.available();

    if (!client) {
        return;
    }

    String request = client.readStringUntil('\r');
    log_i("Request: %s", request);
    client.flush();

    handle_request(client, request);
    client.stop();
}

void Server::handle_request(WiFiClient client, const String &request) {
    if (request.startsWith("GET /sensors/temperature")) {
        float temperature = heater->get_temp();
        String response =
            "HTTP/1.1 200 OK\r\nContent-Type: "
            "application/json\r\n\r\n{\"temperature\": \"" +
            String(temperature) + "\"}";
        client.print(response);

    } else if (request.startsWith("GET /sensors/humidity")) {
        float humidity = humidifier->get_humidity();
        String response =
            "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"humidity\": "
            "\"" +
            String(humidity) + "\"}";
        client.print(response);

    } else if (request.startsWith("GET /heater/target_temp")) {
        float target_temp = heater->get_target();
        String response =
            "HTTP/1.1 200 OK\r\nContent-Type: "
            "application/json\r\n\r\n{\"target_temp\": \"" +
            String(target_temp) + "\"}";
        client.print(response);

    } else if (request.startsWith("POST /heater/target_temp")) {
        log_i("Received target temp");
        String body = client.readString();
        float new_temp = body.toFloat();
        heater->set_temp_target(new_temp);
        String response = "HTTP/1.1 200 OK\r\n\r\n";
        client.print(response);

    } else if (request.startsWith("GET /humidifier/target_humd")) {
        float target_humd = humidifier->get_target();
        String response =
            "HTTP/1.1 200 OK\r\nContent-Type: "
            "application/json\r\n\r\n{\"target_humd\": \"" +
            String(target_humd) + "\"}";
        client.print(response);

    } else if (request.startsWith("POST /humidifier/target_humd")) {
        String body = client.readString();
        float new_humd = body.toFloat();
        humidifier->set_humidity_target(new_humd);
        String response = "HTTP/1.1 200 OK\r\n\r\n";
        client.print(response);

    } else if (request.startsWith("POST /incubation/start/")) {
        int id = request.substring(20).toInt();
        // Start incubation logic for the specific egg ID
        incubation->start_incubation(EggFactory::createEggFromIdx(id));
        String response = "HTTP/1.1 200 OK\r\n\r\n";
        client.print(response);

    } else if (request.startsWith("POST /incubation/stop")) {
        incubation->stop_incubation();
        String response = "HTTP/1.1 200 OK\r\n\r\n";
        client.print(response);

    } else if (request.startsWith("GET /incubation/stats")) {
        // String stats =
        //     incubation->get_stats();  // Assuming get_stats returns JSON-like string
        // String response =
        //     "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" + stats;
        String response = "HTTP/1.1 200 OK\r\n\r\n";
        client.print(response);

    } else {
        String html =
            "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta "
            "name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> "
            "<title>Eggcubator Interface</title> <style> body { font-family: Arial, "
            "sans-serif; margin: 20px; } h1 { text-align: center; } .container { "
            "width: 80%; margin: auto; } .chart-container { margin-bottom: 20px; } "
            ".control-group { margin-bottom: 20px; } .control-group label { display: "
            "block; margin-bottom: 5px; } .control-group input, .control-group select "
            "{ width: 100%; padding: 8px; margin-bottom: 10px; } button { padding: "
            "10px 20px; background-color: #007BFF; color: white; border: none; cursor: "
            "pointer; } button:hover { background-color: #0056b3; } "
            "</style></head><body> <h1>Eggcubator Control Panel</h1> <div "
            "class=\"container\"> <div class=\"chart-container\"> <h2>Temperature</h2> "
            "<canvas id=\"tempChart\" width=\"400\" height=\"200\"></canvas> <label "
            "for=\"setTemp\">Set Temperature (°C):</label> <input type=\"number\" "
            "id=\"setTemp\" step=\"0.1\"> <button onclick=\"setTemperature()\">Set "
            "Temperature</button> </div> <div class=\"chart-container\"> "
            "<h2>Humidity</h2> <canvas id=\"humdChart\" width=\"400\" "
            "height=\"200\"></canvas> <label for=\"setHumd\">Set Humidity (%):</label> "
            "<input type=\"number\" id=\"setHumd\" step=\"0.1\"> <button "
            "onclick=\"setHumidity()\">Set Humidity</button> </div> <div "
            "class=\"control-group\"> <h2>Incubation Control</h2> <label "
            "for=\"eggType\">Select Egg Type:</label> <select id=\"eggType\"> <option "
            "value=\"0\">Chicken</option> <option value=\"1\">Quail</option> <option "
            "value=\"2\">Duck</option> <option value=\"3\">Turkey</option> <option "
            "value=\"4\">Goose</option> <option value=\"5\">Pigeon</option> </select> "
            "<button onclick=\"startIncubation()\">Start Incubation</button> <button "
            "onclick=\"stopIncubation()\">Stop Incubation</button> </div> </div> "
            "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script> <script> "
            "const tempChartCtx = "
            "document.getElementById('tempChart').getContext('2d'); const humdChartCtx "
            "= document.getElementById('humdChart').getContext('2d'); // Temperature "
            "Chart const tempChart = new Chart(tempChartCtx, { type: 'line', data: { "
            "labels: [], // Time labels datasets: [{ label: 'Temperature (°C)', data: "
            "[], borderWidth: 1 }] } }); // Humidity Chart const humdChart = new "
            "Chart(humdChartCtx, { type: 'line', data: { labels: [], // Time labels "
            "datasets: [{ label: 'Humidity (%)', data: [], borderWidth: 1 }] } }); // "
            "API Interaction Functions async function setTemperature() { const temp = "
            "document.getElementById('setTemp').value; await "
            "fetch('/heater/target_temp', { method: 'POST', body: temp }); "
            "alert('Temperature set to ' + temp + '°C'); } async function "
            "setHumidity() { const humd = document.getElementById('setHumd').value; "
            "await fetch('/humidifier/target_humd', { method: 'POST', body: humd }); "
            "alert('Humidity set to ' + humd + '%'); } async function "
            "startIncubation() { const eggType = "
            "document.getElementById('eggType').value; await "
            "fetch(`/incubation/start/${eggType}`, { method: 'POST' }); "
            "alert('Incubation started for egg type: ' + eggType); } async function "
            "stopIncubation() { await fetch('/incubation/stop', { method: 'POST' }); "
            "alert('Incubation stopped'); } // Update Charts Periodically async "
            "function updateCharts() { const tempResponse = await "
            "fetch('/sensors/temperature'); const tempData = await "
            "tempResponse.json(); const humdResponse = await "
            "fetch('/sensors/humidity'); const humdData = await humdResponse.json(); "
            "const now = new Date().toLocaleTimeString(); "
            "tempChart.data.labels.push(now); "
            "tempChart.data.datasets[0].data.push(tempData.temperature); "
            "humdChart.data.labels.push(now); "
            "humdChart.data.datasets[0].data.push(humdData.humidity); "
            "tempChart.update(); humdChart.update(); setTimeout(updateCharts, 5000); } "
            "updateCharts(); // Start updating charts </script></body></html>";

        client.print(html);
    }
}

}  // namespace eggcubator
