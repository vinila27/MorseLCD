CC = avr-gcc
OBJCOPY = avr-objcopy
MCU = atmega328p
NAME = lcdproj

#File system directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
BIN_DIR = ./bin

#Paths to source and object files
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC))
OBJ := $(OBJ:c=o)

#Size optimisation, microcontroller, C standard, all warnings enabled
CFLAGS = -Os -mmcu=$(MCU) -std=c99 -Wall
#Include Path
CFLAGS += -I./inc

#Comm Port
PORT = /dev/ttyACM0
#Upload Baud Rate
BAUD = 115200


$(BIN_DIR)/$(NAME).hex: $(BIN_DIR)/$(NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN_DIR)/$(NAME).elf: $(OBJ)
	$(CC) -mmcu=$(MCU) -o $@ $^

$(OBJ_DIR)/%o: $(SRC_DIR)/%c
	$(CC) $(CFLAGS) -c -o $@ $<

upload: $(BIN_DIR)/$(NAME).hex
	avrdude -v -c arduino -p atmega328p -P $(PORT) -b $(BAUD) -U flash:w:$<

clean: 
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*
