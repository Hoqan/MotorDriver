#include "ssd1306.h"
#include "oledfont.h"

SSD1306::SSD1306() {}

void SSD1306::init()
{
    writeCmd(0xAE);  // display off
    writeCmd(0x20);  // Set Memory Addressing Mode
    writeCmd(0x10);  // 00,Horizontal Addressing Mode;01,Vertical Addressing
                     // Mode;10,Page Addressing Mode (RESET);11,Invalid
    writeCmd(0xb0);  // Set Page Start Address for Page Addressing Mode,0-7
    writeCmd(0xc8);  // Set COM Output Scan Direction
    writeCmd(0x00);  //---set low column address
    writeCmd(0x10);  //---set high column address
    writeCmd(0x40);  //--set start line address
    writeCmd(0x81);  //--set contrast control register
    writeCmd(0x7f);
    writeCmd(0xa1);  //--set segment re-map 0 to 127
    writeCmd(0xa6);  //--set normal display
    writeCmd(0xa8);  //--set multiplex ratio(1 to 64)
    writeCmd(0x3F);  //
    writeCmd(0xa4);  // 0xa4,Output follows RAM content;0xa5,Output ignores RAM
                     // content
    writeCmd(0xd3);  //-set display offset
    writeCmd(0x00);  //-not offset
    writeCmd(0xd5);  //--set display clock divide ratio/oscillator frequency
    writeCmd(0xf0);  //--set divide ratio
    writeCmd(0xd9);  //--set pre-charge period
    writeCmd(0x22);  //
    writeCmd(0xda);  //--set com pins hardware configuration
    writeCmd(0x12);
    writeCmd(0xdb);  //--set vcomh
    writeCmd(0x20);  // 0x20,0.77xVcc
    writeCmd(0x8d);  //--set DC-DC enable
    writeCmd(0x14);  //
    writeCmd(0xaf);  //--turn on oled panel
}

void SSD1306::oledClear()
{
    unsigned char i, n;

    for (i = 0; i < 8; i++) {
        writeCmd(0xb0 + i);
        writeCmd(0x00);
        writeCmd(0x10);

        for (n = 0; n < 128; n++) {
            writeData(0);
        }
    }
}

void SSD1306::writeCmd(uint8_t cmd)
{
    iic_->startTrans();

    iic_->writeByte(DEVICE_ADDR);
    iic_->writeByte(WRITE_CMD);
    iic_->writeByte(cmd);

    iic_->stopTrans();
}

void SSD1306::writeData(uint8_t data)
{
    iic_->startTrans();

    iic_->writeByte(DEVICE_ADDR);
    iic_->writeByte(WRITE_DATA);
    iic_->writeByte(data);

    iic_->stopTrans();
}

void SSD1306::setPos(uint8_t x, uint8_t y)
{
    writeCmd(0xb0 + y);
    writeCmd(((x & 0xf0) >> 4) | 0x10);
    writeCmd((x & 0x0f) | 0x01);
}

/**
 * ---------------> x axis
 *
 *
 * @param[in] x x axis positon
 * @param[in] y y axis position
 * @param[in] chr char will be shown
 * @param[in] height font height,height=8 or height=16
 *
 */
void SSD1306::showChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t height)
{
    uint8_t c = 0;
    uint8_t i = 0;

    c = chr - ' ';

    if (x > MAX_COLUMN - 1) {
        x = 0;
        y = y + 2;
    }
    if (height == 16) {
        setPos(x, y);
        for (i = 0; i < 8; i++) {
            writeData(F8X16[c * 16 + i]);
        }

        setPos(x, y + 1);
        for (i = 0; i < 8; i++) {
            writeData(F8X16[c * 16 + i + 8]);
        }
    }
    else {
        setPos(x, y + 1);
        for (i = 0; i < 6; i++)
            writeData(F6x8[c][i]);
    }
}

void SSD1306::showString(uint8_t        x,
                         uint8_t        y,
                         const uint8_t* str,
                         uint8_t        height)
{
    uint8_t i;

    for (i = 0; str[i] != '\0'; i++) {
        showChar(x, y, str[i], height);
        if (height == 16)
            x += 8;
        else
            x += 6;

        if (x > 120) {
            x = 0;
            y += 1;
        }
    }
}
