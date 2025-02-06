# key_filter

本章使用定时器进行按键消抖，如下，在[gpio中断](../17_gpio_interrupt/README.md)时，中断处理函数是按键按下后进行动作，按键需要消抖，暂时使用了delay，但实际上中断需要快进快出，不允许使用延时函数

```
static void gpio1_io18_irq_handler(unsigned int gicciar, void *param)
{
    static unsigned char state = 0;
    int pinState = 0;

    delay(10);  /* 实际上禁止中断服务函数中延时！！ */
    gpio_pinRead(GPIO1, 18, &pinState);
    if(0 == pinState)
    {
        state = !state;
        beep_switch(state);
    }

    /* 清除中断标志位 */
    gpio_clear_interrupt_flag(GPIO1, 18);

    return;
}
```

## 定时器按键消抖原理

1. 按键按下之后，进入中断服务函数，开启一个定时器，计时10ms
2. 只有最后一次抖动信号开启的定时器才能计时完，计时完毕时产生周期中断，在这个中断服务函数中执行对应操作

![debounce](https://github.com/sybc120404/image4md/blob/main/debounce.png)