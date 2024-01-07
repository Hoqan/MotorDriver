#pragma once

#include "../mcu/gd32/gd32f4xx.h"

class PinCtrl {
public:
    struct Pin {
        uint32_t port;
        uint32_t num;
    };

    PinCtrl();
    PinCtrl(Pin pin);
    PinCtrl(uint32_t port, uint32_t num);
    virtual ~PinCtrl() = default;

    enum Mux {
        GPIO = 0,
        UART,
        SPI,
        IIC,
        ADC,

    };

    enum InputMode {
        INPUT,
        OUTPUT,
        AF,
        ANALOG
    };

    enum PullOption {
        NONE,
        PULLUP,
        PULLDOWN
    };

    void initClk() const;
    void setMux(Mux mux) const;
    void setMode(InputMode inputmode, PullOption pullmode) const;
    void setup(Mux mux, InputMode inputmode, PullOption pullmode) const;
    void DigitalOutput(uint8_t level) const;
    void DigitalInput(uint8_t *level) const;
private:
    Pin pin_;

};

