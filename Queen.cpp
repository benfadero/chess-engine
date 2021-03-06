#include "Queen.h"

using namespace std;

Queen::Queen(Colour _colour,
	     string _name,
	     string _currentPosition) : ChessPiece(_colour,
						   _name,
						   _currentPosition)
{ }

void Queen::calculateAllowedMoves(string position)
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
  
  // Add possible diagonally upward and leftward  moves
  for (char endFile = startFile - 1, endRank = startRank + 1;
       endFile >= MIN_FILE && endRank <= MAX_RANK;
       endFile--, endRank++)
    {
      string move = string() + endFile + endRank;
      if (::positionIsValid(move) && move.compare(position))
	allowedMoves.push_back(move);
    }

  // Add possible diagonally upward and rightward  moves
  for (char endFile = startFile + 1, endRank = startRank + 1;
       endFile <= MAX_FILE && endRank <= MAX_RANK;
       endFile++, endRank++)
    {
      string move = string() + endFile + endRank;
      if (::positionIsValid(move) && move.compare(position))
	  allowedMoves.push_back(move);
    }

  // Add possible diagonally downward and leftward  moves
  for (char endFile = startFile - 1, endRank = startRank - 1;
       endFile >= MIN_FILE && endRank >= MIN_RANK;
       endFile--, endRank--)
    {
      string move = string() + endFile + endRank;
      if (::positionIsValid(move) && move.compare(position))
	allowedMoves.push_back(move);
    }

  // Add possible diagonally downward and rightward  moves
  for (char endFile = startFile + 1, endRank = startRank - 1;
       endFile <= MAX_FILE && endRank >= MIN_RANK;
       endFile++, endRank--)
    {
      string move = string() + endFile + endRank;
      if (::positionIsValid(move) && move.compare(position))
	  allowedMoves.push_back(move);
    }
}
