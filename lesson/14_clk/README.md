# 主频和时钟配置实验

开发板默认时钟频率为396MHz，6U支持更高频率，性能更高

## 硬件原理

时钟来源：晶振
1. 32.768kHz晶振，提供给RTC时钟使用
2. 6U的T16和T17两个IO上接24MHz的晶振，再由此衍生出其他时钟

## I.MX6U系统时钟分析

6U从24MHz晶振生出7路PLL，PLL又生出PFD

### 七路PLL

- PLL1：ARM PLL，供给ARM内核
- PLL2：system PLL，固定22倍频528MHz。该路PLL分出PLL2_PFD0~3
- PLL3：USB1 PLL，固定480MHz，主要用于USB，分出PLL3_PFD0~3
- PLL4：AUDIO PLL，主要供给音频使用
- PLL5：VEDIO PLL，主要共给视频使用
- PLL6：ENET PLL，主要供网络外设使用
- PLL7：USB2 PLL，固定480MHz，给USB2 Phy使用，无PFD

### 各路PLL分出的PFD

### 时钟树

### 外设选择时钟

### 初始化时钟

大部分外设都是使用PLL1~PLL3，需要初始化相关时钟，一般按照时钟树配置

#### 系统主频配置

配置ARM频率，时钟树如下

![ARM_CLK](https://github.com/sybc120404/image4md/blob/main/ARM_CLK.png)

需要配置CACRR寄存器的ARM_PODF位，控制分频值，还有PLL1的值，得到最终ARM主频

CACRR寄存器的ARM_PODF位:

![CACRR_1](https://github.com/sybc120404/image4md/blob/main/CACRR_1.png)

![CACRR_2](https://github.com/sybc120404/image4md/blob/main/CACRR_2.png)

PLL1：看以下(18.5.1.5.1)原理图，PLL1=pll1_sw_clk，由CCSR寄存器的pll1_sw_clk_sel位，控制是pll1_main_clk(0)还是step_clk(1)，前者就是由PLL1而来

![CCSR](https://github.com/sybc120404/image4md/blob/main/CCSR.png)

![CCSR_PLL1](https://github.com/sybc120404/image4md/blob/main/CCSR_PLL1.png)

修改PLL1时，需要给6ULL一个临时的时钟，也就是step_clk。需要将pll1_sw_clk切换来源为step_clk

从上图看出，设置CCSR寄存器step_sel位为0，使用osc_clk作为step_clk来源，也就是晶振

![STEP_CLK](https://github.com/sybc120404/image4md/blob/main/STEP_CLK.png)

再看PLL1取值。由CCM_ANALOG_PLL_ARM寄存器的DIV_SELECT位决定，计算公式如下，Fref是晶振24M

![ARM_PLL](https://github.com/sybc120404/image4md/blob/main/ARM_PLL.png)

bit0-6

![DIV_SELECT](https://github.com/sybc120404/image4md/blob/main/DIV_SELECT.png)

我们要设置主频为528MHz，那么可以设置2分频，PLL1为1056Mhz，这里1056=24*DIV_SEL/2，DIV_SEL=88

设置完切换回PLL1

#### PLL2 PLL3

PLL2和PLL3固定频率，无需初始化

#### PFD初始化

PLL2和PLL3各分出四路PFD，需要初始化

PFD初始化比较简单，直接设置寄存器即可，PLL2对应CCM_ANALOG_PFD_528n，PLL3对应CCM_ANALOG_PFD_480n

公式如下：

![PFD](https://github.com/sybc120404/image4md/blob/main/PFD.png)

#### 其他外设时钟源配置

以下时钟源经常用到，需要初始化

- AHB_CLK_ROOT      132M
- PERCLK_CLK_ROOT   66M
- IPG_CLK_ROOT      66M