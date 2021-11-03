CC = avr-gcc
objcopy = avr-objcopy
MCU = atmega328p
name = test
objects = main.o lcd.o comm.o 
CFLAGS = -Os -mmcu=$(MCU) -std=c99 -Wall
PORT = /dev/ttyACM0
BAUD = 115200

$(name).hex: $(name).elf
	$(objcopy) -O ihex -R .eeprom $< $@

$(name).elf: $(objects)
	$(CC) -mmcu=$(MCU) -o $@ $^

upload: $(name).hex
	avrdude -v -c arduino -p atmega328p -P $(PORT) -b $(BAUD) -U flash:w:$<

clean: 
	rm -f $(name).hex $(name).elf $(objects)

