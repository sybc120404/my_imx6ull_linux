#include "delay.h"
#include "beep.h"

int main(void)
{
    beep_init();

    while(1)
    {
        beep_on();
        delay(2500);
        beep_off();
        delay(2500);
    }

    return 0;
}