#pragma once

#include "./hal/pinctrl.h"
#include "./hal/iic.h"

const PinCtrl PA0(GPIOA, GPIO_PIN_0);
const PinCtrl PA1(GPIOA, GPIO_PIN_1);
const PinCtrl PA2(GPIOA, GPIO_PIN_2);
const PinCtrl PA3(GPIOA, GPIO_PIN_3);
const PinCtrl PA4(GPIOA, GPIO_PIN_4);
const PinCtrl PA5(GPIOA, GPIO_PIN_5);
const PinCtrl PA6(GPIOA, GPIO_PIN_6);
const PinCtrl PA7(GPIOA, GPIO_PIN_7);
const PinCtrl PA8(GPIOA, GPIO_PIN_8);
const PinCtrl PA9(GPIOA, GPIO_PIN_9);
const PinCtrl PA10(GPIOA, GPIO_PIN_10);
const PinCtrl PA11(GPIOA, GPIO_PIN_11);
const PinCtrl PA12(GPIOA, GPIO_PIN_12);
const PinCtrl PA13(GPIOA, GPIO_PIN_13);
const PinCtrl PA14(GPIOA, GPIO_PIN_14);
const PinCtrl PA15(GPIOA, GPIO_PIN_15);

const PinCtrl PB0(GPIOB, GPIO_PIN_0);
const PinCtrl PB1(GPIOB, GPIO_PIN_1);
const PinCtrl PB2(GPIOB, GPIO_PIN_2);
const PinCtrl PB3(GPIOB, GPIO_PIN_3);
const PinCtrl PB4(GPIOB, GPIO_PIN_4);
const PinCtrl PB5(GPIOB, GPIO_PIN_5);
const PinCtrl PB6(GPIOB, GPIO_PIN_6);
const PinCtrl PB7(GPIOB, GPIO_PIN_7);
const PinCtrl PB8(GPIOB, GPIO_PIN_8);
const PinCtrl PB9(GPIOB, GPIO_PIN_9);
const PinCtrl PB10(GPIOB, GPIO_PIN_10);
const PinCtrl PB11(GPIOB, GPIO_PIN_11);
const PinCtrl PB12(GPIOB, GPIO_PIN_12);
const PinCtrl PB13(GPIOB, GPIO_PIN_13);
const PinCtrl PB14(GPIOB, GPIO_PIN_14);
const PinCtrl PB15(GPIOB, GPIO_PIN_15);

const PinCtrl PC0(GPIOC, GPIO_PIN_0);
const PinCtrl PC1(GPIOC, GPIO_PIN_1);
const PinCtrl PC2(GPIOC, GPIO_PIN_2);
const PinCtrl PC3(GPIOC, GPIO_PIN_3);
const PinCtrl PC4(GPIOC, GPIO_PIN_4);
const PinCtrl PC5(GPIOC, GPIO_PIN_5);
const PinCtrl PC6(GPIOC, GPIO_PIN_6);
const PinCtrl PC7(GPIOC, GPIO_PIN_7);
const PinCtrl PC8(GPIOC, GPIO_PIN_8);
const PinCtrl PC9(GPIOC, GPIO_PIN_9);
const PinCtrl PC10(GPIOC, GPIO_PIN_10);
const PinCtrl PC11(GPIOC, GPIO_PIN_11);
const PinCtrl PC12(GPIOC, GPIO_PIN_12);
const PinCtrl PC13(GPIOC, GPIO_PIN_13);
const PinCtrl PC14(GPIOC, GPIO_PIN_14);
const PinCtrl PC15(GPIOC, GPIO_PIN_15);

const IIC<uint8_t>::IICConfig IIC1_CONFIG {
    .type = IIC<uint8_t>::Type::SOFT,
    .pins = {&PB0, &PB1},
    .interface = I2C1,
    .clk = RCU_I2C1,
    .speed = I2C_CKCFG_CLKC,
    .dev_addr = 0x3C
};
