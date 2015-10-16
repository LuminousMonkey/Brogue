PROG := bin/brogue
TEST_PROG := bin/unit_tests

# For Debugging Makefile
# OLD_SHELL := $(SHELL)
# SHELL = $(warning [$@ ($^) ($?)])$(OLD_SHELL)

# Need SDL flags for compiling.
SDL_FLAGS = $(shell pkg-config --cflags sdl)
SDL_LIBS = $(shell pkg-config --libs sdl)

CURSES_LIBS = $(shell pkg-config --libs ncurses)
CURSES_CFLAGS = $(shell pkg-config --cflags ncurses)

CUNIT_LIBS = $(shell pkg-config --libs cunit)
CUNIT_CFLAGS = $(shell pkg-config --cflags cunit)

INCLUDES = -Isrc/brogue -Isrc/platform -I/usr/include/libtcod

CFLAGS = -MMD -Wall -pedantic -std=c99 $(INCLUDES) ${DEFINES}
LIBS = -lm
RELEASENAME=brogue-1.7.3
CC = clang
OUTDIRS := obj/brogue obj/platform obj/tests obj/tests/brogue

ifeq (${DEBUG},1)
  CFLAGS += -g
endif

TCOD_DEF = -DBROGUE_TCOD
TCOD_LIBS = $(shell pkg-config --libs sdl) -ltcod
TCOD_CFLAGS = $(shell pkg-config --cflags sdl)

CURSES_DEF = -DBROGUE_CURSES

.PHONY : clean dirs both curses tcod tar

all: tcod

dirs:
	@mkdir -p $(OUTDIRS)

SRCFILES := $(wildcard src/brogue/*.c) $(wildcard src/platform/*.c)
OBJFILES := $(patsubst src/%.c,obj/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,obj/%.d,$(SRCFILES))

tcod : DEFINES = ${TCOD_DEF}
tcod : LIBS += $(TCOD_LIBS)
tcod : CFLAGS += ${TCOD_CFLAGS}

curses : DEFINES = ${CURSES_DEF}
curses : LIBS += ${CURSES_LIBS}
curses : CFLAGS += ${CURSES_CFLAGS}

both: DEFINES = ${TCOD_DEF} ${CURSES_DEF}
both : LIBS = ${TCOD_LIBS} ${CURSES_LIBS}
both: CFLAGS += ${TCOD_CFLAGS} ${CURSES_CFLAGS}

ifeq (${TESTS},1)
  SRCFILES = $(wildcard src/tests/brogue/*.c) src/tests/unit_tests.c

  LIBS += $(CUNIT_LIBS)
  CFLAGS += ${CUNIT_CFLAGS}
  PROG := $(TEST_PROG)
  INCLUDES += -Itests/src/brogue
  OBJFILES = $(patsubst src/%.c,obj/%.o,$(SRCFILES))
  DEPFILES = $(patsubst src/%.c,obj/%.d,$(SRCFILES))
endif

both : dirs bin/brogue
curses : dirs $(PROG)
tcod : dirs $(PROG)

$(PROG): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Rule for making all *.c files in src to *.o files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(DEFINES) -MF $(patsubst obj/%.o, obj/%.d,$@) -c $< -o $@

clean:
	rm -f src/brogue/*.o src/platform/*.o $(PROG) $(TEST_PROG)
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

-include $(SRCFILES:.c=.d)
