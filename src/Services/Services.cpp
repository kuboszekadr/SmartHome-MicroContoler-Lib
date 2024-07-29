#include "Services.h"

AsyncWebServer Services::server = AsyncWebServer(80);
std::vector<Services::IService*> Services::services = std::vector<Services::IService *>();

Services::IService::IService()
{
    services.push_back(this);
}

void Services::init()
{
    for(const auto& service : services)
    {
        service->create();
    }

    // for (const auto& socket: sockets)
    // {
    //     server.addHandler(socket);
    // }
    
}

void Services::serveHTMLFolder()
{

    File html_folder = SPIFFS.open("/html");
    if (!html_folder.isDirectory())
    {
        Serial.println("/html is not a directory");
        return;
    }

    File file = html_folder.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            file = html_folder.openNextFile();
            continue;
        }

        String file_name = file.name();
        file_name = file_name.substring(0, file_name.length() - 5);
        char url[32] = {};

        sprintf(url, "/%s", file_name);
        
        server.on(
            url, 
            HTTP_GET, 
            [file](AsyncWebServerRequest *request)
            {
                request->send(
                    SPIFFS, 
                    file.path(), 
                    "text/html");
            }
        );

        file = html_folder.openNextFile();

        }
}