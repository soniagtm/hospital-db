# This makefile is intended to build the seven programs for
# Hospital database.
#
# This makefile assumes a Linux environment. The executables
# have no extension.
#
# Modified from Aj. Sally's Lab9 Makefile
#
# Modified by Sonia Gautam (Sonia) ID 63070503410
# 13 December 2020
#


EXECUTABLES = hospitalDB

all : $(EXECUTABLES)

mainProgram.o : mainProgram.c
	gcc -c mainProgram.c

displayObject.o : displayObject.c hospitalDB.h
	gcc -c displayObject.c

addObject.o : addObject.c hospitalDB.h
	gcc -c addObject.c

searchObject.o : searchObject.c hospitalDB.h
	gcc -c searchObject.c

readWriteData.o : readWriteData.c hospitalDB.h
	gcc -c readWriteData.c

dateFunctions.o : dateFunctions.c dateFunctions.h
	gcc -c dateFunctions.c

validateData.o : validateData.c hospitalDB.h
	gcc -c validateData.c

hospitalDB : mainProgram.o displayObject.o addObject.o searchObject.o readWriteData.o dateFunctions.o validateData.o
	gcc -o hospitalDB mainProgram.o displayObject.o addObject.o searchObject.o readWriteData.o dateFunctions.o validateData.o

clean :
	-rm *.o
	-rm hospitalDB
