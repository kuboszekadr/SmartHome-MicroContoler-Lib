#include "Config.h"

Config::Config(const char *name, const char *root)
{
    memcpy(_name, name, 15);
    memcpy(_root, root, 15);
}

config_status_t Config::load()
{
    char _file_path[32];
    file_path(_file_path);

    logger.logf("Loading: %s\n", _file_path);

    File config_file = SPIFFS.open(_file_path, FILE_READ);
    if (!config_file)
    {
        logger.logf("Config file %s.json does not exists!\n", _name);
        return CONFIG_FILE_ERROR;
    }

    DeserializationError err = deserializeJson(data, config_file);
    if (err)
    {
        logger.log("Serialization error...");
        return CONFIG_SERIALIZATION_ERROR;
    }

    logger.log("Config loaded sucesfully.");
    return CONFIG_LOADED;
}

config_status_t Config::save()
{
    char _file_path[32];
    file_path(_file_path);

    File config_file = SPIFFS.open(_file_path, FILE_WRITE);
    if (!config_file)
    {
        return CONFIG_FILE_ERROR;
    }

    serializeJson(data, config_file);
    return CONFIG_SAVED;
}

void Config::file_path(char *buff)
{
    sprintf(buff, "/%s/%s.json", _root, _name);
}
