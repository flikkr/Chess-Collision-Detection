#pragma once
#include "Piece.h"

/*
	Restricted to diagonal movement
	Shape is circle
*/
class Bishop : public Piece
{
public:
	Bishop() : Piece() { this->shape = Shape::Circle; this->type = Type::Bishop; }
	bool isValidMove(const float newX, const float newY);
};
