#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop: public ChessPiece {
 public:
  Bishop(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
};

#endif
