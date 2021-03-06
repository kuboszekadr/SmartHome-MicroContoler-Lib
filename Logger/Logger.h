#ifndef Logger__h
#define Logger__h

#include <ESP32Time.h>
#include <vector>

typedef void (*stream)(const char *module_name,
                       const char *log_level,
                       const char *msg,
                       const char *timestamp);

extern std::vector<stream> streams;
const char date_format[16] = "%F %T";

class Logger
{
public:
    Logger(const char *module_name);

    void log(const char *msg);
    void logf(const char *msg_format, ...);

    static void addStream(stream s);

private:
    char _log_level[32] = "INFO"; // placeholder
    char _module_name[32] = "";

    ESP32Time _time;

    void _stream(const char *module_name,
                 const char *log_level,
                 const char *msg,
                 const char *timestamp);
};

#endif