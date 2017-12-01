#include "ChessHelper.h"

using namespace std;

bool positionIsValid(string position)
{
  if (position.length() != 2)
    return false;
  
  if (position.front() < MIN_FILE || position.front() > MAX_FILE)
    return false;

  if (position.back() < MIN_RANK || position.back() > MAX_RANK)
    return false;

  return true;
}
