# Bradford Smith (bsmith8)
# Makefile for CS 492 Lab 1
# 02/16/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=dp_one
AUTHOR=bsmith8
PROJECT=cs492-lab1
SRC=dp_one.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH=
LIBPATH=
LDLIBS=-lpthread
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+=
CPPFLAGS+= -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(PRG)

re: fclean all

tar: fclean
	tar -cvzf $(AUTHOR)_$(PROJECT).tar.gz ./*

