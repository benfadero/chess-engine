#include "Knight.h"

using namespace std;

Knight::Knight(Colour _colour,
	       string _name,
	       string _currentPosition) : ChessPiece(_colour,
						     _name,
						     _currentPosition)
{ }

void Knight::calculateAllowedMoves(string position)
{
  // If there is a vector, delete it
  if (allowedMoves.size() > 0)
    allowedMoves.clear();
  
  const char startFile = position.front();
  const char startRank = position.back();
  const int numMoves = 8;
  
  // Define all possible files and ranks
  char endFileL1 = startFile - 1;
  char endFileR1 = startFile + 1;
  char endFileL2 = startFile - 2;
  char endFileR2 = startFile + 2;
  char endRankU1 = startRank + 1;
  char endRankD1 = startRank - 1;
  char endRankU2 = startRank + 2;
  char endRankD2 = startRank - 2;

  // Define all possible moves
  string moves[numMoves];
  moves[0] = string() + endFileL1 + endRankU2;
  moves[1] = string() + endFileR1 + endRankU2;
  moves[2] = string() + endFileL1 + endRankD2;
  moves[3] = string() + endFileR1 + endRankD2;
  moves[4] = string() + endFileL2 + endRankU1;
  moves[5] = string() + endFileL2 + endRankD1;
  moves[6] = string() + endFileR2 + endRankU1;
  moves[7] = string() + endFileR2 + endRankD1;
  
  for (int i = 0; i < numMoves; i++)
    {
      if (::positionIsValid(moves[i]))
	{
	  allowedMoves.push_back(moves[i]);
	}
    }
}
