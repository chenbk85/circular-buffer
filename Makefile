CC=g++-4.7
CFLAGS=-c -g -std=c++11 -Wall
LDFLAGS=
SOURCES=honeybee.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=honeybee

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
