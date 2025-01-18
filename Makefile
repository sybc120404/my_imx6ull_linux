CROSS_COMPILE 	?= arm-linux-gnueabihf-
CC 				:= $(CROSS_COMPILE)gcc
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump

LED_INCLUDE_DIR				:= LED_BSP/bsp/led/
IMX6ULL_LIB_INCLUDE_DIR		:= imx6ull_lib/inc/

LED := LED_BSP/led.bin

.PHONY: clean all led

all: $(LED)

led: $(LED)
	@echo "make led DONE"

$(LED) : imx6ull_lib/obj/ccm.o imx6ull_lib/obj/delay.o imx6ull_lib/obj/gpio.o imx6ull_lib/obj/iomux.o LED_BSP/obj/bsp_led.o LED_BSP/obj/start.o LED_BSP/obj/main.o
	$(LD) -TLED_BSP/imx6ull.lds -o LED_BSP/led.elf $^
	$(OBJCOPY) -O binary -S LED_BSP/led.elf $@
	$(OBJDUMP) -D LED_BSP/led.elf > LED_BSP/led.dis

LED_BSP/obj/bsp_led.o : LED_BSP/bsp/led/bsp_led.c
	$(CC) -O2 -Wall -nostdlib -I $(LED_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

LED_BSP/obj/start.o : LED_BSP/project/start.s
	$(CC) -O2 -Wall -nostdlib -c -o $@ $<

LED_BSP/obj/main.o : LED_BSP/project/main.c
	$(CC) -O2 -Wall -nostdlib -I $(LED_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/ccm.o : imx6ull_lib/src/ccm.c
	$(CC) -O2 -Wall -nostdlib -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/delay.o : imx6ull_lib/src/delay.c
	$(CC) -O2 -Wall -nostdlib -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/gpio.o : imx6ull_lib/src/gpio.c
	$(CC) -O2 -Wall -nostdlib -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/iomux.o : imx6ull_lib/src/iomux.c
	$(CC) -O2 -Wall -nostdlib -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

clean:
	rm -rf LED_BSP/led.bin LED_BSP/led.elf LED_BSP/led.dis imx6ull_lib/obj/*.o LED_BSP/obj/*.o LED_BSP/load.imx