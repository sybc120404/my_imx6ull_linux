CROSS_COMPILE 	?= arm-linux-gnueabihf-
TARGET 			?= led

CC 				:= $(CROSS_COMPILE)gcc
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump

INCDIRS 		:= imx6ull \
				   bsp/led \
				   bsp/clk \
				   bsp/delay
SRCDIRS 		:= project \
				   bsp/led \
				   bsp/clk \
				   bsp/delay

INCLUDES 		:= $(patsubst %, -I%, $(INCDIRS))

SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES 			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR 		:= $(notdir $(SFILES))
CFILENDIR 		:= $(notdir $(CFILES))

SOBJS 			:= $(patsubst %, obj/%, $(SFILENDIR:.s=.o))
COBJS 			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))

OBJS			:= $(SOBJS) $(COBJS)

VPATH 			:= $(SRCDIRS)

.PHONY: clean

$(TARGET).bin: $(OBJS)
	$(LD) -Timx6ull.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis

$(SOBJS): obj/%.o: %.s
	$(CC) -O2 -Wall -nostdlib -c -o $@ $<

$(COBJS): obj/%.o: %.c
	$(CC) -O2 -Wall -c $(INCLUDES) -o $@ $<

clean:
	rm -rf $(TARGET).bin $(TARGET).elf $(TARGET).dis $(OBJS)