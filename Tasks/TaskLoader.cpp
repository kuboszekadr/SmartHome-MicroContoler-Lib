#include "TaskLoader.h"

void TaskScheduler::loadConfig()
{
    logger.log("Loading tasks from config files...");

    for (uint8_t i = 0; i < Task::tasks_amount; i++)
    {
        Task *task = Task::tasks[i];
        task->loadConfig();
    }
    
}