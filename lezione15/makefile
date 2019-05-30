POISSON_OBJ  = poisson.o ode.o root_finders.o
WAVE_OBJ  = wave.o ode.o root_finders.o

CXX     = g++
CFLAGS  = -c
SRC     = /opt/project/lib
VPATH   = ./:$(SRC)
INCLUDE_DIRS = -I. -I$(SRC)
LDFLAGS = -lm

poisson:  $(POISSON_OBJ)
	$(CXX) $(POISSON_OBJ) $(LDFLAGS) -o $@

wave:  $(WAVE_OBJ)
	$(CXX) $(WAVE_OBJ) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<
