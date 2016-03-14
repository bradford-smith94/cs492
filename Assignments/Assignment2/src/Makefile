# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 2
# 03/14/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=VMsimulator
AUTHOR=bsmith8
PROJECT=cs492-assignment2
SRC=
# C++: OBJ=$(SRC:.cpp=.o)
# C: OBJ=$(SRC:.c=.o)
# C++: CXX=g++
# C: CC=gcc
RM=rm -f
INCLPATH=
LIBPATH=
LDLIBS=
LDFLAGS+=
# implicit compiling rules:
# C++ compiled with: `$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)`
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+=
CPPFLAGS+= -pedantic-errors -Wall
CXXFLAGS+=
DBFLGS= -g -DDEBUG

all: $(OBJ)
	#$(CXX) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)
	#$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

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

