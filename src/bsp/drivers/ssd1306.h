#ifndef SSD1306_H
#define SSD1306_H

#include "../hal/iic.h"

class SSD1306 {
  public:
    static constexpr uint8_t DEVICE_ADDR = 0x78;
    static constexpr uint8_t WRITE_CMD   = 0x0;
    static constexpr uint8_t WRITE_DATA  = 0x40;

    static constexpr uint8_t MAX_COLUMN = 128;

    SSD1306();
    SSD1306(IIC<uint8_t>* iic);
    ~SSD1306() = default;

    void init();

    void oledClear();

    void showChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t height);

    void showString(uint8_t x, uint8_t y, const uint8_t* str, uint8_t height);

  private:
    IIC<uint8_t>* iic_;

    void writeCmd(uint8_t cmd);

    void writeData(uint8_t data);

    void setPos(uint8_t x, uint8_t y);
};

#endif  // SSD1306_H
