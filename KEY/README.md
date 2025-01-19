# key

本工程为按键实验

# 实验原理

从底板原理图可以看出，使用KEY来控制按键，低电平时电路导通，高电平时电路不导通

![KEY](https://github.com/sybc120404/image4md/blob/main/KEY.png)

使用UART1_CTS引脚进行控制

![UART1_CTS](https://github.com/sybc120404/image4md/blob/main/UART1_CST.png)

该引脚可以复用为GPIO1_IO18

![GPIO1_IO18](https://github.com/sybc120404/image4md/blob/main/GPIO1_IO18.png)

