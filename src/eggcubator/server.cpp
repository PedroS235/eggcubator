#include "eggcubator/server.hpp"

#include <ArduinoJson.h>

#include "Arduino.h"
#include "ArduinoJson.hpp"
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
    if (request.startsWith("GET /temperature")) {
        float temperature = heater->get_temp();
        float target = heater->get_target();
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";

        response += "{\"current_temperature\":";
        response += String(temperature);
        response += ",\"target_temperature\":";
        response += String(target);
        response += "}";
        client.print(response);

    } else if (request.startsWith("POST /temperature")) {
        // Read the body containing the JSON payload.
        String body = client.readStringUntil('\r');

        log_i("%s", body.c_str());

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body.c_str());
        if (error) {
            String response =
                "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n";
            response += "{\"error\":\"Invalid JSON\"}";
            client.print(response);
            return;
        }

        // Expecting a JSON like {"target": 30.0}
        float new_temp = doc["target"];
        heater->set_temp_target(new_temp);

        // Send a JSON response confirming the update.
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{\"status\":\"OK\"}";
        client.print(response);

    } else if (request.startsWith("GET /humidity")) {
        float humidity = humidifier->get_humidity();
        float target = humidifier->get_target();
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{\"current_humidity\":";
        response += String(humidity);
        response += ",\"target_humidity\":";
        response += String(target);
        response += "}";
        client.print(response);

    } else if (request.startsWith("POST /humidity")) {
        String body = client.readString();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);
        if (error) {
            String response =
                "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n";
            response += "{\"error\":\"Invalid JSON\"}";
            client.print(response);
            return;
        }
        float new_humd = doc["target"];
        humidifier->set_humidity_target(new_humd);
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{\"status\":\"OK\"}";
        client.print(response);

    } else if (request.startsWith("POST /incubation/start/")) {
        // Assuming the egg type id is passed in the URL after /incubation/start/
        int id = request.substring(20).toInt();
        incubation->start_incubation(EggFactory::createEggFromIdx(id));
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{\"status\":\"OK\"}";
        client.print(response);

    } else if (request.startsWith("POST /incubation/stop")) {
        incubation->stop_incubation();
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{\"status\":\"OK\"}";
        client.print(response);

    } else if (request.startsWith("GET /incubation")) {
        // For now, just sending an empty response; add your incubation details here.
        String response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n";
        response += "{}";
        client.print(response);

    } else {
        // clang-format off
        const char *html = "<!doctypehtml><html lang=\"en\"><meta charset=\"UTF-8\"><meta content=\"width=device-width,initial-scale=1\"name=\"viewport\"><title>Eggcubator Control Panel</title><link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css\"rel=\"stylesheet\"><script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script><script src=\"https://cdn.jsdelivr.net/npm/chartjs-adapter-date-fns\"></script><div class=\"container-fluid mt-4\"><div class=\"row\"><div class=\"col-lg-6\"><h3>Control Panel</h3><div class=\"mb-3\"><label class=\"form-label\"for=\"targetTemp\">Target Temperature (°C)</label> <input class=\"form-control\"id=\"targetTemp\"placeholder=\"Enter target temperature\"step=\"0.1\"type=\"number\"> <button class=\"btn btn-primary mt-2\"id=\"setTempBtn\">Set Temperature</button></div><div class=\"mb-3\"><label class=\"form-label\"for=\"eggType\">Egg Type</label> <select class=\"form-select\"id=\"eggType\"><option value=\"0\">Chicken<option value=\"1\">Quail<option value=\"2\">Duck<option value=\"3\">Turkey<option value=\"4\">Goose<option value=\"5\">Pigeon</select></div><div class=\"mb-3\"><button class=\"btn btn-success me-2\"id=\"startIncubation\">Start Incubation</button> <button class=\"btn btn-danger\"id=\"stopIncubation\">Stop Incubation</button></div></div><div class=\"col-lg-6\"><h3>Combined Chart</h3><canvas id=\"combinedChart\"></canvas></div></div></div><script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js\"></script><script>const ctx=document.getElementById(\"combinedChart\").getContext(\"2d\");const eggtype={chicken:0,quail:1,duck:2,turkey:3,goose:4,pigeon:5};const combinedChart=new Chart(ctx,{type:\"line\",data:{datasets:[{label:\"Current Temperature\",data:[],borderColor:\"rgba(255, 10, 10, 1)\",fill:false,yAxisID:\"y-temp\",parsing:{xAxisKey:\"time\",yAxisKey:\"value\"},pointRadius:0},{label:\"Target Temperature\",data:[],borderColor:\"rgba(255, 155, 155, 1)\",borderDash:[5,5],fill:false,yAxisID:\"y-temp\",parsing:{xAxisKey:\"time\",yAxisKey:\"value\"},pointRadius:0},{label:\"Current Humidity\",data:[],borderColor:\"rgba(10, 10, 255, 1)\",fill:false,yAxisID:\"y-humidity\",parsing:{xAxisKey:\"time\",yAxisKey:\"value\"},pointRadius:0},{label:\"Target Humidity\",data:[],borderColor:\"rgba(54, 162, 235, 1)\",borderDash:[5,5],fill:false,yAxisID:\"y-humidity\",parsing:{xAxisKey:\"time\",yAxisKey:\"value\"},pointRadius:0}]},options:{scales:{x:{type:\"time\",time:{unit:\"minute\",stepSize:2,displayFormats:{minute:\"h:mm\"}},title:{display:true,text:\"Time\"}},\"y-temp\":{type:\"linear\",position:\"left\",title:{display:true,text:\"Temperature (°C)\"}},\"y-humidity\":{type:\"linear\",position:\"right\",title:{display:true,text:\"Humidity (%)\"},grid:{drawOnChartArea:false}}}}});async function updateCombinedChart(){try{const[tempResponse,humidityResponse]=await Promise.all([fetch(\"/temperature\"),fetch(\"/humidity\")]);const tempData=await tempResponse.json();const humidityData=await humidityResponse.json();const now=new Date();combinedChart.data.datasets[0].data.push({time:now,value:tempData.current_temperature});combinedChart.data.datasets[1].data.push({time:now,value:tempData.target_temperature});combinedChart.data.datasets[2].data.push({time:now,value:humidityData.current_humidity});combinedChart.data.datasets[3].data.push({time:now,value:humidityData.target_humidity});combinedChart.update()}catch(error){console.error(\"Error updating chart:\",error)}}setInterval(updateCombinedChart,1000);document.getElementById(\"setTempBtn\").addEventListener(\"click\",async()=>{const target=parseFloat(document.getElementById(\"targetTemp\").value,);if(!isNaN(target)){const response=await fetch(\"/temperature\",{method:\"POST\",headers:{\"Content-Type\":\"application/json\"},body:JSON.stringify({target})});const result=await response.json();console.log(\"Set temperature result:\",result)}});document.getElementById(\"startIncubation\").addEventListener(\"click\",async()=>{const eggType=parseInt(document.getElementById(\"eggType\").value);const response=await fetch(\"/incubation/start\",{method:\"POST\",headers:{\"Content-Type\":\"application/json\"},body:JSON.stringify({egg_type:eggType})});const result=await response.json();console.log(\"Start incubation result:\",result)});document.getElementById(\"stopIncubation\").addEventListener(\"click\",async()=>{const response=await fetch(\"/incubation/stop\",{method:\"POST\",headers:{\"Content-Type\":\"application/json\"}});const result=await response.json();console.log(\"Stop incubation result:\",result)});</script>";
        // clang-format on

        client.print(html);
    }
}

}  // namespace eggcubator
