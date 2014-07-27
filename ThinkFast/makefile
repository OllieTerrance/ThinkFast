CC=g++ -O3 -std=c++11 -Wall -pedantic
LIBS=-lsndfile -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

OUT=bin/ThinkFast

all: $(SOURCES) $(OUT)

$(OUT): $(OBJECTS)
	mkdir -p bin && $(CC) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) -c $< $(LIBS) -o $@

run: all
	./$(OUT) &

clean:
	rm -f *.o; rm -rf bin/
