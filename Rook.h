#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook: public ChessPiece {
 public:
  Rook(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
};

#endif
