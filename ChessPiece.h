#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessHelper.h"

#include <iostream>
#include <map>
#include <vector>

class ChessPiece
{
 protected:
  Colour colour;
  std::string name, currentPosition;
  std::vector<std::string> allowedMoves;
  bool hasMoved;
  
 public:
  ChessPiece(Colour, std::string, std::string);
  std::string getPosition();
  std::string getColourString();
  std::string getName();
  Colour getColour();
  bool moveIsValid(std::string, std::string);
  virtual bool captureIsValid(std::string, std::string);
  virtual void calculateAllowedMoves(std::string) = 0;
  std::vector<std::string> getAllowedMoves();
  virtual std::vector<std::string> getAllowedCaptures();
  virtual void movePiece(std::string);
  virtual ~ChessPiece() = 0;
};
#endif
