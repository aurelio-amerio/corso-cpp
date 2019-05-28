PENDULUM_OBJ  = pendulum.o ode.o

CXX     = g++
CFLAGS  = -c
SRC     = /opt/project/lib
VPATH   = ./:$(SRC)
INCLUDE_DIRS = -I. -I$(SRC)
LDFLAGS = -lm

pendulum:  $(PENDULUM_OBJ)
	$(CXX) $(PENDULUM_OBJ) $(LDFLAGS) -o $@
%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $<
