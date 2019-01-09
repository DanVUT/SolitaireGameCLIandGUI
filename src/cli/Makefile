CC = g++
CFLAGS = -std=c++11
LDFLAGS =


SOURCES = main.cpp stacks.cpp row.cpp pileOfCards.cpp game.cpp deckOfCards.cpp card.cpp
HEADERS = stacks.h row.h pileOfCards.h game.h deckOfCards.h card.h
OBJECTS = $(SOURCES:.cpp=.o)
EXE = hra2017-cli

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean

clean:
	rm -rf *.o $(EXE)
	rm -rf hra2017-cli
doxygen:
	doxygen Doxyfile