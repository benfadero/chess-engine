#include "Rook.h"

using namespace std;

Rook::Rook(Colour _colour,
	   string _name,
	   string _currentPosition) : ChessPiece(_colour,
						 _name,
						 _currentPosition)
{ }

void Rook::calculateAllowedMoves(string position)
{
  // If there is a vector, delete it
  if (allowedMoves.size() > 0)
    allowedMoves.clear();
  
  const char startFile = position.front();
  const char startRank = position.back();
  
  // Add possible vertical moves
  for (char endRank = MIN_RANK; endRank <= MAX_RANK; endRank++)
    {
      string move = string() + startFile + endRank;
      if (::positionIsValid(move) && move.compare(position))
	allowedMoves.push_back(move);
    }
  
  // Add possible horizontal moves
  for (char endFile = MIN_FILE; endFile <= MAX_FILE; endFile++)
    {
      string move = string() + endFile + startRank;
      if (::positionIsValid(move) && move.compare(position))
	allowedMoves.push_back(move);
    }
}
