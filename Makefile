SOURCES = othello.cpp
HEADERS = othello.hpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBS = -lm

CC = g++
CPPFLAGS = -std=c++11 -g

%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $<

othello: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

tests: test-othello

test-othello: test-othello.o othello.o
	$(CC) -o $@ test-othello.o othello.o $(LIBS)

test-othello: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

test-test: test.o othello.o
	$(CC) -o $@ test.o othello.o  $(LIBS)

clean: 
	$(RM) othello $(OBJECTS) test-*
