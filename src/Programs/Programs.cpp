#include "Programs.h"

bool Programs::Program::isRunning()
{
    return _is_running;
}

void Programs::Program::deactivate()
{
    _is_active = false;
}

void Programs::Program::activate()
{
    _is_active = true;
}