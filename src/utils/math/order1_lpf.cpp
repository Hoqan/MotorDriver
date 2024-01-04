#include "order1_lpf.h"

template <typename T>
Order1Lpf<T>::Order1Lpf(const float& ts, const float& cutoff_freq)
    : Filter<T>(), TS_(ts), CUTOFF_FREQ_(cutoff_freq), calculated_()
{
    k = 1 - 1 / (1 + TS_ * CUTOFF_FREQ_);
}

template <typename T>
T Order1Lpf<T>::calc(const T& val)
{
    T ret;

    if (!calculated_) {
        calculated_      = true;
        return last_val_ = val;
    }

    ret       = (1 - k) * last_val_ + k * val;
    last_val_ = ret;
    return ret;
}
