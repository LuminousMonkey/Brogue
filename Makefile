PROG := bin/brogue
# Need SDL flags for compiling.
SDL_FLAGS = `sdl-config --cflags` `sdl-config --libs`
LIBTCODDIR=src/libtcod-1.5.2
LIBS = $(shell pkg-config --libs ncurses) -lm
CURSES_CFLAGS = $(shell pkg-config --cflags ncurses)

COMMON_CFLAGS = -MMD -Wall -Wno-parentheses -Isrc/brogue -Isrc/platform ${DEFINES}
CFLAGS = $(COMMON_CFLAGS) $(CURSES_CFLAGS)
RELEASENAME=brogue-1.7.3
LASTTARGET := $(shell ./brogue --target)
CC ?= gcc
OUTDIRS := obj/brogue obj/platform

SRCFILES := $(wildcard src/brogue/*.c) $(wildcard src/platform/*.c)
OBJFILES := $(patsubst src/%.c,obj/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,obj/%.d,$(SRCFILES))

ifeq (${LASTTARGET},both)
all : dirs both
else ifeq (${LASTTARGET},curses)
all : dirs curses
else ifeq (${LASTTARGET},tcod)
all : dirs tcod
else
all : dirs both
endif


TCOD_DEF = -DBROGUE_TCOD -I$(LIBTCODDIR)/include
TCOD_DEP = ${LIBTCODDIR}
TCOD_LIB = -L. -L${LIBTCODDIR} ${SDL_FLAGS} -ltcod -Wl,-rpath,.

CURSES_DEF = -DBROGUE_CURSES
CURSES_LIB = -lncurses -lm

.PHONY : clean dirs both curses tcod tar

all : dirs $(PROG)

dirs:
	@mkdir -p $(OUTDIRS)

tcod : DEPENDENCIES += ${TCOD_DEP}
tcod : DEFINES += ${TCOD_DEF}
tcod : LIBRARIES += ${TCOD_LIB}

curses : DEFINES = ${CURSES_DEF}
curses : LIBRARIES = ${CURSES_LIB}

both : DEPENDENCIES += ${TCOD_DEP}
both : DEFINES += ${TCOD_DEF} ${CURSES_DEF}
both : LIBRARIES += ${TCOD_LIB} ${CURSES_LIB}

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
both : bin/brogue
curses : bin/brogue
tcod : bin/brogue
endif

$(PROG): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

#bin/brogue : ${DEPENDENCIES} ${BROGUEFILES}
#	$(CC) -O2 -march=i586 -o bin/brogue ${BROGUEFILES} ${LIBRARIES} -Wl,-rpath,.

# Rule for making all *.c files in src to *.o files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -MF $(patsubst obj/%.o, obj/%.d,$@) -c $< -o $@

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

