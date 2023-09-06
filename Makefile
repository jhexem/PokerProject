# specify the compiler
CC=g++-13

# specify options for the compiler
CFLAGS=-std=c++14 -c

xpoker: pokerClasses.o pokerMain.o
	$(CC) pokerClasses.o pokerMain.o -o xpoker

pokerMain.o: pokerMain.cpp
	$(CC) $(CFLAGS) pokerMain.cpp

pokerClasses.o: pokerClasses.cpp
	$(CC) $(CFLAGS) pokerClasses.cpp

clean:
	rm -f xpoker pokerMain.o pokerClasses.o
