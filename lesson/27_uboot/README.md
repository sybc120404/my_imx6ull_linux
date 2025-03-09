# UBOOT

## 什么是uboot

uboot是一个复杂的裸机程序，作用是启动Linux或其他系统

uboot最主要的工作是初始化DDR，Linux就是运行在DDR中

一般Linux镜像(zImage/uImage)+设备树(.dtb文件)存放在SD卡、EMMC、NAND、SPI Flash等外置区域。需要将Linux镜像拷贝到DDR中，才可以启动。这部分工作由uboot完成

uboot不仅可以启动linux，也可以启动其他系统。uboot支持多种架构

除了uboot，其他的bootloader也可以启动Linux

uboot获取：
1. uboot官方，缺点是支持比较少，对驱动支持不完善
2. SOC厂商定制uboot
3. 制作开发板的厂商定制uboot

## 正点原子官方uboot编译

编译uboot需要修改配置

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_ddr512_emmc_defconfig
make V=1 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j12
```