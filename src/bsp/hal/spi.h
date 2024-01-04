#pragma once

#include "./iostream.h"
#include "./pinctrl.h"
#include "utils/common_utils.h"

template<typename T>
class Spi : IOstream<T> {
public:
    struct Pins {
        PinCtrl *miso;
        PinCtrl *mosi;
        PinCtrl *clk;
        PinCtrl *cs;
    };

    struct SpiConfig
    {
        Pins pins;
        uint32_t num;
        rcu_periph_enum clk;
        uint32_t dev_mode;
        uint32_t trans_mode;
        uint32_t frame_size;
        uint32_t cs;
        uint32_t endian;
        uint32_t clk_polarity_phase;
        uint32_t prescale;
    };

    Spi();
    Spi(const SpiConfig &spi_cfg);
    virtual ~Spi() = default;

    void init();

    void write(uint16_t *data, uint32_t size);
    
    void write(T data) override;

    void read(T data) override;

private:
    SpiConfig spi_cfg_;

    void initPins();
};
