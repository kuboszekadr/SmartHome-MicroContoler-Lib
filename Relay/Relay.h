#ifndef Relay_h
#define Relay_h

#include <Arduino.h>
#include <Logger.h>
#include <map>

class Relay
{
public:
  static std::map <const char*, Relay*> relays;
  Relay(const char *name, int pin);

  void turnOn();
  void turnOff();

  int getState();

private:
  Logger logger = Logger("relay");
  int _pin;
};

#endif