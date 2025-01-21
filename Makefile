CROSS_COMPILE 	?= arm-linux-gnueabihf-
CC 				:= $(CROSS_COMPILE)gcc
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump
CFLAGS 			:= -Wall -O2 -nostdlib

LED_INCLUDE_DIR				:= LED_BSP/bsp/led/
LED_SDK_INCLUDE_DIR			:= LED_SDK/bsp/led/
IMX6ULL_LIB_INCLUDE_DIR		:= imx6ull_lib/inc/

LED := LED_BSP/led.bin
LED_SDK := LED_SDK/led.bin
BEEP := BEEP/beep.bin
KEY := KEY/key.bin

.PHONY: clean all led led_sdk beep key

all: $(LED) $(LED_SDK) $(BEEP) $(KEY)

led: $(LED)
led_sdk: $(LED_SDK)
beep : $(BEEP)
key : $(KEY)

$(LED) : imx6ull_lib/obj/ccm.o imx6ull_lib/obj/delay.o imx6ull_lib/obj/gpio.o imx6ull_lib/obj/iomux.o LED_BSP/obj/bsp_led.o LED_BSP/obj/start.o LED_BSP/obj/main.o
	$(LD) -TLED_BSP/imx6ull.lds -z noexecstack -o LED_BSP/led.elf $^
	$(OBJCOPY) -O binary -S LED_BSP/led.elf $@
	$(OBJDUMP) -D LED_BSP/led.elf > LED_BSP/led.dis

$(LED_SDK) : imx6ull_lib/obj/delay.o LED_SDK/obj/led.o LED_SDK/obj/start.o LED_SDK/obj/main.o
	$(LD) -TLED_SDK/imx6ull.lds -z noexecstack -o LED_SDK/led.elf $^
	$(OBJCOPY) -O binary -S LED_SDK/led.elf $@
	$(OBJDUMP) -D LED_SDK/led.elf > LED_SDK/led.dis

$(BEEP) : imx6ull_lib/obj/delay.o BEEP/obj/beep.o BEEP/obj/start.o BEEP/obj/main.o
	$(LD) -TBEEP/imx6ull.lds -z noexecstack -o BEEP/beep.elf $^
	$(OBJCOPY) -O binary -S BEEP/beep.elf $@
	$(OBJDUMP) -D BEEP/beep.elf > BEEP/beep.dis

$(KEY) : imx6ull_lib/obj/delay.o KEY/obj/key.o KEY/obj/start.o KEY/obj/main.o BEEP/obj/beep.o
	$(LD) -TKEY/imx6ull.lds -z noexecstack -o KEY/key.elf $^
	$(OBJCOPY) -O binary -S KEY/key.elf $@
	$(OBJDUMP) -D KEY/key.elf > KEY/key.dis

KEY/obj/key.o : KEY/bsp/key.c
	$(CC) $(CFLAGS) -I KEY/bsp -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

KEY/obj/start.o : KEY/project/start.s
	$(CC) $(CFLAGS) -c -o $@ $<

KEY/obj/main.o : KEY/project/main.c
	$(CC) $(CFLAGS) -I KEY/bsp -I BEEP/bsp -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

BEEP/obj/beep.o : BEEP/bsp/beep.c
	$(CC) $(CFLAGS) -I BEEP/bsp/ -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

BEEP/obj/start.o : BEEP/project/start.s
	$(CC) $(CFLAGS) -c -o $@ $<

BEEP/obj/main.o : BEEP/project/main.c
	$(CC) $(CFLAGS) -I BEEP/bsp/ -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

LED_BSP/obj/bsp_led.o : LED_BSP/bsp/led/bsp_led.c
	$(CC) $(CFLAGS) -I $(LED_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

LED_SDK/obj/led.o : LED_SDK/bsp/led/led.c
	$(CC) $(CFLAGS) -I $(LED_SDK_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

LED_BSP/obj/start.o : LED_BSP/project/start.s
	$(CC) $(CFLAGS) -c -o $@ $<

LED_SDK/obj/start.o : LED_SDK/project/start.s
	$(CC) $(CFLAGS) -c -o $@ $<

LED_BSP/obj/main.o : LED_BSP/project/main.c
	$(CC) $(CFLAGS) -I $(LED_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

LED_SDK/obj/main.o : LED_SDK/project/main.c
	$(CC) $(CFLAGS) -I $(LED_SDK_INCLUDE_DIR) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/ccm.o : imx6ull_lib/src/ccm.c
	$(CC) $(CFLAGS) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/delay.o : imx6ull_lib/src/delay.c
	$(CC) $(CFLAGS) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/gpio.o : imx6ull_lib/src/gpio.c
	$(CC) $(CFLAGS) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

imx6ull_lib/obj/iomux.o : imx6ull_lib/src/iomux.c
	$(CC) $(CFLAGS) -I $(IMX6ULL_LIB_INCLUDE_DIR) -c -o $@ $<

clean:
	rm -rf LED_BSP/led.bin LED_BSP/led.elf LED_BSP/led.dis imx6ull_lib/obj/*.o LED_BSP/obj/*.o load.imx
	rm -rf LED_SDK/led.bin LED_SDK/led.elf LED_SDK/led.dis imx6ull_lib/obj/*.o LED_SDK/obj/*.o load.imx
	rm -rf BEEP/beep.bin BEEP/beep.elf BEEP/beep.dis imx6ull_lib/obj/*.o BEEP/obj/*.o load.imx
	rm -rf KEY/key.bin KEY/key.elf KEY/key.dis imx6ull_lib/obj/*.o KEY/obj/*.o load.imx