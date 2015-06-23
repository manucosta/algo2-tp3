#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
CC = g++
DEBUG = -g
CPPFLAGS = -I /aed2 -Wall $(DEBUG)
SOURCES = test.cpp ColaPrior.h aed2.h ../mini_test.h
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = test

$(TARGET):	$(OBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
