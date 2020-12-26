CC = gcc
LD = gcc
LDFLAGS =
CFLAGS = -I. -O0
OBJS = mkskillrand3.o mkskillrand4.o mkskillblank.o
PROGS = mkskillrand3 mkskillrand4 mkskillblank
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
	@echo " LD    mkskillrand3"
	@$(LD) -o mkskillrand3 mkskillrand3.o $(LDFLAGS)
	@echo " LD    mkskillrand4"
	@$(LD) -o mkskillrand4 mkskillrand4.o $(LDFLAGS)
	@echo " LD    mkskillblank"
	@$(LD) -o mkskillblank mkskillblank.o $(LDFLAGS)

manual: $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT)

install: $(PROGS) manual
	@echo " INSTALL    mkskillrand3"
	@install mkskillrand3 $(PREFIX)/bin
	@echo " INSTALL    mkskillrand4"
	@install mkskillrand4 $(PREFIX)/bin

uninstall:
	@echo " RM    mkskillrand3"
	@rm $(PREFIX)/bin/mkskillrand3
	@echo " RM    mkskillrand4"
	@rm $(PREFIX)/bin/mkskillrand4

.PHONY: clean

clean:
	rm -f *.o Oak*.pb-c.* *.a $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT) $(PROGS)
