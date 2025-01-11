SRC = src/
INC = inc/
OBJ = obj/
BIN := bin/
LD := arm-linux-gnueabihf-ld
GCC := arm-linux-gnueabihf-gcc
OBJCOPY := arm-linux-gnueabihf-objcopy
OBJDUMP := arm-linux-gnueabihf-objdump
CFLAGS := -I$(INC) -Wall -nostdlib -O2

OBJS := $(OBJ)start.o $(OBJ)led.o

$(BIN)led.bin: $(OBJS)
	$(LD) -Timx6ull.lds -o $(OBJ)led_elf $^
	$(OBJCOPY) -O binary -S $(OBJ)led_elf $@
	$(OBJDUMP) -D -m arm $(OBJ)led_elf > $(OBJ)led.dis

$(OBJ)%.o : $(SRC)%.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(OBJ)%.o : $(SRC)%.s
	arm-linux-gnueabihf-gcc -c $(SRC)start.s -o $(OBJ)start.o

clean:
	rm -rf $(OBJ)*.o $(BIN)*.bin