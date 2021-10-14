CC = avr-gcc
objcopy = avr-objcopy
name = test
objects = main.o lcd.o comm.o 
CFLAGS = -Os -mmcu=atmega328p -std=c99
PORT = COM3
BAUD = 115200

$(name).hex: $(name).elf
	$(objcopy) -O ihex -R .eeprom $< $@

$(name).elf: $(objects)
	$(CC) -o $@ $^

install: $(name).hex
	avrdude -v -c arduino -p atmega328p -P $(PORT) -b $(BAUD) -U flash:w:$<

clean: 
	rm -f $(name).hex $(name).elf $(objects)

