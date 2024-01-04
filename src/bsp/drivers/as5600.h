#pragma once

#include "../hal/iic.h"

class AS5600 {
  public:
    AS5600();
    virtual ~AS5600() = default;

    void init();

    void getAngle();

    int16 getRawCount();

  private:
    IIC<uint16>* iic_;
    uint8       angle_reg_;
};
