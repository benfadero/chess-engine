#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen: public ChessPiece {
 public:
  Queen(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
};

#endif
