#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
//#include <iostream>
//#include <string>

class Pawn: public ChessPiece
{
 private:
  std::vector<std::string> allowedCaptureMoves;
 public:
  Pawn(Colour, std::string, std::string);
  void calculateAllowedMoves(std::string);
  void movePiece(std::string);
  bool captureIsValid(std::string, std::string);
  std::vector<std::string> getAllowedCaptures();
};

#endif
