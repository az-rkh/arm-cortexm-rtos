CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -g -Wall
LDFLAGS = -nostdlib -T linker.ld
SRC = startup.c main.c
TARGET = kernel.elf


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

run: $(TARGET)
	qemu-system-arm -machine lm3s6965evb -nographic -kernel $(TARGET)

clean:
	rm -rf $(TARGET)