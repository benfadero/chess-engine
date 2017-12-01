#include "ChessBoard.h"

using namespace std;

ChessBoard::ChessBoard()
{
  initialiseBoard();
}

void ChessBoard::initialiseBoard()
{
  playerTurn = WHITES_TURN;
  
  // Initialise white pieces
  board.insert({"A1", new Rook(WHITE, "Rook", "A1")});
  board.insert({"B1", new Knight(WHITE, "Knight", "B1")});
  board.insert({"C1", new Bishop(WHITE, "Bishop", "C1")});
  board.insert({"D1", new Queen(WHITE, "Queen", "D1")});
  board.insert({"E1", new King(WHITE, "King", "E1")});
  board.insert({"F1", new Bishop(WHITE, "Bishop", "F1")});
  board.insert({"G1", new Knight(WHITE, "Knight", "G1")});
  board.insert({"H1", new Rook(WHITE, "Rook", "H1")});
  
  char whitePawnRank = '2';
  for (char file = MIN_FILE; file <= MAX_FILE; file++)
    {
      string position = string() + file + whitePawnRank;
      board.insert({position, new Pawn(WHITE, "Pawn", position)});
    }

  // Initialise black pieces
  board.insert({"A8", new Rook(BLACK, "Rook", "A8")});
  board.insert({"B8", new Knight(BLACK, "Knight", "B8")});
  board.insert({"C8", new Bishop(BLACK, "Bishop", "C8")});
  board.insert({"D8", new Queen(BLACK, "Queen", "D8")});
  board.insert({"E8", new King(BLACK, "King", "E8")});
  board.insert({"F8", new Bishop(BLACK, "Bishop", "F8")});
  board.insert({"G8", new Knight(BLACK, "Knight", "G8")});
  board.insert({"H8", new Rook(BLACK, "Rook", "H8")});
  
  char blackPawnRank = '7';
  for (char file = MIN_FILE; file <= MAX_FILE; file++)
    {
      string position = string() + file + blackPawnRank;
      board.insert({position, new Pawn(BLACK, "Pawn", position)});
    }
}

void ChessBoard::deleteBoard()
{
  for (Board::iterator it = board.begin(); it != board.end(); it++) 
    {
      delete it->second;
    }

  board.clear();
}

void ChessBoard::switchTurn()
{
  if (playerTurn == WHITES_TURN)
    {
      playerTurn = BLACKS_TURN;
      return;
    }

  if (playerTurn == BLACKS_TURN)
    {
      playerTurn = WHITES_TURN;
      return;
    }
}

MoveDirection ChessBoard::findMoveDirection(string startPosition, string endPosition)
{
  char startFile = startPosition.front();
  char startRank = startPosition.back();
  char endFile = endPosition.front();
  char endRank = endPosition.back();

  // Find direction of submitted move

  // Try vertical
  if (startFile == endFile)
    {
      // Try upwards
      if (endRank > startRank)
	return VERT_UP;

      // Try downwards
      else if (endRank < startRank)
	return VERT_DOWN;
    }

  // Try horizontal
  if (startRank == endRank)
    {
      // Try left
      if (endFile < startFile)
	return HOR_LEFT;

      // Try right
      else if (endFile > startFile)
	return HOR_RIGHT;
    }

  // Try diagonal up
  if (startFile != endFile && endRank > startRank)
    {
      // Try diagonal up and left
      if (endFile < startFile)
	return DIAG_UP_LEFT;

      // Try diagonal up and right
      else if (endFile > startFile)
        return  DIAG_UP_RIGHT;
    }

  // Try diagonal down
  if (startFile != endFile && endRank < startRank)
    {
      // Try diagonal down and left
      if (endFile < startFile)
	return DIAG_DOWN_LEFT;

      // Try diagonal down and right
      else if (endFile > startFile)
	return DIAG_DOWN_RIGHT;
    }

  // Error
  return DIR_ERROR;
}

bool ChessBoard::pieceInWay(ChessPiece *piece, string endPosition,
			    MoveDirection moveDir)
{
  // If the piece is a knight or king (since kings can only ever move 1 space),
  // return false
  if (!piece->getName().compare("Knight") ||
      !piece->getName().compare("King"))
    return false;

  string startPosition = piece->getPosition();

  char startFile = startPosition.front();
  char startRank = startPosition.back();
  char endFile = endPosition.front();
  char endRank = endPosition.back();

  switch (moveDir)
    {
    case VERT_UP:
      for (char rank = startRank + 1; rank < endRank; rank++)
	if (pieceAtFileAndRank(startFile, rank))
	  return true;
      break;
      
    case VERT_DOWN:
      for (char rank = startRank - 1; rank > endRank; rank--)
	if (pieceAtFileAndRank(startFile, rank))
	  return true;
          
    case HOR_LEFT:
      for (char file = startFile - 1; file > endFile; file--)
	if (pieceAtFileAndRank(file, startRank))
	    return true;
      
    case HOR_RIGHT:
      for (char file = startFile + 1; file < endFile; file++)
	if (pieceAtFileAndRank(file, startRank))
	  return true;
            
    case DIAG_UP_LEFT:
      for (char file = startFile - 1, rank = startRank + 1;
	   file > endFile && rank < endRank;
	   file--, rank++)
	if (pieceAtFileAndRank(file, rank))
	  return true;
            
    case DIAG_UP_RIGHT:
      for (char file = startFile + 1, rank = startRank + 1;
	   file < endFile && rank < endRank;
	   file++, rank++)
	if (pieceAtFileAndRank(file, rank))
	  return true;
      
    case DIAG_DOWN_LEFT:
      for (char file = startFile - 1, rank = startRank - 1;
	   file > endFile && rank > endRank;
	   file--, rank--)
	if (pieceAtFileAndRank(file, rank))
	  return true;

    case DIAG_DOWN_RIGHT:
      for (char file = startFile + 1, rank = startRank - 1;
	   file < endFile && rank > endRank;
	   file++, rank--)
	if (pieceAtFileAndRank(file, rank))
	  return true;

    case DIR_ERROR:
      return false;
    }

  return false;
}

bool ChessBoard::pieceAtFileAndRank(const char file, const char rank)
{
  string position = string() + file + rank;
  if (board.count(position))
    return true;

  return false;
}

void ChessBoard::movePiece(ChessPiece *piece, string endPosition)
{
  string startPosition = piece->getPosition();
  
  // Update current position of piece
  piece->movePiece(endPosition);
  
  // Copy piece to new position and delete piece at old position
  board.insert({endPosition, piece});
  board.erase(startPosition);
}

void ChessBoard::capturePiece(ChessPiece *sourcePiece, ChessPiece *destPiece)
{
  string startPosition = sourcePiece->getPosition();
  string endPosition = destPiece->getPosition();

  // Delete piece at destination position
  //  delete destPiece;
  board.erase(endPosition);

  // Move piece to destination
  movePiece(sourcePiece, endPosition);
}

Colour ChessBoard::getOppColour(Colour playerColour)
{
  if (playerColour == WHITE)
    return BLACK;

  else
    return WHITE;
}

string ChessBoard::getKingPosition(Colour pieceColour)
{
  // Iterate through board
  for (Board::iterator it = board.begin(); it != board.end(); it++) 
      if (!it->second->getName().compare("King")
	  && it->second->getColour() == pieceColour)
	return it->first;

  return "";
}

bool ChessBoard::evaluateCheck(Colour playerColour)
{
  string kingPos = getKingPosition(playerColour);
  Colour oppColour = getOppColour(playerColour);
    
  for (Board::iterator it = board.begin(); it != board.end(); it++) 
    {
      // If black piece can move to white king
      ChessPiece *piece = it->second;
      string piecePosition = it->first;
      MoveDirection moveDir = findMoveDirection(piecePosition, kingPos);
      if (it->second->getColour() == oppColour
	  && piece->moveIsValid(piecePosition, kingPos)
	  && !pieceInWay(piece, kingPos, moveDir))
	return true;
    }

  return false;
}

bool ChessBoard::tryMoveAndEvaluateCheck(Colour playerColour, string startPosition,
					 string endPosition)
{
  ChessPiece *sourcePiece, *destPiece;
  Board boardCopy = board;
  
  if (board.count(startPosition))
    sourcePiece = board.at(startPosition);
  
  if (board.count(endPosition))
    destPiece = board.at(endPosition);

  // If no piece at end position, try move
  if (!board.count(endPosition))
    {
      movePiece(sourcePiece, endPosition);
      // If in check after move, reset board
      // to previous state and return true
      if (evaluateCheck(playerColour))
	{
	  board.at(endPosition)->movePiece(startPosition);
	  board = boardCopy;
	  return true;
	}
    }
  
  else if (board.count(endPosition))
    {
      capturePiece(sourcePiece, destPiece);
      
      if (evaluateCheck(playerColour))
	{
	  board.at(endPosition)->movePiece(startPosition);
	  board = boardCopy;
	  return true;
	}
    }

  board.at(endPosition)->movePiece(startPosition);
  board = boardCopy;
  boardCopy.clear();  
  return false;
}

bool ChessBoard::evaluateStalemate(Colour playerColour)
{
  // Try every move; if there is a move that does not result in check
  // then return false.

  for (char file = MIN_FILE; file <= MAX_FILE; file++)
    for (char rank = MIN_RANK; rank <= MAX_RANK; rank++)
      {
	string testPosition = string() + file + rank;
	if (board.count(testPosition))
	  {
	    ChessPiece *piece = board.at(testPosition);

	    // For non-pawn pieces 
	    if( piece->getColour() == playerColour && piece->getName().compare("Pawn"))
	      {
		piece->calculateAllowedMoves(piece->getPosition());
		int length = (int) piece->getAllowedMoves().size();
		
		for (int i = 0; i < length; i++)
		  {
		    piece->calculateAllowedMoves(piece->getPosition());
		    string startPosition = piece->getPosition();
		    string endPosition = piece->getAllowedMoves()[i];

		    if (canMakeMove(startPosition, endPosition))
		      {
			if (!tryMoveAndEvaluateCheck(playerColour, startPosition, endPosition))
			  return false;
		      }
		  }
	      }
	    // For pawns
	    else if (piece->getColour() == playerColour && !piece->getName().compare("Pawn"))
	      {
		piece->calculateAllowedMoves(piece->getPosition());
		int length = (int) piece->getAllowedCaptures().size();
		
		for (int i = 0; i < length; i++)
		  {
		    piece->calculateAllowedMoves(piece->getPosition());
		    string startPosition = piece->getPosition();
		    string endPosition = piece->getAllowedCaptures()[i];

		    if (canMakeMove(startPosition, endPosition))
		      {
			if (!tryMoveAndEvaluateCheck(playerColour, startPosition, endPosition))
			  return false;
		      }
		  }
	      }
	  }
	
      }
  
  return true;
}

bool ChessBoard::evaluateCheckmate(Colour playerColour)
{
  if (evaluateCheck(playerColour) && evaluateStalemate(playerColour))
    return true;

  return false;
}

bool ChessBoard::canMakeMove(string startPosition, string endPosition)
{
  // Declare pointer for piece at starting position, and corresponding variables
  ChessPiece *piece;
  Colour pieceColour;
  bool moveValidForPiece, captureValidForPiece;
  string pieceColourString, pieceName;
  
  // Declare pointer for piece at end position
  ChessPiece *pieceAtEndPosition;
  MoveDirection movDir = findMoveDirection(startPosition, endPosition);    

  // If there is a piece at start position, assign
  // piece pointer to it and set variables
  if (board.count(startPosition))
    {
      piece = board.at(startPosition);
      pieceColour = piece->getColour();
      moveValidForPiece = piece->moveIsValid(startPosition,
					     endPosition);
      captureValidForPiece = piece->captureIsValid(startPosition,
						   endPosition);
      pieceColourString = piece->getColourString();
      pieceName = piece->getName();
    }
  
  // If there is a piece at end position, and it is a king, or the
  // same colour as piece at start position, the piece cannot move. 
  if (board.count(endPosition))
    {
      pieceAtEndPosition = board.at(endPosition);
      
      if(pieceColour == pieceAtEndPosition->getColour()
	 || !piece->getName().compare("King"))
	 return false;
    }
  
  // Check if submitted move is invalid
  if ((!moveValidForPiece && !captureValidForPiece)
      || !::positionIsValid(endPosition))
    return false;
    
  // Check if a pawn tries to capture vertically
  if (moveValidForPiece && !captureValidForPiece
      && board.count(endPosition))
    return false;
     
  // Or if a pawn tries to capture nothing
  if (!moveValidForPiece && captureValidForPiece
      && !board.count(endPosition))
    return false;
    
  // Check if there is a piece in the way of the submitted move
  if (pieceInWay(piece, endPosition, movDir))
    return false;

  return true;
}

void ChessBoard::submitMove(string startPosition, string endPosition)
{
  // Declare pointer for piece at starting position, and corresponding variables
  ChessPiece *piece;
  Colour pieceColour, oppColour;
  string pieceColourString, pieceName;
  
  // Check whether input positions are valid 
  if (!::positionIsValid(startPosition))
    {
      cout << startPosition << " is not a valid position!" << endl;
      return;
    }

  if (!::positionIsValid(endPosition))
    {
      cout << endPosition << " is not a valid position!" << endl;
      return;
    }

  // Check whether there is a piece at start position
  if (!board.count(startPosition))
    {
      cout << "There is no piece at position " << startPosition;
      cout << "!" << endl;
      return;
    }

  // If there is, assign pointer to it and set variables
  else 
    {
      piece = board.at(startPosition);
      pieceColour = piece->getColour();
      oppColour = getOppColour(pieceColour);
      pieceColourString = piece->getColourString();
      pieceName = piece->getName();
    }

  // Check move is possible
  if (!canMakeMove(startPosition, endPosition))
    {
      cout << pieceColourString << " " << pieceName;
      cout << " cannot move to " << endPosition << "!" << endl;
      
      return;
    }

  // Check whether it is valid for current player to move piece
  if (pieceColour != (Colour) playerTurn)
    {
      if (playerTurn == WHITES_TURN)
	{
	  cout << "It is not Black's turn to move!" << endl;
	  return;
	}

      else
	{
	  cout << "It is not White's turn to move!" << endl;
	  return;
	}
    }
    
  // If there is piece at the end position, capture it
  if (board.count(endPosition))
    {
      ChessPiece *pieceAtEndPosition = board.at(endPosition);
      
      if (tryMoveAndEvaluateCheck(pieceColour, startPosition,
			     endPosition))
	{
	  if (evaluateCheck(pieceColour))
	    {
	      cout << "Invalid move: player is still in check";
	      cout << endl;
	      return;
	    }

	  else
	    {
	      cout << "Invalid move: leads to player being in check";
	      cout << endl;
	      return;
	    }
	}
      
      cout << pieceColourString << " " << pieceName;
      cout << " moves from " << startPosition << " to ";
      cout << endPosition << " taking ";
      cout << pieceAtEndPosition->getColourString() << " ";
      cout << pieceAtEndPosition->getName() << endl;

      capturePiece(piece, pieceAtEndPosition);
    }
  
  // Else if there is no piece at end position,
  // move the piece normally
  else
    {
      if (tryMoveAndEvaluateCheck(pieceColour, startPosition,
			     endPosition))
	{
	  if (evaluateCheck(pieceColour))
	    {
	      cout << "Invalid move: player is still in check";
	      cout << endl;
	      return;
	    }

	  else
	    {
	      cout << "Invalid move: leads to player being in check";
	      cout << endl;
	      return;
	    }
	}
      
      cout << piece->getColourString() << " " << piece->getName();
      cout << " moves from " << startPosition << " to ";
      cout << endPosition << endl;
      
      movePiece(piece, endPosition);
    }

  if (evaluateStalemate(oppColour) && !evaluateCheckmate(oppColour))
    {
      cout << "Stalemate reached." << endl;
    }
 

  if (evaluateCheckmate(oppColour))
    {
      if (playerTurn == WHITES_TURN)
	cout << "Black is in checkmate" << endl;
      else
	cout << "White is in checkmate" << endl;
      return;
    }
  
  if (evaluateCheck(oppColour))
    {
      if (playerTurn == WHITES_TURN)
	cout << "Black is in check" << endl;
      else 
	cout << "White is in check" << endl;
    }
  
  switchTurn();
  return;
}

void ChessBoard::resetBoard()
{
  cout << "A new chess game is started!" << endl;

  deleteBoard();
  initialiseBoard();
}

ChessBoard::~ChessBoard()
{
  deleteBoard();
}
