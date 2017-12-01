#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
 public:
  King(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
};

#endif
