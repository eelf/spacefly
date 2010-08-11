CC = gcc
CCFLAGS = -Wall -g
LDFLAGS =
OBJDIR = objs

OBJECTS = helloworld.o piece.o camera.o

OBJS = $(OBJECTS:%=$(OBJDIR)/%)
SRCS = $(OBJECTS:%.o=%.c)

ifndef OSTYPE
  OSTYPE = $(shell uname -s|awk '{print tolower($$0)}')
  #export OSTYPE
endif

ifeq ($(OSTYPE),linux)
	LDFLAGS += -lglut -lGLU
else ifeq ($(OSTYPE),mac)
	LDFLAGS += -lglut -lGLU
else
	LDFLAGS += -lglut -lGLU
endif

$(OBJDIR)/%.o: %.c
	if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	$(CC) $(CCFLAGS) -c $< -o $@

helloworld: $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm $(OBJDIR)/*

run: helloworld
	./helloworld

all: helloworld

