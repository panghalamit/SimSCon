# makefile

IDIR = include
PIDIR = ../simcon/include
CC = g++
DEBUG = -g
PROFILE =
CFLAGS = -Wall -c $(DEBUG) -I$(IDIR) -I$(PIDIR) $(PROFILE)

SDIR = src
ODIR = bin
PODIR = ../simcon/bin
LIBS = -lm

_DEPS = event.h simulation.h vm.h common.h lcgrand.h simsdata.h
_PDEPS = simdata.h utils.h algo.h stateIterator.h state.h config.h policy.h khanna.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) $(patsubst %,$(PIDIR)/%,$(_PDEPS))

_OBJ = event.o vm.o simulation.o common.o lcgrand.o simsdata.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_POBJ = simdata.o utils.o algo.o stateIterator.o state.o policy.o khanna.o
POBJ = $(patsubst %,$(PODIR)/%,$(_POBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

all: dir $(ODIR)/sim

dir:
	mkdir -p $(ODIR)

$(ODIR)/sim: $(OBJ) $(POBJ)
	$(CC) $(LIBS) -I$(IDIR) -I$(PIDIR) -o $@ $^ $(SDIR)/main.cpp $(PROFILE)

clean:
	rm -rf $(ODIR) *~ $(INCDIR)/*~

distclean: clean
	rm -f results/*.txt
	rm -f results/*.pdf

plot:
	cd results && gnuplot service_time_plot.p

.PHONY: clean
