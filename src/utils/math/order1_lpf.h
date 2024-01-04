#pragma once

#include "filter.h"

template <typename T>
class Order1Lpf : public Filter<T> {
  public:
    Order1Lpf(const float& ts, const float& cutoff_freq);
    virtual ~Order1Lpf() = default;

    /**
     * order 1 low pass filter
     * @param[in] val the val needed to calculate
     * @return the result of calculation
     */
    T calc(const T& val) override;

  private:
    const float CUTOFF_FREQ_;
    const float TS_;
    T           last_val_;
    float       k;
    bool        calculated_;
};
