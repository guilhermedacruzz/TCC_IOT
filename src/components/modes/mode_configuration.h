#ifndef _MODE_CONFIGURATION_
#define _MODE_CONFIGURATION_

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "mode_basic_sample.h"
#include "./models/settings.h"

extern NVS nvs;

AsyncWebServer server(80);
bool status = false;

class ModeConfiguration : public ModeBasicSample
{

private:
    const char *assid = "Teste12345";
    const char *asecret = "12345678";
    Settings settings;

public:
    ModeConfiguration()
    {
        Serial.println("Iniciando modo de configuração!");
        WiFi.mode(WIFI_MODE_AP); // Modifica o modo do WiFi para Access Point

        Serial.println("Criando ponto de acesso....");
        WiFi.softAP(this->assid, this->asecret);

        // Inicializa o server que recebe das configurações
        server.on(
            "/hello",
            HTTP_POST,
            [](AsyncWebServerRequest *request) {},
            NULL,
            [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
            {
                size_t i;
                char mensage[len];

                for (i = 0; i < len; i++)
                {
                    mensage[i] = data[i];
                }
                mensage[i] = '\0';

                Serial.println(mensage);

                status = true;
                request->send(200, "text/plain", "Ok!");
            });

        Serial.print("Iniciando server no ip: ");
        Serial.println(WiFi.softAPIP());

        server.begin();
    }

    void loop()
    {
        if(status) {

        }
    }
};

#endif