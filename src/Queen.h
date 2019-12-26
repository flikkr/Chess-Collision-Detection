#pragma once
#include "Piece.h"

/*
	Restricted to diagonal and x/y axis movement
	Shape is circle
*/
class Queen : public Piece
{
public:
	Queen() : Piece() { this->shape = Shape::Circle; this->type = Type::Queen; }
	bool isValidMove(const float newX, const float newY);
};
