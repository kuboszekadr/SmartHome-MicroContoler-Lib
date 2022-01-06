#ifndef TaskScheduler_Task_h
#define TaskScheduler_Task_h

#include "Config.h"

#include <Arduino.h>
#include <ESP32Time.h>
#include <Logger.h>

#define TASK_MAX_TASKS 5
#define TASK_NAME_LENGTH 20
#define TASK_JSON_SIZE 256

typedef void (*task)();

namespace TaskScheduler
{
    const char config_path[] PROGMEM = "tasks/%s.json";

    class Task : public ESP32Time
    {
    public:
        static Task *tasks[TASK_MAX_TASKS];
        static uint8_t tasks_amount;

        Task(const char *name, task fnc);
        void getName(char *buf);

        bool isExecutable();
        bool loadConfig();

        void forceExecute() { _fnc(); };
        void execute();

        void deactivate() { _is_active = false; }; // deactive whole task
        void activate() { _is_active = true; };    // active whole task

        void schedule(int day_of_week, uint16_t hour) { _schedule[day_of_week] = hour; }; // time execution
        void schedule(uint16_t hour); // time execution

    private:
        uint8_t _id;
        const char *_name; // name of the task
        void (*_fnc)();    // pointer to the function to be executed

        bool _is_active = true; // is task activate
        long _schedule[7];  // array of days with scheduled execution dates

        // when task was run last time
        long _last_run_date;
        long _last_run_time;
    };
} // namespace TaskScheduler

#endif