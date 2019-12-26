#include "Game.h"
using namespace std;

int main()
{
	Game g;

	g.printPieces();
	g.run(300);

	exit(0);
}

Game::Game()
{
	populate();

	this->rookScore = 0;
	this->bishopScore = 0;
	this->queenScore = 0;
}

void Game::run(unsigned const int numOfMoves)
{
	cout << "\nThe game has begun!" << endl;

	// Avoids pseudorandomness
	random_device rd;
	mt19937 gen(rd());

	for (unsigned int i = 0; i < numOfMoves; i++)
	{
		// Checks if there's only one piece left on the board
		if (pieces.size() == 1) break;

		cout << "\n\nMove " << i + 1 << ": \t";

		// Select each piece sequentially so each one gets a turn
		Piece* p = pieces[i % pieces.size()];
		Piece::Type type = p->type;

		float xPos = -1;
		float yPos = -1;

		// Exits loop once valid coordinates have been chosen
		while (isOutOfBounds(xPos, yPos))
		{
			xPos = p->getX();
			yPos = p->getY();

			// Generates possible moves for rook
			if (type == Piece::Type::Rook)
			{
				// Choose which x or y axis to move on
				uniform_int_distribution<> choiceAxis(1, 2);
				// Generate random coordinate
				uniform_int_distribution<> xy_rand(1, BOARD_WIDTH - 1);

				float distanceToMove = (float)xy_rand(gen);
				int choice = choiceAxis(gen);

				// x axis movement
				if (choice == 1)
					xPos = distanceToMove;
				// y axis movement
				else
					yPos = distanceToMove;
			}
			// Generates possible moves for bishop
			else if (type == Piece::Type::Bishop)
			{
				// Choose which diagonal direction to move on
				uniform_int_distribution<> choiceDiagonal(1, 4);
				// Generate random coordinate
				uniform_int_distribution<> xy_rand(1, BOARD_WIDTH - 1);

				float distanceToMove = (float)xy_rand(gen);
				int choice = choiceDiagonal(gen);

				// Move down and right
				if (choice == 1)
				{
					xPos += distanceToMove;
					yPos += distanceToMove;
				}
				// Move up and left
				else if (choice == 2)
				{
					xPos -= distanceToMove;
					yPos -= distanceToMove;
				}
				// Move up and right
				else if (choice == 3)
				{
					xPos += distanceToMove;
					yPos -= distanceToMove;
				}
				// Move down and left
				else
				{
					xPos -= distanceToMove;
					yPos += distanceToMove;
				}
			}
			// Generates possible moves for queen
			else
			{
				// Choose which x, y axis or diagonal direction to move on
				uniform_int_distribution<> choiceXYDiagonal(1, 6);
				// Generate random coordinate
				uniform_int_distribution<> xy_rand(1, BOARD_WIDTH - 1);

				float distanceToMove = (float)xy_rand(gen);
				int choice = choiceXYDiagonal(gen);

				// x axis movement
				if (choice == 1)
				{
					xPos = distanceToMove;
				}
				// y axis movement
				else if (choice == 2)
				{
					yPos = distanceToMove;
				}
				// Move down and right
				if (choice == 3)
				{
					xPos += distanceToMove;
					yPos += distanceToMove;
				}
				// Move up and left
				else if (choice == 4)
				{
					xPos -= distanceToMove;
					yPos -= distanceToMove;
				}
				// Move up and right
				else if (choice == 5)
				{
					xPos += distanceToMove;
					yPos -= distanceToMove;
				}
				// Move down and left
				else
				{
					xPos -= distanceToMove;
					yPos += distanceToMove;
				}
			}

			/*if (isOutOfBounds(xPos, yPos)) continue;

			break;*/
		}

		// New coordinates
		cout << *p << " to (x:" << xPos << ",y:" << yPos << ")";

		try
		{
			movePiece(*p, xPos, yPos);
		}
		// If out of bounds (should never happen, but out of precaution)
		catch (invalid_argument e)
		{
			continue;
		}
	}

	// Print scoreboard
	cout << "\n\nThe game has ended.\n" << *this << endl;
}

void Game::placePiece(Piece& p, const float xPos, const float yPos)
{
	// Checks that pieces are not placed out of bounds
	if (isOutOfBounds(xPos, yPos))
		throw invalid_argument("Cannot place piece out of bounds");

	p.setX(xPos);
	p.setY(yPos);
	p.setID(pieces.size());

	// Add to vector of pieces
	pieces.push_back(&p);
}

void Game::removePiece(Piece* p)
{
	// Looks for piece p
	vector<Piece*>::iterator it = find(pieces.begin(), pieces.end(), p);

	// Delete if found
	if (it != pieces.end())
	{
		this->pieces.erase(it);
		delete p;
	}
}

void Game::printPieces()
{
	// Print all pieces
	for (unsigned int i = 0; i < pieces.size(); i++) 
	{	
		cout << "Piece " << i + 1 << ": " << *pieces[i] << endl;
	}
}

void Game::movePiece(Piece& p, const float newX, const float newY)
{
	// Checks that pieces are not moved out of bounds
	if (isOutOfBounds(newX, newY))
		throw invalid_argument("Cannot place piece out of bounds");

	// Increment used when moving piece
	const float increment = 0.1f;
	// Used for accuracy
	const float epsilon = 0.01f;

	// Checks that the piece has reached its x, y destination
	bool hasReachedXDestination = abs(p.getX() - newX) < epsilon;
	bool hasReachedYDestination = abs(p.getY() - newY) < epsilon;

	if (p.isValidMove(newX, newY))
	{
		while (!hasReachedXDestination || !hasReachedYDestination)
		{
			// Update position in given direction using given increment
			updatePosition(p, newX, newY, increment);

			// Update for next loop to see if piece has reached destination
			hasReachedXDestination = abs(p.getX() - newX) < epsilon;
			hasReachedYDestination = abs(p.getY() - newY) < epsilon;

			// Check collision
			for (unsigned int i = 0; i < pieces.size(); i++)
			{
				// If collision is detected, remove piece and add 1 to score
				if (p.hasCollided(*pieces[i]) && &p != pieces[i])
				{
					cout << "\n--------------------------------------------------------------------------------------------" << endl;
					cout << "CAPTURE! \t" << p << " has captured piece " << *pieces[i] << "!";
					cout << "\n--------------------------------------------------------------------------------------------" << endl;

					removePiece(pieces[i]);

					// Attribute point to correct piece type
					if (p.type == Piece::Type::Bishop)
						bishopScore += 1;
					else if (p.type == Piece::Type::Queen)
						queenScore += 1;
					else
						rookScore += 1;

					return;
				}
			}
		}
	}
}

bool Game::isOutOfBounds(const float xPos, const float yPos)
{
	// Checks that x and y are not outside boundaries
	if (xPos < 1.0f || xPos > (BOARD_WIDTH - 1) || yPos < 1.0f || yPos > (BOARD_HEIGHT - 1))
	{
		return true;
	}

	return false;
}

void Game::updatePosition(Piece& p, const float newX, const float newY, const float increment)
{
	float oldX = p.getX();
	float oldY = p.getY();
	float diagonalIncrement = (float)(0.1f / sqrt(2));

	// Moving right
	if (oldX < newX && oldY == newY)
		p.move(oldX + increment, oldY);
	// Moving left
	else if (oldX > newX&& oldY == newY)
		p.move(oldX - increment, oldY);
	// Moving down
	else if (oldX == newX && oldY < newY)
		p.move(oldX, oldY + increment);
	// Moving up
	else if (oldX == newX && oldY > newY)
		p.move(oldX, oldY - increment);
	// Move up and right
	else if (oldX < newX && oldY > newY)
		p.move(oldX + diagonalIncrement, oldY - diagonalIncrement);
	// Move down and right
	else if (oldX < newX && oldY < newY)
		p.move(oldX + diagonalIncrement, oldY + diagonalIncrement);
	// Move down and left
	else if (oldX > newX&& oldY < newY)
		p.move(oldX - diagonalIncrement, oldY + diagonalIncrement);
	// Move up and left
	else if (oldX > newX&& oldY > newY)
		p.move(oldX - diagonalIncrement, oldY - diagonalIncrement);
	else
		throw "Shouldn't happen";
}

void Game::populate()
{
	// Quantity of pieces to populate
	const int quantity = 50;
	int startX = 5;
	int startY = 5;
	bool firstLoop = true;

	cout << "/----------------- Pieces -----------------/" << endl;

	for (unsigned int i = 0; i < quantity; i++)
	{
		// Avoids pseudorandomness
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(1, 3);

		Piece* p;

		// Generates random piece
		if (dis(gen) == 1)
		{
			p = new Rook();
		}
		else if (dis(gen) == 2)
		{
			p = new Bishop();
		}
		else
		{
			p = new Queen();
		}

		// Places pieces line by line on x axis first, then move up y axis and repeat
		try
		{
			placePiece(*p, (float)(startX % BOARD_WIDTH), (float)(startY % BOARD_WIDTH));
		}
		catch (invalid_argument e)
		{
			cout << "Piece " << p << " couldn't be placed" << endl;
			continue;
		}

		startX += 10;


		if (firstLoop)
		{
			firstLoop = false;
			continue;
		}

		if (startX % BOARD_WIDTH == 5)
			startY += 10;
	}
}

ostream& operator<<(ostream& outStream, const Game& game)
{
	// Prints scoreboard of game
	outStream << "\n/----------------- Results -----------------/"
			<< "\n\tRook score: \t" << game.rookScore 
			<< "\n\tBishop score: \t" << game.bishopScore
			<< "\n\tQueen score: \t" << game.queenScore
			<< "\n/-------------------------------------------/" << endl;
	return outStream;
}