# da se iz vima moze :make
PROJECT=trx_ad9850
MMCU=atmega644
PART=m644
PROGRAMMER=usbasp
FUSES=-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

OBJECTS=main.o ad9850.o lcd_library.o utils.o

CC=avr-gcc
CFLAGS=-Os -Wall -Wextra -mmcu=$(MMCU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -std=c99 -fdata-sections 
OBJ2HEX=avr-objcopy


all: $(PROJECT).elf
	$(OBJ2HEX) -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJECT).elf $(OBJECTS) 

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@ 

hex : 
	$(OBJ2HEX) -O ihex $(PROJECT).elf $(PROJECT).hex

flash : all 
	avrdude -p $(PART) -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex $(FUSES)

clean :
	rm -f *.elf *.hex *.o

