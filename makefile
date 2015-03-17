CC = gcc
CCFLAGS = -Wall -g -std=c99
LDFLAGS =
OBJDIR = objs

TARGET = cubik
MODULES = $(TARGET) piece camera side data gl_extend
#MODULES += cube



OBJS = $(MODULES:%=$(OBJDIR)/%.o)
SRCS = $(MODULES:%=%.c)

ifndef OSTYPE
  OSTYPE = $(shell uname -s|awk '{print tolower($$0)}')
  #export OSTYPE
endif

ifeq ($(OSTYPE),linux)
	LDFLAGS += -lglut -lGLU
else ifeq ($(OSTYPE),darwin)
	LDFLAGS += -framework GLUT -framework OpenGL
else
	LDFLAGS += -lglut -lGLU
endif

$(OBJDIR)/%.o: %.c
	if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	$(CC) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm $(OBJDIR)/*

run: $(TARGET)
	./$(TARGET)

all: $(TARGET)

