#include "Bishop.h"

bool Bishop::isValidMove(const float newX, const float newY)
{
	float oldX = this->getX();
	float oldY = this->getY();
	// Accuracy variable
	float epsilon = 0.1f;
	// Distance between the two pairs of coordinates 
	float distance = sqrt(pow(oldX - newX, 2) + pow(oldY - newY, 2));

	// Checks if diagonal movement in either 4 directions is valid
	return abs(newX - (oldX + (distance / sqrt(2)))) < epsilon && abs(newY - (oldY + (distance / sqrt(2)))) < epsilon ||
		abs(newX - (oldX - (distance / sqrt(2)))) < epsilon && abs(newY - (oldY - (distance / sqrt(2)))) < epsilon ||
		abs(newX - (oldX + (distance / sqrt(2)))) < epsilon && abs(newY - (oldY - (distance / sqrt(2)))) < epsilon ||
		abs(newX - (oldX - (distance / sqrt(2)))) < epsilon && abs(newY - (oldY + (distance / sqrt(2)))) < epsilon;
}