#include "sys_timer.h"
#include <stdio.h>

class TestSysTimer : public SysTimer<uint32> {
  public:
    TestSysTimer() {}

    void init() {}

  private:
};

#if 0
int main()
{
    TestSysTimer test_systimer;

    SysTimer<uint32>::delayMs(5000);
    while (1) {}
}

#endif