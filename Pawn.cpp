#include "Pawn.h"

using namespace std;

Pawn::Pawn(Colour _colour,
	   string _name,
	   string _currentPosition) : ChessPiece(_colour,
						 _name,
						 _currentPosition)
{ }

void Pawn::calculateAllowedMoves(std::string position)
{
  if (allowedMoves.size() > 0)
    allowedMoves.clear(); 

  if (allowedCaptureMoves.size() > 0)
    allowedCaptureMoves.clear();
  
  const char startFile = position.front();
  const char startRank = position.back();

  // Add files for possible capture moves (same for both colours)
  char captureFile1 = startFile - 1;
  char captureFile2 = startFile + 1;
  
  // Add moves for white
  if (colour == WHITE)
    {
      // Allows moving forward 1 space
      char endRank1 = startRank + 1;
      string move1 = string() + startFile + endRank1;
      if (::positionIsValid(move1))
	allowedMoves.push_back(move1);
      
      // Add possible capture moves
      string captureMove1 = string() + captureFile1 + endRank1;
      string captureMove2 = string() + captureFile2 + endRank1;

      if (::positionIsValid(captureMove1))
	allowedCaptureMoves.push_back(captureMove1);

      if (::positionIsValid(captureMove2))
	allowedCaptureMoves.push_back(captureMove2);
      
      // Allows moving forward 2 spaces if piece has not yet moved
      if (hasMoved == false)
	{
	  char endRank2 = startRank + 2;
	  string move2 = string() + startFile + endRank2;
	  if (::positionIsValid(move2))
	    allowedMoves.push_back(move2);
	}
    }

  // Add moves for black
  if (colour == BLACK)
    {
      // Allows moving forward 1 space
      char endRank1 = startRank - 1;
      string move1 = string() + startFile + endRank1;
      if (::positionIsValid(move1))
	allowedMoves.push_back(move1);
      
      // Add possible capture moves
      string captureMove1 = string() + captureFile1 + endRank1;
      string captureMove2 = string() + captureFile2 + endRank1;
      
      if (::positionIsValid(captureMove1))
	allowedCaptureMoves.push_back(captureMove1);
      
      if (::positionIsValid(captureMove2))
	allowedCaptureMoves.push_back(captureMove2);
      
      // Allows moving forward 2 spaces if piece has not yet moved
      if (hasMoved == false)
	{
	  char endRank2 = startRank - 2;
	  string move2 = string() + startFile + endRank2;
	  if (::positionIsValid(move2))
	    allowedMoves.push_back(move2);
	}
    }
}

bool Pawn::captureIsValid(string startPosition, string endPosition)
{
  calculateAllowedMoves(startPosition);
  
  for (int i = 0; i < (int) allowedCaptureMoves.size(); i++)
    if (endPosition.compare(allowedCaptureMoves[i]) == 0)
      return true;

  return false;
}

void Pawn::movePiece(string endPosition)
{
  // Update position
  currentPosition = endPosition;

  // Set hasMoved to true
  if (!hasMoved)
    hasMoved = true;

  // Clear vectors of allowed moves
  allowedMoves.clear();
  allowedCaptureMoves.clear();
}

vector<string> Pawn::getAllowedCaptures()
{
  return allowedCaptureMoves;
}
