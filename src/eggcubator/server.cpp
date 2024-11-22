#include "eggcubator/server.hpp"

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiServer.h"
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
        log_e("Failed to connect to WiFi");

        return false;
    }

    log_i("Connected to WiFi. IP = %s", WiFi.localIP().toString().c_str());
    server.begin();
    log_i("Server is Running");
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
    if (request.indexOf("/start") != -1) {
        log_i("Starting incubation requested");
    } else if (request.indexOf("/stop") != -1) {
        log_i("Stoping incubation requested");
    }

    String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    html += "<!DOCTYPE HTML><html>";
    html += "<h1>EggCubator Web Interface</h1>";
    html += "<p><a href=\"/start\">Start Incubation</a></p>";
    html += "<p><a href=\"/stop\">Stop Incubation</a></p>";
    html += "</html>";

    // String response = generateHtml();
    client.print(html);
}

}  // namespace eggcubator
