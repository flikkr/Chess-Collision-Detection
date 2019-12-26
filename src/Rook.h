#pragma once
#include "Piece.h"

/*
	Restricted to x/y axis movement
	Shape is square
*/
class Rook : public Piece
{
public:
	Rook() : Piece() { this->shape = Shape::Square; this->type = Type::Rook; }
	bool isValidMove(const float newX, const float newY);
};
