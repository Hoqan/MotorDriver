#pragma once

#include "bsp/basetype.h"
#include "utils/timers/sys_timer.h"

class StopWatch {
  public:
    StopWatch();
    virtual ~StopWatch() = default;

    void init();

    /**
     * start the stopwatch,get current sys time at start
     * @retrun current sys time at start
     */
    uint32 start();

    /**
     * stop the stopwatch,get current sys time at stop
     * @retrun current sys time at stop
     */
    uint32 stop();

  private:
    uint32 s_time_;  // start time
    bool   is_runing_;
};