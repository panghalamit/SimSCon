# makefile

IDIR = include
CC = g++
DEBUG = -g
PROFILE =
CFLAGS = -Wall -c $(DEBUG) -I$(IDIR) $(PROFILE)

SDIR = src
ODIR = bin
LIBS = -lm

_DEPS = event.h simulation.h vm.h common.h lcgrand.h simdata.h config.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = event.o vm.o simulation.o common.o lcgrand.o simdata.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

all: dir $(ODIR)/sim

dir:
	mkdir -p $(ODIR)

$(ODIR)/sim: $(OBJ)
	$(CC) $(LIBS) -I$(IDIR) -o $@ $^ $(SDIR)/main.cpp $(PROFILE)

clean:
	rm -rf $(ODIR) *~ $(INCDIR)/*~

distclean: clean
	rm -f results/*.txt
	rm -f results/*.pdf

plot:
	cd results && gnuplot service_time_plot.p

.PHONY: clean
