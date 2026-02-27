CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -g -Wall -I -ffreestanding
LDFLAGS = -nostdlib -T linker.ld -lnosys
SRC = startup.c main.c kernel.c
ASM = pendsv.s
TARGET = kernel.elf


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(ASM)

run: $(TARGET)
	qemu-system-arm -machine lm3s6965evb -nographic -kernel $(TARGET)

clean:
	rm -rf $(TARGET)