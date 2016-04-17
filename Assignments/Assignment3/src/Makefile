# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 3
# 04/17/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=fs
AUTHOR=bsmith8
PROJECT=cs492-assignment3
FILES=../file_list.txt
DIRS=../dir_list.txt
ifndef ROOT
	ROOT=..
endif

SRC=main.c fs_cd.c fs_ls.c fs_mkdir.c fs_create.c fs_append.c fs_remove.c \
	fs_delete.c fs_exit.c fs_dir.c fs_prfiles.c fs_prdisk.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH= -I../include
LIBPATH=
LDLIBS=
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(OBJ) inputs
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

# generate input files for the program
inputs:
	find $(ROOT) -type d > $(DIRS)
	find $(ROOT) -type f -ls > $(FILES)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(DIRS)
	$(RM) $(FILES)
	$(RM) $(PRG)

re: fclean all

tar: fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../*

