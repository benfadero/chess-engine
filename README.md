# chess-engine
This is program developed during the first term of my studies at Imperial College London. It is an engine for simulating chess games.

**ChessMain.cpp** (the file in which the main function is defined) contains a simple test, followed by a simulation of a game played between Alekhine and Vasic in 1931. 

Games can be simulated by first calling the **resetBoard()** method on the **cb** object (of type **ChessBoard**), followed by submitting moves by calling **cb.submitMove(std::string startPosition, std::string endPosition)**, where the two arguments are the start and end positions of the intended move, respectively, given as chess board coordinates.
