#pragma once

#include "../hal/iostream.h"

class MA702 {
public:
    MA702();
    virtual ~MA702() = default;

    void init();


private:
    IOstream<char> *iostream;

};
