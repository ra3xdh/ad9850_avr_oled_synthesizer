PROJECT=trx_ad9850
MMCU=atmega644
PART=m644
PROGRAMMER=usbasp
FUSES=-U lfuse:w:0xf7:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

OBJECTS=main.o ad9850.o lcd.o utils.o adc.o eeprom.o font.o i2c.o sevenseg_digit.o vektor-zeichen.o vektor-zeichen-data.o bar_indicator.o

CC=avr-gcc
CFLAGS=-Os -Wall -Wextra -mmcu=$(MMCU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -std=c99 -fdata-sections 
DEFINES=-DF_CPU=20000000UL -DVEKFONT='(-1)' 
OBJ2HEX=avr-objcopy


all: $(PROJECT).elf
	$(OBJ2HEX) -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJECT).elf $(OBJECTS) 

%.o: %.c 
	$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@ 

hex : 
	$(OBJ2HEX) -O ihex $(PROJECT).elf $(PROJECT).hex

flash : all 
	avrdude -p $(PART) -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex $(FUSES)

clean :
	rm -f *.elf *.hex *.o

