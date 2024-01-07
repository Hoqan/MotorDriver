#pragma once

#include "../mcu/gd32/gd32f4xx.h"
#include "bsp/basetype.h"

#define SYSTICK_HANDER sys_tick_handle

template <typename T>
class SysTimer {
  public:
    SysTimer();

    void init();

    /**
     * max time=999us
     */
    static inline T micros()
    {
        return TIMER_CNT(TIMER1);
    }

    /**
     * max time=65535ms
     */
    static inline T millis()
    {
        return TIMER_CNT(TIMER0);
    }

    /**
     * @param[in] ms delay time  should under 65536ms
     */
    static void delayMs(uint32 ms);

    /**
     * @param[in] us delay time  should under 65536us
     */
    static void delayUs(uint32 us);

  private:
    static const T max_cnt_;

  private:
    static inline T deltaTime(T t1, T t2)
    {
        return (t2 >= t1) ? (t2 - t1) : (t2 - t1 + max_cnt_);
    }
};

#include "sys_timer.tpp"
