# BEEP

该例程为蜂鸣器实验

## 蜂鸣器硬件原理

如下为底板上BEEP的原理图，为PNP三极管，BEEP低电平时，电路导通，蜂鸣器响；反之不响

![BEEP](https://github.com/sybc120404/image4md/blob/main/BEEP.png)

再看BEEP在核心板上，使用SNVS_TAMPER1控制

![BEEP_CORE](https://github.com/sybc120404/image4md/blob/main/CORE_BEEP.png)

## 软件编写思路

1. 使能时钟信号
2. IO复用为GPIO
3. 设置GPIO属性，方向，值

查看参考手册，SNVS_TAMPER1可以复用为GPIO5_01

![SNVS_TAMPER1](https://github.com/sybc120404/image4md/blob/main/SVNS_TAMPER1.png)

剩余工作可以使用NXP的SDK接口完成，和LED很类似