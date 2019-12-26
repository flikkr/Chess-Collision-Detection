#include "Rook.h"

bool Rook::isValidMove(const float newX, const float newY)
{
	float oldX = this->getX();
	float oldY = this->getY();

	// If x is the same or y is the same
	return oldX == newX && oldY != newY || oldY == newY && oldX != newX;
}