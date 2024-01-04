#include "stop_watch.h"

StopWatch::StopWatch() : s_time_(), is_runing_() {}

void StopWatch::init() {}

uint32 StopWatch::start()
{
    if (!is_runing_)
        s_time_ = SysTimer<uint16>::micros();
    return s_time_;
}

uint32 StopWatch::stop()
{
    is_runing_ = false;
    return SysTimer<uint16>::micros() - s_time_;
}
