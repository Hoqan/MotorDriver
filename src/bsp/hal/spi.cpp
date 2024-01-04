#include "spi.h"

template<typename T>
Spi<T>::Spi()
    : IOstream<T>() {

}

template<typename T>
Spi<T>::Spi(const SpiConfig &spi_config) 
    : IOstream<T>()
    , spi_cfg_(spi_config) {

}

template<typename T>
void Spi<T>::init() {
    spi_parameter_struct spi_init_struct;

    initPins();
    rcu_periph_clock_enable(spi_cfg_.clk);

    /* configure SPI1 parameter */
    spi_init_struct.trans_mode           = spi_cfg_.trans_mode;
    spi_init_struct.device_mode          = spi_cfg_.dev_mode;
    spi_init_struct.frame_size           = spi_cfg_.frame_size;
    spi_init_struct.clock_polarity_phase = spi_cfg_.clk_polarity_phase;
    spi_init_struct.nss                  = spi_cfg_.cs;
    spi_init_struct.prescale             = spi_cfg_.prescale;
    spi_init_struct.endian               = spi_cfg_.endian;
    spi_init(spi_cfg_.num, &spi_init_struct);
}

template<typename T>
void Spi<T>::write(uint16_t *data, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        while(RESET == spi_i2s_flag_get(SPI3, SPI_FLAG_TBE));
        spi_i2s_data_transmit(spi_cfg_.num, data[i]);
    }
}

template<typename T>
void Spi<T>::write(T data) {
    uint32_t size = array_len(data);

    for (uint32_t i = 0; i < size; i++) {
        while(RESET == spi_i2s_flag_get(SPI3, SPI_FLAG_TBE));
        spi_i2s_data_transmit(spi_cfg_.num, data[i]);
    }
}

template<typename T>
void Spi<T>::read(T data) {
    while(RESET == spi_i2s_flag_get(spi_cfg_.num, SPI_FLAG_RBNE));
//    spi3_receive_array[receive_n] = spi_i2s_data_receive(spi_cfg_.num);
}

template<typename T>
void Spi<T>::initPins() {
    spi_cfg_.pins.clk->setup(PinCtrl::SPI, PinCtrl::AF, PinCtrl::NONE);
    spi_cfg_.pins.miso->setup(PinCtrl::SPI, PinCtrl::AF, PinCtrl::NONE); 
    spi_cfg_.pins.mosi->setup(PinCtrl::SPI, PinCtrl::AF, PinCtrl::NONE);
    spi_cfg_.pins.cs->setup(PinCtrl::SPI, PinCtrl::AF, PinCtrl::NONE); 
}
