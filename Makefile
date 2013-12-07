PROG := bin/brogue
# Need SDL flags for compiling.
SDL_FLAGS = $(shell pkg-config --cflags sdl)
SDL_LIBS = $(shell pkg-config --libs)

CURSES_LIBS = $(shell pkg-config --libs ncurses) -lm
CURSES_CFLAGS = $(shell pkg-config --cflags ncurses)

CFLAGS = -MMD -Wall -pedantic -Weverything -std=c99 -Isrc/brogue -Isrc/platform ${DEFINES}
RELEASENAME=brogue-1.7.3
LASTTARGET := $(shell ./brogue --target)
CC ?= gcc
OUTDIRS := obj/brogue obj/platform

SRCFILES := $(wildcard src/brogue/*.c) $(wildcard src/platform/*.c)
OBJFILES := $(patsubst src/%.c,obj/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,obj/%.d,$(SRCFILES))

ifeq (${LASTTARGET},both)
all : both
else ifeq (${LASTTARGET},curses)
all : curses
else ifeq (${LASTTARGET},tcod)
all : tcod
else
all : both
endif

TCOD_DEF = -DBROGUE_TCOD
TCOD_LIBS = $(shell pkg-config --libs sdl) -ltcod -Wl
TCOD_CFLAGS = $(shell pkg-config --cflags sdl)

CURSES_DEF = -DBROGUE_CURSES

.PHONY : clean dirs both curses tcod tar

all : $(PROG)

dirs:
	@mkdir -p $(OUTDIRS)

tcod : DEFINES = ${TCOD_DEF}
tcod : LIBS = ${TCOD_LIBS}
tcod : CFLAGS += ${TCOD_CFLAGS}

curses : DEFINES = ${CURSES_DEF}
curses : LIBS = ${CURSES_LIBS}
curses : CFLAGS += ${CURSES_CFLAGS}

both : DEFINES = ${TCOD_DEF} ${CURSES_DEF}
both : LIBS = ${TCOD_LIBS} ${CURSES_LIBS}
both: CFLAGS += ${TCOD_CFLAGS} ${CURSES_CFLAGS}

ifeq (${LASTTARGET},both)
both : bin/brogue
tcod : clean bin/brogue
curses : clean bin/brogue
else ifeq (${LASTTARGET},curses)
curses : bin/brogue
tcod : clean bin/brogue
both : clean bin/brogue
else ifeq (${LASTTARGET},tcod)
tcod : bin/brogue
curses : clean bin/brogue
both : clean bin/brogue
else
both : dirs bin/brogue
curses : dirs bin/brogue
tcod : dirs bin/brogue
endif

$(PROG): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

#bin/brogue : ${DEPENDENCIES} ${BROGUEFILES}
#	$(CC) -O2 -march=i586 -o bin/brogue ${BROGUEFILES} ${LIBRARIES} -Wl,-rpath,.

# Rule for making all *.c files in src to *.o files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(DEFINES) -MF $(patsubst obj/%.o, obj/%.d,$@) -c $< -o $@

clean : 
	rm -f src/brogue/*.o src/platform/*.o bin/brogue
	rm -fr obj

${LIBTCODDIR} :
	src/get-libtcod.sh

tar : both
	rm -f ${RELEASENAME}.tar.gz
	tar --transform 's,^,${RELEASENAME}/,' -czf ${RELEASENAME}.tar.gz \
	Makefile \
	brogue \
	$(wildcard *.sh) \
	$(wildcard *.rtf) \
	readme \
	$(wildcard *.txt) \
	bin/brogue \
	bin/keymap \
	bin/icon.bmp \
	bin/brogue-icon.png \
	$(wildcard bin/fonts/*.png) \
	$(wildcard bin/*.so) \
	$(wildcard src/*.sh) \
	$(wildcard src/brogue/*.c) \
	$(wildcard src/brogue/*.h) \
	$(wildcard src/platform/*.c) \
	$(wildcard src/platform/*.h)

