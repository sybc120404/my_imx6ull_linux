CROSS_COMPILE 	?= arm-linux-gnueabihf-

LED_BSP_DIR 	:= LED_BSP

CC 				:= $(CROSS_COMPILE)gcc
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump

INCDIRS_LED 	:= imx6ull_lib/inc \
					$(LED_BSP_DIR)/bsp/led \
SRCDIRS_LED 	:= imx6ull_lib/src \
				   	$(LED_BSP_DIR)/project \
				   	$(LED_BSP_DIR)/led \

INCLUDES_LED 	:= $(patsubst %, -I%, $(INCDIRS_LED))

SFILES_LED			:= $(foreach dir, $(SRCDIRS_LED), $(wildcard $(dir)/*.s))
CFILES_LED 			:= $(foreach dir, $(SRCDIRS_LED), $(wildcard $(dir)/*.c))

SFILENDIR_LED 		:= $(notdir $(SFILES_LED))
CFILENDIR_LED 		:= $(notdir $(CFILES_LED))

SOBJS_LED 			:= $(patsubst %, obj/%, $(SFILENDIR_LED:.s=.o))
COBJS_LED 			:= $(patsubst %, obj/%, $(CFILENDIR_LED:.c=.o))

OBJS_LED			:= $(SOBJS_LED) $(COBJS_LED)

VPATH 			:= $(SRCDIRS_LED)

TARGET_LED		:= led
TARGET_BEEP		:= beep

.PHONY: all led_clean

all: led

led: $(TARGET_LED).bin

$(LED_BSP_DIR)/$(TARGET_LED).bin: $(LED_BSP_DIR)/$(OBJS_LED)
	$(LD) -T$(LED_BSP_DIR)/imx6ull.lds -o $(LED_BSP_DIR)/$(TARGET_LED).elf $^
	$(OBJCOPY) -O binary -S $(LED_BSP_DIR)/$(TARGET_LED).elf $@
	$(OBJDUMP) -D $(TARGET_LED).elf > $(TARGET_LED).dis

$(LED_BSP_DIR)/$(SOBJS_LED): $(LED_BSP_DIR)/obj/%.o: %.s
	$(CC) -O2 -Wall -nostdlib -c -o $@ $<

$(LED_BSP_DIR)/$(COBJS_LED): $(LED_BSP_DIR)/obj/%.o: %.c
	$(CC) -O2 -Wall -c $(INCLUDES_LED) -o $@ $<

led_clean:
	rm -rf $(LED_BSP_DIR)/$(TARGET_LED).bin $(LED_BSP_DIR)/$(TARGET_LED).elf $(LED_BSP_DIR)/$(TARGET_LED).dis $(LED_BSP_DIR)/$(OBJS_LED)