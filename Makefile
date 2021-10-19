CXX = g++
CXXFLAGS = -g -Wall -Werror
LDFLAGS =
LDLIBS =

# systemc setup
CXXFLAGS += $(shell pkg-config --cflags          systemc)
LDFLAGS  += $(shell pkg-config --libs-only-L     systemc)
LDLIBS   += $(shell pkg-config --libs-only-other systemc)
LDLIBS   += $(shell pkg-config --libs-only-l     systemc)

SOURCES = 	pkt_sender.cpp \
			pkt_receiver.cpp \
			fifo.cpp \
			pkt_sch.cpp \
			stim.cpp \
			switch_clk.cpp \
			main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
APPNAME = test

all: $(APPNAME)

$(APPNAME): $(OBJECTS)
	$(CXX) -o $(APPNAME) $(OBJECTS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJECTS) $(APPNAME)

.PHONY: all clean
