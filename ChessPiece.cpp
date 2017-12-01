#include "ChessPiece.h"

using namespace std;

ChessPiece::ChessPiece(Colour _colour,
		       string _name,
		       string _currentPosition) : colour(_colour),
						  name(_name),
						  currentPosition(_currentPosition)
{
  hasMoved = false;
}

string ChessPiece::getPosition()
{
  return currentPosition;
}

string ChessPiece::getColourString()
{
  string colourString;
  
  if (colour == WHITE)
    {
      colourString = "White's";
      return colourString;
    }

  colourString = "Black's";
  return colourString;
}

string ChessPiece::getName()
{
  return name;
}
Colour ChessPiece::getColour()
{
  return colour;
}

bool ChessPiece::moveIsValid(string startPosition, string endPosition)
{
  calculateAllowedMoves(startPosition);
  
  for (int i = 0; i < (int) allowedMoves.size(); i++)
    if (endPosition.compare(allowedMoves[i]) == 0)
      return true;
  
  return false;
}

bool ChessPiece::captureIsValid(string startPosition, string endPosition)
{
  return moveIsValid(startPosition, endPosition);
}

vector<string> ChessPiece::getAllowedMoves()
{
  return allowedMoves;
}

vector<string> ChessPiece::getAllowedCaptures()
{
  return allowedMoves;
}

void ChessPiece::movePiece(string endPosition)
{
  // Update position
  currentPosition = endPosition;
  
  // Set hasMoved to true
  if (!hasMoved)
    hasMoved = true;
  
  // Clear vector of allowed moves
  if (allowedMoves.size())
    allowedMoves.clear();
}

ChessPiece::~ChessPiece()
{ }
