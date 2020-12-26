CC = gcc
LD = gcc
LDFLAGS =
CFLAGS = -I. -O0
OBJS = mkskillrand.o
PROGS = mkskillrand
MANUALS_PS = manual.ps
MANUALS_PDF = manual.pdf
MANUALS_TEXT = manual.txt
PREFIX = /usr/local


all: $(PROGS)

%.txt: %.ms
	@echo " TROFF   " $< " TEXT"
	# @groff -Tascii -ms -Z $< | grotty -c | sed 's/[\x01-\x1F\x7F]//g' | sed 's/\([A-Za-z.,()]\)\1\+/\1/g' > $@
	@groff -Tascii -ms -Z $< | grotty -c | sed 's/[\x01-\x1F\x7F]//g' > $@


%.ps: %.ms
	@echo " TROFF   " $<
	@groff -Tps -ms $< > $@

%.pdf: %.ps
	@echo " PS2PDF   " $<
	@ps2pdf $< $@

%.o: %.c
	@echo " CC   " $<
	@$(CC) $(CFLAGS) -c -o $@ $<

%.pb-c.c: %.proto
	@echo " PROTOC   " $<
	@protoc-c --c_out=. $<

$(PROGS): $(OBJS)
	@echo " LD    mkskillrand"
	@$(LD) -o mkskillrand mkskillrand.o $(LDFLAGS)

manual: $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT)

install: $(PROGS) manual
	@echo " INSTALL    mkskillrand"
	@install mkskillrand $(PREFIX)/bin

uninstall:
	@echo " RM    mkskillrand"
	@rm $(PREFIX)/bin/mkskillrand

.PHONY: clean

clean:
	rm -f *.o Oak*.pb-c.* *.a $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT) $(PROGS)