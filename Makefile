CC	= avr-gcc
CFLAGS  = -Wall -Os

all:
	$(MAKE) -C lib
	$(MAKE) -C cmd

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C cmd clean

upload:
	avrdude
