POISSON_OBJ  = poisson.o ode.o

CXX     = g++
CFLAGS  = -c
SRC     = /opt/project/lib
VPATH   = ./:$(SRC)
INCLUDE_DIRS = -I. -I$(SRC)
LDFLAGS = -lm

POISSON:  $(POISSON_OBJ)
	$(CXX) $(POISSON_OBJ) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<
