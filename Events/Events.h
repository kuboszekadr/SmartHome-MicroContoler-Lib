#ifndef Events_h
#define Events_h

#define EVENT_QUEUE_LENGTH 10

#include "Event.h"
#include "EventNames.h"
#include "EventType.h"

#include "../Logger/Logger.h"

#include <Arduino.h>

namespace Events
{
    void raise(EventType event);
    void notifyListeners();

    extern EventType queue[EVENT_QUEUE_LENGTH];
    extern int queue_length;
    extern Logger logger;

}; // namespace Events

#endif