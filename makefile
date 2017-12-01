OBJ = ChessMain.o ChessBoard.o ChessPiece.o ChessHelper.o\
	King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o
EXE = chess

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -MMD

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)

.PHONY: clean
