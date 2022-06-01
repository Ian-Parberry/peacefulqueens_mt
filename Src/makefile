SRC = Task.cpp Task.h ThreadManager.cpp ThreadManager.h Backtrack.cpp Backtrack.h Main.cpp
EXE = peacefulqueens_mt
INC = ../../thread++/Src
LIB = ../../thread++/Src/threadplusplus.a

all: $(SRC) $(EXE)

$(EXE): $(SRC)
	g++ -std=c++0x -o $(EXE) -O3 -ffast-math -I $(INC) $(SRC) $(LIB) -lpthread
