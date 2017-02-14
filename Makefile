CC ?= gcc
EXTRA_CFLAGS ?=
EXTRA_LDFLAGS ?=
CFLAGS := $(shell pkg-config --cflags glib-2.0 gio-2.0 gtk+-3.0 libxml-2.0) -Wall -g -ansi -std=c99 $(EXTRA_CFLAGS)
LDFLAGS = $(EXTRA_LDFLAGS) -Wl,--as-needed
LDADD := $(shell pkg-config --libs glib-2.0 gio-2.0 gtk+-3.0 gthread-2.0 alsa libxml-2.0) -lexpat -lm
OBJECTS = gdigi.o gui.o effects.o preset.o gtkknob.o preset_xml.o
DEPFILES = $(foreach m,$(OBJECTS:.o=),.$(m).m)

.PHONY : clean distclean all
%.o : %.c
	$(CC) $(CFLAGS) -c $<

.%.m : %.c
	$(CC) $(CFLAGS) -M -MF $@ -MG $<

all: gdigi

gdigi: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $+ $(LDADD)

images/gdigi_icon.h: images/icon.png
	gdk-pixbuf-csource --raw --name=gdigi_icon $< > $@

clean:
	rm -f *.o

distclean : clean
	rm -f .*.m
	rm -f images/gdigi_icon.h
	rm -f gdigi

install: gdigi
	install gdigi $(DESTDIR)/usr/bin
	install -m 0644 gdigi.desktop $(DESTDIR)/usr/share/applications/
	install -m 0644 images/gdigi.png $(DESTDIR)/usr/share/icons/

NODEP_TARGETS := clean distclean
depinc := 1
ifneq (,$(filter $(NODEP_TARGETS),$(MAKECMDGOALS)))
depinc := 0
endif
ifneq (,$(fitler-out $(NODEP_TARGETS),$(MAKECMDGOALS)))
depinc := 1
endif

ifeq ($(depinc),1)
-include $(DEPFILES)
endif
