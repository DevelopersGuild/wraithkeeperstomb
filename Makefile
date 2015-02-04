COMPILER=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SFML_PATH=../build/lib/


SOURCES=src/*


OBJECTS=$(SOURCES:.cpp=.o)
SFML_OBJECTS=-lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE=chamberslabyrinth



all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(LDFLAGS) -L$(SFML_PATH)/lib $(OBJECTS) -o $@ $(SFML_OBJECTS)

.cpp.o:
	$(COMPILER) $(CFLAGS) $< -I$(SFML_PATH)/include -o $@
