CC = g++
CFLAGS = -W -Wall -std=c++17 -O3 -pthread
LINK = `pkg-config --cflags --libs opencv`
SRC = julia.cpp

julia: 	
	$(CC) $(CFLAGS) $(SRC) $(LINK)

clean:
	rm a.out
