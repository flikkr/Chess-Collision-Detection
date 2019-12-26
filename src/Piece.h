#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility>
#include <string>

using namespace std;

class Piece
{
public:
	// Identifies the shape of the piece
	enum class Shape { None, Circle, Square };
	// Identifies the type of the piece
	enum class Type { None, Rook, Bishop, Queen };

	const static int RADIUS = 1;
	const static int SIDE = 2;

	Piece() = default;

	/* Encapsulation */

	float getX() { return xPos; }
	void setX(float xPos) { this->xPos = xPos; }
	float getY() { return yPos; }
	void setY(float yPos) { this->yPos = yPos; }
	float getID() { return id; }
	void setID(int id) { this->id = id; }
	Shape shape = Shape::None;
	Type type = Type::None;

	/* Movement and collision */

	// Returns true if two pieces have collided
	bool hasCollided(Piece& other);
	// Moves pieces to new xy coordinates
	void move(const float newX, const float newY);
	// Checks that the move is valid for the type of piece
	virtual bool isValidMove(const float xPos, const float yPos) = 0;

	friend ostream& operator<<(ostream& outStream, const Piece& piece);
private:
	// Stores x position of piece
	float xPos = 0;
	// Stores y position of piece
	float yPos = 0;
	// Stores id for identification
	int id = 0;
};
