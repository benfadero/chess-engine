#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight: public ChessPiece {
 public:
  Knight(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
};

#endif
