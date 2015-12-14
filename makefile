DEBUG=yes
ifeq ($(DEBUG),yes)
	CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g
else
	CXXFLAGS=-std=c++11 -march=native -O2
endif

LDFLAGS=-lIceE -lIceEC #-lIceUtil #-lIceStorm -pthread -lvlc
CXX= g++
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDE_DIR=Ice/
INCLUDE=include/
LIB_DIR=Ice/libIce/
BIN_DIR=bin/

SRC=$(wildcard $(SRC_DIR)*.cpp)
SRC_BIS=$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC))
OBJ=$(SRC_BIS:.cpp=.o)

EXE=$(BIN_DIR)exe

all: $(EXE)

slice: interface.ice
	slice2cpp $< && mv interface.cpp $(SRC_DIR) && mv interface.h $(INCLUDE)

$(EXE): $(OBJ) main.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR)  -L $(LIB_DIR) $^ $(LDFLAGS) -o $@ 

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCLUDE)%.h
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

.PHONY: clean mrproper

clean:
	rm -f $(OBJ_DIR)*.o

mrproper: clean
	rm -f $(EXE)


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.
