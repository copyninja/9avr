CC	= avr-gcc
CFLAGS  = -Wall -Os
AR = avr-ar

INCLUDE = -Iinclude

LIBSRCS = $(wildcard lib/*.c)
LIBOBJS = $(LIBSRCS:.c=.o)
LIBSTYX = libstyx.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: $(LIBSTYX)

$(LIBSTYX): $(LIBOBJS)
	$(AR) rcs $(LIBSTYX) $(LIBOBJS)

clean:
	rm -f $(LIBOBJS) $(LIBSTYX)

upload:
	avrdude
