CC = gcc
LD = gcc
LDFLAGS =
CFLAGS = -I. -O0
OBJS = mkskillrand.o mkspawnrand.o mkitemrand.o mkskillrand3.o
PROGS = mkskillrand mkspawnrand mkitemrand GUI.exe mkskillrand3
MANUALS_PS = manual.ps
MANUALS_PDF = manual.pdf
MANUALS_TEXT = manual.txt
PREFIX = /usr/local
RES = GUIresources.res

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
	@echo " LD    mkskillrand3"
	@$(LD) -o mkskillrand3 mkskillrand3.o $(LDFLAGS)
	@echo " LD    mkspawnrand"
	@$(LD) -o mkspawnrand mkspawnrand.o $(LDFLAGS)
	@echo " LD    mkitemrand"
	@$(LD) -o mkitemrand mkitemrand.o $(LDFLAGS)

manual: $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT)

install: $(PROGS) manual
	@echo " INSTALL    mkskillrand"
	@install mkskillrand $(PREFIX)/bin
	@echo " INSTALL    mkskillrand3"
	@install mkskillrand3 $(PREFIX)/bin
	@echo " INSTALL    mkspawnrand"
	@install mkspawnrand $(PREFIX)/bin
	@echo " INSTALL    mkitemrand"
	@install mkitemrand $(PREFIX)/bin

uninstall:
	@echo " RM    mkskillrand"
	@rm $(PREFIX)/bin/mkskillrand
	@echo " RM    mkskillrand3"
	@rm $(PREFIX)/bin/mkskillrand3
	@echo " RM    mkspawnrand"
	@rm $(PREFIX)/bin/mkspawnrand
	@echo " RM    mkitemrand"
	@rm $(PREFIX)/bin/mkitemrand

.PHONY: clean

clean:
	rm -f *.o Oak*.pb-c.* *.a $(MANUALS_PS) $(MANUALS_PDF) $(MANUALS_TEXT) $(PROGS) $(RES)
