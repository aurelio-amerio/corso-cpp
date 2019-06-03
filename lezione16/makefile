OSC_OBJ  = qho.o root_finders.o ode.o

CXX     = g++
CFLAGS  = -c
SRC     = /opt/project/lib
VPATH   = ./:$(SRC)
INCLUDE_DIRS = -I. -I$(SRC)
LDFLAGS = -lm

osc:  $(OSC_OBJ)
	$(CXX) $(OSC_OBJ) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<
