#ifndef Relay_h
#define Relay_h

#include "../Logger/Logger.h"

#include <Arduino.h>
#include <map>

class Relay
{
public:
  static std::map <const char*, Relay*> relays;
  Relay(const char *name, int pin);
  ~Relay();

  void turnOn();
  void turnOff();

  int getState();

private:
  Logger logger = Logger("relay");
  int _pin;
};

#endif