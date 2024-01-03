#include "Relay.h"

std::map <const char*, Relay*> Relay::relays;

Relay::Relay(const char *name, int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH); // on ESP32 seems like HIGH=LOW on arduino...

    relays.insert(std::make_pair(name, this));
}

Relay::~Relay()
{
    for (auto it = relays.begin(); it != relays.end(); ++it)
    {
        if (it->second == this)
        {
            relays.erase(it);
            break;
        }
    }
}

void Relay::turnOn()
{
    logger.logf("Opening relay on pin %d", _pin);
    digitalWrite(_pin, LOW);
}

void Relay::turnOff()
{
    logger.logf("Closing relay on pin %d", _pin);
    digitalWrite(_pin, HIGH);
}

int Relay::getState()
{
    return digitalRead(_pin);
}