# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 2
# 03/23/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=VMsimulator
AUTHOR=bsmith8
PROJECT=cs492-assignment2
SRC=main.c page_table.c
OBJ=$(SRC:.c=.o)
CC=gcc
LATEX=../report.tex
PDF=$(LATEX:.tex=.pdf)
TEX=pdflatex -shell-escape -interaction=nonstopmode -file-line-error
RM=rm -f
INCLPATH=-I../include
LIBPATH=
LDLIBS=
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
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

test: debug
	./$(PRG) ../plist ../ptrace 2 FIFO +

plots: re
	./plot.sh

tex: plots
	$(TEX) -output-directory=.. $(LATEX)

texclean:
	$(RM) ../*.aux
	$(RM) ../*.log
	$(RM) ../*.png

texfclean: texclean
	$(RM) $(PDF)

tar: fclean tex texclean
	tar -cvzf $(AUTHOR)_$(PROJECT).tar.gz ../*

