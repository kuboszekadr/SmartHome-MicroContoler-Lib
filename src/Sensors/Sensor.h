#ifndef Sensor_h
#define Sensor_h

#include "Events/EventType.h"
#include "Readings.h"

#include <Arduino.h>

#define SENSOR_AMOUNT 10 // maximum amount of sensors
#define SENSOR_NAME_LENGHT 20

namespace Sensors
{
    class Sensor
    {
    public:
        Sensor(std::vector<std::string> measures,
               const char *name,

               Events::EventType trigger_low,
               Events::EventType trigger_high);

        virtual float makeReading() = 0;           // to be overwriten by the subclasses
        virtual Events::EventType checkTrigger(float reading) = 0; // check if current level of sensor value is between low and high trigger

        bool isAvailable() { return _readings_amount >= _sampling_amount; };          // check if sensor gathered enough data
        bool isReady() { return (millis() - _last_reading) >= _sampling_interval; }; // check if sensor can gather data

        void getName(char *buffer);
        Readings getReadings() { return _readings; };

        void setTriggerValues(float low, float high);
        void setSampling(uint8_t amount, uint32_t interval);
        
        void restart();
    protected:
        const char *_name; // sensor name / label
        Readings _readings = Readings();

        uint8_t _sampling_amount = 1; // how many readings should be made
        uint8_t _readings_amount = 0;

        uint32_t _last_reading = 0L; // when last reading was done (as millis)
        uint32_t _sampling_interval = 0L; // how often sensor should make reading (in millis)

        float _trigger_value_low = -1.0; // average sensor value
        Events::EventType _trigger_low;  // event to be rised when sensor value is below low value

        float _trigger_value_high = -1.0; // +/- level when specify event should be published
        Events::EventType _trigger_high;  // event to be rised when sensor value is above value

        Events::EventType _last_trigger = Events::EventType::EMPTY;

    };                     // namespace Sensors

    extern uint8_t sensors_amount;         // how many sensors are initalized
    extern Sensor *sensors[SENSOR_AMOUNT]; // array of generated sensors

}

#endif