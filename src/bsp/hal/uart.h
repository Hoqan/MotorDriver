#pragma once

#include "bsp/basetype.h"
#include "iostream.h"

struct UartCfg
{
    uint32 baudrate;
    uint32 interface;
    uint32 clock_src;
};

class Uart : IOstream {
  public:
    Uart();
    virtual ~Uart() = default;

    void read() override;

    void write() override;

    void init();

  private:
};
