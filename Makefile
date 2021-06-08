# da se iz vima moze :make
PROJECT=trx_ad9850
MMCU=atmega644
PART=m644
PROGRAMMER=usbasp

OBJECTS=main.o ad9850.o

CC=avr-gcc
CFLAGS=-Os -Wall -mmcu=$(MMCU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -std=c99 -fdata-sections 
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
	avrdude -p $(PART) -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex

clean :
	rm -f *.elf *.hex *.o

