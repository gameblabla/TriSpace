CC          	= gcc

CFLAGS			= -O0 -g3 -Isrc
LDFLAGS     	= -lSDL -lSDL_image -lm -lSDL_mixer -lSDL_ttf

PNAME			= main.elf

TINGYGL_LIB		= -lGL

SDL_INCLUDE		= -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
TINYGL_INCLUDE	= -I/usr/include/GL
INCLUDES		=  $(SDL_INCLUDE) $(TINYGL_INCLUDE)

ifdef TARGET
include $(TARGET).mk
endif

# Files to be compiled
SRCDIR 		=  ./src ./res ./src/universe ./src/engine ./src/ui ./src/npcs
VPATH		= $(SRCDIR)
SRC_C		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
OBJS		= $(notdir $(patsubst %.c, %.o, $(SRC_C)))

# Rules to make executable
$(PNAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(PNAME) $^ $(LDFLAGS) $(TINGYGL_LIB)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

debug: CFLAGS += -DDEBUG=1 -DNO_FPS_LIMIT=1 -g
debug: $(PNAME)

clean:
	rm *.o
