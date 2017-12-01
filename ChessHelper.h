/* Contains general (i.e. not classic-specific) helper 
functions, as well as constants and enums in the global namespace */

#ifndef HELPER_H
#define HELPER_H

#include <iostream>

#define MIN_FILE ((unsigned char) 'A')
#define MIN_RANK ((unsigned char) '1')
#define MAX_FILE ((unsigned char) 'H')
#define MAX_RANK ((unsigned char) '8')

enum Colour{WHITE, BLACK};
enum Turn{WHITES_TURN, BLACKS_TURN};
enum MoveDirection{DIR_ERROR,
		   VERT_UP, VERT_DOWN, HOR_LEFT, HOR_RIGHT,
		   DIAG_UP_LEFT, DIAG_UP_RIGHT,
		   DIAG_DOWN_LEFT, DIAG_DOWN_RIGHT};



bool positionIsValid(std::string); // Returns true if input is valid format and in
// valid range

#endif
