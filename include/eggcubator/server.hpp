#ifndef SERVER_HPP
#define SERVER_HPP

// #include "WString.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "eggcubator/core/heater.h"
#include "eggcubator/core/humidifier.h"
#include "eggcubator/incubation.h"

namespace eggcubator {

class Server {
   public:
    Server(Heater *heater, Humidifier *humidifier, IncubationRoutine *incubation);
    bool init(char *ssid, char *password, int port = 80);

    void handle_client();

   private:
    Heater *heater;
    Humidifier *humidifier;
    IncubationRoutine *incubation;
    WiFiServer server;

    unsigned long timeout = 10000;

    void api();
    void handle_request(WiFiClient client, const String &request);
    void handle_root();
};

}  // namespace eggcubator

#endif  // !SERVER_HPP
