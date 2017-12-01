#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "ChessHelper.h"
#include <iostream>
#include <map>

typedef std::map<std::string, ChessPiece*> Board;

class ChessBoard
{
 private:
  Turn playerTurn;
  Board board;
  
  void initialiseBoard(); // Set up the board
  void deleteBoard(); // Deletes the board
  void switchTurn(); // Change which player is allowed to make a move
  MoveDirection findMoveDirection(std::string , std::string); // Helper function
  bool pieceInWay(ChessPiece*, std::string,  MoveDirection); // True if piece in way of move
  bool pieceAtFileAndRank(const char, const char); // True if piece at file and rank
  void movePiece(ChessPiece*, std::string); // Moves piece on board map
  void capturePiece(ChessPiece*, ChessPiece*); // Captures piece 
  Colour getOppColour(Colour); // Gets opponent's colour
  std::string getKingPosition(Colour);  // Get the position of the king for player
  bool evaluateCheck(Colour); // True if player is in check
  bool tryMoveAndEvaluateCheck(Colour, std::string, std::string); // Tries a move,
  // evaluates whether move leads to check, then returns the board to its previous state
  bool evaluateStalemate(Colour); // True if stalemate is reached
  bool evaluateCheckmate(Colour); // True if player is in checkmate
  bool canMakeMove(std::string, std::string); // True if move can be legally made
    
 public:
  ChessBoard();
  void submitMove(std::string, std::string); // Used to submit moves
  void resetBoard(); // Reset board to original state
  ~ChessBoard();
};

#endif
