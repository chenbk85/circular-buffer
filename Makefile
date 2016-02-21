CC=g++-4.7
CFLAGS=-c -g -std=c++11 -Wall
LDFLAGS=
SOURCES=honeybee.cpp
OBJECTS=$(SOURCES:.cpp=.o)
DEPS:=$(OBJECTS:.o=.d)
EXECUTABLE=honeybee

all: $(SOURCES) $(EXECUTABLE)

-include $(DEPS)

%.o: %.cpp
	$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CFLAGS) -o $@ $<

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS)
