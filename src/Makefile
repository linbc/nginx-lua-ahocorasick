#.SUFFIXES: .c .o

#.c.o:
#	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIR)

PATH:=${ALCHEMY_HOME}/achacks:${PATH}
CC = gcc
CCPP = g++
AR = ar
CFLAGS := -Wall -W -g -O3
LDFLAGS = 
PROJECT_DIR = ../..
INCLUDE_DIR = -I$(PROJECT_DIR)/src -I$(PROJECT_DIR)/ahocorasick -I../ -I./
LIBNAME = libahocorasick.a

OBJS_SRC = $(patsubst %.c, %.o,$(wildcard *.c))

.PHONY: all lib echo clean

src/%.o:src/%.c
	$(CC) $< -o $@ -c $(CFLAGS) $(INCLUDE_DIR)

all: $(LIBNAME) lib

$(LIBNAME):$(OBJS_RSA) $(OBJS_SRC) 
	$(AR) rcs $(LIBNAME) $(OBJS_SRC) 
	ranlib $(LIBNAME)

lib:
	@cp -p $(LIBNAME) $(PROJECT_DIR)/lib
	@cp -p *.l.bc $(PROJECT_DIR)/lib

echo:
	@echo $(OBJS_SRC) $(OBJS_RSA)

clean:
	rm -rf $(LIBNAME) $(OBJS_SRC) $(OBJS_RSA) *.bc
	rm -r $(PROJECT_DIR)/lib/$(LIBNAME)
