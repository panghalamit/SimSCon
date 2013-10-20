# makefile

IDIR = include
CC = g++
DEBUG = -g
PROFILE =
CFLAGS = -Wall -c $(DEBUG) -I$(IDIR) $(PROFILE)

SDIR = src
ODIR = bin
LIBS = -lm

_DEPS = event.h simulation.h vm.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = event.o vm.o simulation.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

all: dir $(ODIR)/main

dir:    
	mkdir -p $(ODIR)

$(ODIR)/main: $(OBJ)
	$(CC) $(LIBS) -I$(IDIR) -o $@ $^ $(SDIR)/main.cpp $(PROFILE)
clean:
	rm -rf $(ODIR) *~ $(INCDIR)/*~

.PHONY: clean
