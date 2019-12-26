#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include <vector>
#include <iostream>
#include <random>

class Game
{
	// Board dimensions
	const static int BOARD_HEIGHT = 50;
	const static int BOARD_WIDTH = 50;

public:
	// Creates new game board and populates it
	Game();
	// Runs the game for n number of moves
	void run(unsigned const int numOfMoves);
	// Prints all pieces currently in the game
	void printPieces();

	// Prints scoreboard
	friend ostream& operator<<(ostream& outStream, const Game& game);
private:
	// Stores pieces in the game
	vector<Piece*> pieces;
	// Used to track scores
	int rookScore;
	int bishopScore;
	int queenScore;
	// Checks whether coordinates result in piece going out of bounds
	bool isOutOfBounds(const float xPos, const float yPos);
	// Places pieces on the board and updates the quantity of pieces
	void placePiece(Piece& p, const float xPos, const float yPos);
	// Places piece on the board, updates the vector and sets the piece's x/y coordinate
	void movePiece(Piece& p, const float newX, const float newY);
	// Updates the pieces position for a given increment
	void updatePosition(Piece& p, const float xPos, const float yPos, const float increment);
	// Populates the board
	void populate();
	// Removes piece from the game
	void removePiece(Piece* p);
};
