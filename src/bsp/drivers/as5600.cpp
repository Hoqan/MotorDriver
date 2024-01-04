#include "./as5600.h"

AS5600::AS5600() {}

void AS5600::init() {}

int16 AS5600::getRawCount()
{
    uint16_t raw_count = 0;
    iic_->read(angle_reg_, raw_count);
    return raw_count;
}
