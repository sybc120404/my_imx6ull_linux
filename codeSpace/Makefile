# files path of project
INCLUDE_DIR		:= 	inc
INCLUDE_DIR_STD	:=	stdio/include
OBJECT_DIR		:= 	obj/
ASSEMBLY_DIR	:= 	asm/
SOURCE_DIR		:=	asm/	\
					src/app/beep	\
					src/app/key		\
					src/app/led		\
					src/app/ext_interrupt	\
					src/app/epit	\
					src/app/gpt		\
					src/app/ap3216c	\
					src/app/icm20608	\
					src/platform 	\
					src/project		\
					stdio/lib
TARGET_DIR		:= 	target/
LIB_PATH		:= 	-lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4/

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
FLOAT_CACL_FLAG	:= -march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=hard
CINCLUDE		:= -I $(INCLUDE_DIR) -I $(INCLUDE_DIR_STD)



# target of project
TARGET   		:= main

.PHONY: clean

$(TARGET_DIR)$(TARGET).bin : $(OBJS)
	$(LD) -T$(LDFILE) -o $(TARGET_DIR)$(TARGET).elf $^ $(LIB_PATH)
	$(OBJCOPY) -O binary -S $(TARGET_DIR)$(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET_DIR)$(TARGET).elf > $(TARGET_DIR)$(TARGET).dis

$(SOBJS) : $(OBJECT_DIR)%.o : %.s
	$(CC) $(CFLAGS) $(CINCLUDE) -fno-builtin -c -o $@ $<

$(COBJS) : $(OBJECT_DIR)%.o : %.c
	$(CC) $(CFLAGS) $(CINCLUDE) $(FLOAT_CACL_FLAG) -fno-builtin -Wa,-mimplicit-it=thumb -c -o $@ $<

clean:
	rm -rf $(TARGET_DIR)$(TARGET)* $(OBJS) load.imx