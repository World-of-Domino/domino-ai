PNAME         = domino-ai
CC            = gcc
CFLAGS        = -Wall
LDFLAGS       = -s
VER           = 0.1
SRCS          = src
PREFIX        = /usr/local
INSTALL       = install
LN            = ln -fs

.PHONY: all clean install

all: $(PNAME)

clean:
	rm -f $(PNAME)

$(PNAME): $(SRCS)/lista.c $(SRCS)/domino.c $(SRCS)/main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

install: $(PNAME)
	$(INSTALL) -d $(PREFIX)/bin
	$(INSTALL) -m 0755 $(PNAME) $(PREFIX)/bin/
