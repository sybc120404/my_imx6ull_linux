# RTC

## RTC原理

6ULL内部自带RTC外设(SRTC)，内容在手册的SNVS章节

6U的RTC分为LP和HP，分别为低功耗和高功耗。LP是SRTC，HP是RTC，但HP的RTC掉电后数据丢失，即使有纽扣电池，所以必须使用SRTC

RTC很类似定时器，外接32.768kHZ晶振，然后开始计时，使用两个寄存器进行计时

RTC的使用：

1. 打开RTC，然后RTC就开始工作
2. 不断读取RTC计数寄存器，获取时间值，或者向RTC计数器写入时间值