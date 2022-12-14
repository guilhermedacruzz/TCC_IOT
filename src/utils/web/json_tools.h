#ifndef _JSON_TOOLS_
#define _JSON_TOOLS_

#include <typeinfo>
#include <ArduinoJson.h>
#include "./models/settings.h"

class JsonTools
{
public:
    JsonTools() {}

    Settings deserialize(String body)
    {
        DynamicJsonDocument doc(1024);

        deserializeJson(doc, body);

        JsonObject obj = doc.as<JsonObject>();

        return Settings(
            (obj["_id"].as<String>() != "null" ? obj["_id"] : String()),
            obj["name"],
            obj["description"],
            obj["user"],
            obj["timer"],
            obj["ssid"],
            obj["password"]);
    }

    String createYourselfInDatabase(Settings settings)
    {
        return "{\"name\":\"" + settings.name + "\","
                "\"description\":\"" + settings.description + "\","
                "\"user\":\"" +settings.user_id + "\","
                "\"timer\":" + settings.timer + ","
                "\"ssid\":\"" + settings.ssid + "\","
                "\"password\":\"" + settings.password + "\"}";
    }

    String createSendDataToApi(Settings settings, String motorStatus)
    {
        return "{\"iot\":\"" + settings.id + "\","
                                             "\"minutes\": 1,"
                                             "\"status\":\"" +
               motorStatus + "\"}";
    }
};

#endif