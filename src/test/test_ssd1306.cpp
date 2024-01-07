#include "bsp/board_cfg.h"
#include "ssd1306.h"
#include "sys_timer.h"

IIC<uint8_t> iic_instance(IIC1_CONFIG);

class TestSSD1306 : public SysTimer<uint32> {
  public:
    TestSSD1306() : ssd1306_(&iic_instance) {}

    void init()
    {
        iic_instance.init();
        ssd1306_.init();
    }

  private:
    SSD1306 ssd1306_;
};

#if 1
int main()
{
    TestSSD1306 test_ssd1306;

    test_ssd1306.init();

    while (1) {}
}

#endif