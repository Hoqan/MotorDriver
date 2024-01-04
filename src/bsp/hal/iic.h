#pragma once

#include "../basetype.h"
#include "./iostream.h"
#include "./pinctrl.h"
#include "sys_timer.h"

template <typename T>
class IIC : public IOstream<T> {
  public:
    using Timer = SysTimer<uint32_t>;
    enum Type { SOFT = 0, HARDWARE };

    struct Pins
    {
        const PinCtrl* clk;
        const PinCtrl* data;
    };

    struct IICConfig
    {
        Type            type;
        Pins            pins;
        uint32_t        interface;
        rcu_periph_enum clk;
        uint32_t        speed;
        uint32_t        dev_addr;
        uint32_t        timeout;
    };

    IIC();
    virtual ~IIC() = default;

    void init();

    void startTrans(uint8 dev_addr, bool send);

    void startTrans();

    void stopTrans();

    void read(T data) override;

    void read(uint8 addr, T& data);

    void write(T data) override;

    uint8_t writeByte(uint8_t byte);

  private:
    IICConfig iic_cfg_;
    uint32_t  timeout_cnt_;
};
