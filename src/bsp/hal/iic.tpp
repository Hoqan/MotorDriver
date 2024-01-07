#include "./iic.h"

template <typename T>
IIC<T>::IIC()
{
}

template <typename T>
IIC<T>::IIC(IICConfig cfg) : iic_cfg_(cfg)
{
}

template <typename T>
void IIC<T>::init()
{
    if (iic_cfg_.type == HARDWARE) {
        iic_cfg_.pins.clk->setup(PinCtrl::IIC, PinCtrl::AF, PinCtrl::NONE);
        iic_cfg_.pins.data->setup(PinCtrl::IIC, PinCtrl::AF, PinCtrl::NONE);
        /* enable I2C clock */
        rcu_periph_clock_enable(iic_cfg_.clk);
        /* configure I2C clock */
        i2c_clock_config(iic_cfg_.interface, iic_cfg_.speed, I2C_DTCY_2);
        /* configure I2C address */
        i2c_mode_addr_config(iic_cfg_.interface, I2C_I2CMODE_ENABLE,
                             I2C_ADDFORMAT_7BITS, iic_cfg_.dev_addr);
        /* enable I2CX */
        i2c_enable(iic_cfg_.interface);
        /* enable acknowledge */
        i2c_ack_config(iic_cfg_.interface, I2C_ACK_ENABLE);
    }
    else if (iic_cfg_.type == SOFT) {
        iic_cfg_.pins.clk->setup(PinCtrl::GPIO, PinCtrl::OUTPUT, PinCtrl::NONE);
        iic_cfg_.pins.data->setup(PinCtrl::GPIO, PinCtrl::OUTPUT,
                                  PinCtrl::NONE);
    }
}

template <typename T>
void IIC<T>::read(T data)
{
    startTrans(iic_cfg_.dev_addr, true);

    /* wait until the transmit data buffer is empty */
    while ((!i2c_flag_get(iic_cfg_.interface, I2C_FLAG_TBE)) &&
           (timeout_cnt_ < iic_cfg_.timeout)) {
        timeout_cnt_++;
    }
    // TODO:
    // i2c_data_transmit(iic_cfg_.interface, readaddr);
}

template <typename T>
void IIC<T>::read(uint8 addr, T& data)
{
    startTrans(iic_cfg_.dev_addr, true);

    /* wait until the transmit data buffer is empty */
    while ((!i2c_flag_get(iic_cfg_.interface, I2C_FLAG_TBE)) &&
           (timeout_cnt_ < iic_cfg_.timeout)) {
        timeout_cnt_++;
    }
    i2c_data_transmit(iic_cfg_.dev_addr, addr);

    stopTrans();
}

template <typename T>
void IIC<T>::write(T data)
{
    // uint8_t bytes = sizeof(T);

    // while (bytes--) {
    //     writeByte();
    // }
}

template <typename T>
uint8_t IIC<T>::writeByte(uint8_t byte)
{
    uint8_t i;
    uint8_t ack;

    if (iic_cfg_.type == SOFT) {
        for (i = 0; i < 8; i++) {
            if (byte & 0x80) {
                iic_cfg_.pins.data->DigitalOutput(1);
            }
            else {
                iic_cfg_.pins.data->DigitalOutput(0);
            }

            // DelayUs();
            iic_cfg_.pins.clk->DigitalOutput(1);
            Timer::delayUs(10);
            Timer::delayUs(10);
            Timer::delayUs(10);
            iic_cfg_.pins.clk->DigitalOutput(0);
            byte <<= 1;
        }

        iic_cfg_.pins.data->DigitalOutput(1);
        Timer::delayUs(10);
        iic_cfg_.pins.clk->DigitalOutput(1);
        Timer::delayUs(10);
        Timer::delayUs(10);
        iic_cfg_.pins.data->DigitalInput(&ack);
        iic_cfg_.pins.clk->DigitalOutput(0);
    }

    return ack;
}

template <typename T>
void IIC<T>::startTrans(uint8 dev_addr, bool send)
{
    uint32 dirc;

    if (iic_cfg_.type == SOFT) {
        iic_cfg_.pins.clk->DigitalOutput(1);
        iic_cfg_.pins.data->DigitalOutput(1);
        Timer::delayUs(10);
        iic_cfg_.pins.data->DigitalOutput(0);
        Timer::delayUs(10);
        iic_cfg_.pins.clk->DigitalOutput(0);
    }
    else {
        /* i2c master sends start signal only when the bus is idle */
        while (i2c_flag_get(iic_cfg_.interface, I2C_FLAG_I2CBSY) &&
               (timeout_cnt_ < iic_cfg_.timeout)) {
            // timeout++;
        }
        i2c_start_on_bus(iic_cfg_.interface);

        /* i2c master sends START signal successfully */
        while ((!i2c_flag_get(iic_cfg_.interface, I2C_FLAG_SBSEND)) &&
               (timeout_cnt_ < iic_cfg_.timeout)) {
            // timeout++;
        }
        dirc = (send) ? I2C_TRANSMITTER : I2C_RECEIVER;
        i2c_master_addressing(iic_cfg_.interface, dev_addr, dirc);

        /* address flag set means i2c slave sends ACK */
        while ((!i2c_flag_get(iic_cfg_.interface, I2C_FLAG_ADDSEND)) &&
               (timeout_cnt_ < iic_cfg_.timeout)) {
            // timeout++;
        }
        i2c_flag_clear(iic_cfg_.interface, I2C_FLAG_ADDSEND);
    }
}

template <typename T>
void IIC<T>::startTrans()
{
    if (iic_cfg_.type == SOFT) {
        iic_cfg_.pins.clk->DigitalOutput(1);
        iic_cfg_.pins.data->DigitalOutput(1);
        Timer::delayUs(10);
        iic_cfg_.pins.data->DigitalOutput(0);
        Timer::delayUs(10);
        iic_cfg_.pins.clk->DigitalOutput(0);
    }
}

template <typename T>
void IIC<T>::stopTrans()
{
    if (iic_cfg_.type == SOFT) {
        iic_cfg_.pins.data->DigitalOutput(0);
        Timer::delayUs(10);
        iic_cfg_.pins.clk->DigitalOutput(1);
        Timer::delayUs(10);
        iic_cfg_.pins.data->DigitalOutput(1);
    }
    else {
        i2c_stop_on_bus(iic_cfg_.interface);
    }
}
