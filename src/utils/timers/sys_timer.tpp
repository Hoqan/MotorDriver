#include "sys_timer.h"
#include <limits>

template <typename T>
const T SysTimer<T>::max_cnt_ = std::numeric_limits<T>::max();

template <typename T>
SysTimer<T>::SysTimer()
{
    init();
}

template <typename T>
void SysTimer<T>::init()
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER0);
    rcu_periph_clock_enable(RCU_TIMER1);

    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER0);
    timer_deinit(TIMER1);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0, &timer_initpara);
    /* TIMER1 configuration */
    timer_initpara.prescaler         = 199;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);

    /* TIMER1 as a master */
    timer_master_slave_mode_config(TIMER1, TIMER_MASTER_SLAVE_MODE_ENABLE);
    timer_master_output_trigger_source_select(TIMER1, TIMER_TRI_OUT_SRC_UPDATE);

    /* TIMER0 as a slaver */
    timer_input_trigger_source_select(TIMER0, TIMER_SMCFG_TRGSEL_ITI1);
    timer_slave_mode_select(TIMER0, TIMER_SLAVE_MODE_EXTERNAL0);

    /* TIMER0 counter enable */
    timer_enable(TIMER0);
    /* TIMER1 counter enable */
    timer_enable(TIMER1);
}

template <typename T>
void SysTimer<T>::delayMs(uint32 ms)
{
    uint32 cur_ms = millis();

    while (deltaTime(cur_ms, millis()) < ms)
        ;
}

template <typename T>
void SysTimer<T>::delayUs(uint32 us)
{
    uint32 cur_us = micros();

    while (deltaTime(cur_us, micros()) < us)
        ;
}

// extern "C" {
// void SYSTICK_HANDER() {}
// }
