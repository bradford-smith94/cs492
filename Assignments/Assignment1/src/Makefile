# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 1
# 03/04/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=hw1
AUTHOR=bsmith8
PROJECT=cs492-assignment1
LATEX=../report.tex
PDF=$(LATEX:.tex=.pdf)
TEX=pdflatex -shell-escape -interaction=nonstopmode -file-line-error
SRC=main.c q.c fib.c producer.c product.c consumer.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH=-I../include
LIBPATH=
LDLIBS=-lpthread
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

tex:
	$(TEX) -output-directory=.. $(LATEX)

texclean:
	$(RM) ../*.aux
	$(RM) ../*.log

texfclean: texclean
	$(RM) $(PDF)

tar: fclean tex texclean
	tar -cvzf $(AUTHOR)_$(PROJECT).tar.gz ../*

