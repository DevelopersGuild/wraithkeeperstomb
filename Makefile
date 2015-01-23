COMPILER=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SFML_PATH=binaryLibs/SFML-2.2


SOURCES=src/main.cpp


OBJECTS=$(SOURCES:.cpp=.o)
SFML_OBJECTS=-lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE=chamberslabyrinth



all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -L$(SFML_PATH)/lib $(OBJECTS) $(SFML_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -I$(SFML_PATH)/include -o $@
