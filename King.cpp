#include "King.h"

using namespace std;

King::King(Colour _colour,
	   string _name,
	   string _currentPosition) : ChessPiece(_colour,
						 _name,
						 _currentPosition)
{ }

void King::calculateAllowedMoves(string position)
{
  // If there is a vector, delete it
  if (allowedMoves.size() > 0)
    allowedMoves.clear(); 

  const char startFile = position.front();
  const char startRank = position.back();

  // Add possible moves in all directions
  for (char endFile = startFile - 1; endFile <= startFile + 1; endFile++)
    for (char endRank = startRank - 1; endRank <= startRank + 1; endRank++)
      {
	string move = string() + endFile + endRank;
	if (::positionIsValid(move) && move.compare(position))
	  allowedMoves.push_back(move);
      }
}
