#include "./pinctrl.h"

PinCtrl::PinCtrl() {

}

PinCtrl::PinCtrl(Pin pin)
    : pin_(pin) {
    
}

PinCtrl::PinCtrl(uint32_t port, uint32_t num) {
    pin_.port = port;
    pin_.num = num;
}

void PinCtrl::initClk() const {
    rcu_periph_enum gpio_clk;

    switch (pin_.num) {
        case GPIOA:
            gpio_clk = RCU_GPIOA;
            break;
        case GPIOB:
            gpio_clk = RCU_GPIOB;
            break;
        case GPIOC:
            gpio_clk = RCU_GPIOC;
            break;
        case GPIOD:
            gpio_clk = RCU_GPIOD;
            break;
        case GPIOE:
            gpio_clk = RCU_GPIOE;
            break;
        case GPIOF:
            gpio_clk = RCU_GPIOF;
            break;
        case GPIOG:
            gpio_clk = RCU_GPIOG;
            break;
        case GPIOH:
            gpio_clk = RCU_GPIOH;
            break;
        case GPIOI:
            gpio_clk = RCU_GPIOI;
            break;
        default:
            break;
    }
    rcu_periph_clock_enable(gpio_clk);
}

void PinCtrl::setMux(Mux mux) const {

    switch (mux) {
        case GPIO:
            break;
        case SPI:
            gpio_af_set(pin_.port, GPIO_AF_5, pin_.num);
            break;
        case IIC:
            gpio_af_set(pin_.port, GPIO_AF_5, pin_.num);
            break;
        case UART:
            gpio_af_set(pin_.port, GPIO_AF_5, pin_.num);
            break;
        case ADC:
            gpio_af_set(pin_.port, GPIO_AF_5, pin_.num);
            break;
        default:
            break;
    }
}

void PinCtrl::setMode(InputMode inputmode, PullOption pullmode) const {
    uint32_t in_m;
    uint32_t pull_m;

    switch (inputmode) {
        case INPUT:
            in_m = GPIO_MODE_INPUT;
            break;
        case OUTPUT:
            in_m = GPIO_MODE_OUTPUT;
            break;
        case AF:
            in_m = GPIO_MODE_AF;
            break;
        case ANALOG:
            in_m = GPIO_MODE_ANALOG;
            break;
    }

    switch (pullmode) {
        case NONE:
            pull_m  = NONE;
            break;
        case PULLUP:
            pull_m = GPIO_PUPD_PULLUP;
            break;
        case PULLDOWN:
            pull_m = GPIO_PUPD_PULLDOWN;
            break;
    }

    gpio_mode_set(pin_.port, in_m, pull_m, pin_.num);
    // gpio_output_options_set(pin_.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, pin_.num); 
}

void PinCtrl::setup(Mux mux, InputMode inputmode, PullOption pullmode) const {
    initClk();
    setMux(mux);
    setMode(inputmode, pullmode);
}

void PinCtrl::DigitalOutput(uint8_t level) const {
    bit_status bit_lev;

    bit_lev = (level == 1) ? SET : RESET;
    gpio_bit_write(pin_.port, pin_.num, bit_lev);
}

void PinCtrl::DigitalInput(uint8_t *level) const {
    bit_status bit_lev;
    
    bit_lev = gpio_input_bit_get(pin_.port, pin_.num);
    *level = bit_lev;
}
