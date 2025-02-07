# files path of project
INCLUDE_DIR		:= 	inc/
OBJECT_DIR		:= 	obj/
ASSEMBLY_DIR	:= 	asm/
SOURCE_DIR		:=	asm/	\
					src/app/beep	\
					src/app/key		\
					src/app/led		\
					src/app/ext_interrupt	\
					src/app/epit	\
					src/app/gpt		\
					src/platform 	\
					src/project
TARGET_DIR		:= 	target/

SFILES			:= $(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.s))
CFILES			:= $(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.c))
SFILESNDIR		:= $(notdir $(SFILES))
CFILESNDIR		:= $(notdir $(CFILES))
SOBJS			:= $(patsubst %, $(OBJECT_DIR)%, $(SFILESNDIR:.s=.o))
COBJS			:= $(patsubst %, $(OBJECT_DIR)%, $(CFILESNDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

LDFILE			:= asm/imx6ull.lds

VPATH			:= $(SOURCE_DIR)

# some common variables of cross-compile
CROSS_COMPILE 	?= arm-linux-gnueabihf-
CC 				:= $(CROSS_COMPILE)gcc
LD 				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump
CFLAGS 			:= -Wall -O2 -nostdlib
CINCLUDE		:= -I $(INCLUDE_DIR)



# target of project
TARGET   		:= main

.PHONY: clean

$(TARGET_DIR)$(TARGET).bin : $(OBJS)
	$(LD) -T$(LDFILE) -o $(TARGET_DIR)$(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET_DIR)$(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET_DIR)$(TARGET).elf > $(TARGET_DIR)$(TARGET).dis

$(SOBJS) : $(OBJECT_DIR)%.o : %.s
	$(CC) $(CFLAGS) $(CINCLUDE) -c -o $@ $<

$(COBJS) : $(OBJECT_DIR)%.o : %.c
	$(CC) $(CFLAGS) $(CINCLUDE) -c -o $@ $<

clean:
	rm -rf $(TARGET_DIR)$(TARGET)* $(OBJS) load.imx