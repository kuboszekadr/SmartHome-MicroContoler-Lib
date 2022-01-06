#ifndef Config__h
#define Config__h

#define CONFIG_FILES_AMOUNT 5

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Logger.h>
#include <FS.h>
#include <SPIFFS.h>

typedef enum
{
    CONFIG_LOADED,
    CONFIG_FILE_ERROR,
    CONFIG_SERIALIZATION_ERROR,
    CONFIG_SAVED
} config_status_t;

class Config
{
public:
    Config(const char *name, const char *root="config");

    char *name(){return _name;};
    void file_path(char *buff);

    config_status_t load();
    config_status_t save();

    StaticJsonDocument<512> data;

protected:
    char _name[16];
    char _root[16];

    Logger logger = Logger("config");
};

#endif