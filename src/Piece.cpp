#include "Piece.h"

using namespace std;

bool Piece::hasCollided(Piece& other)
{
	/* 
		Circle/Circle collision

		This technique involves finding the distance between two circles and checking
		that the distance is never less than the sum of their radii. If it is, collision has occured
	*/
	if (this->shape == Shape::Circle && other.shape == Shape::Circle)
	{
		float distanceX = xPos - other.getX();
		float distanceY = yPos - other.getY();

		float radiiSum = RADIUS * 2;

		if (distanceX * distanceX + distanceY * distanceY < radiiSum * radiiSum)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	/* 
		Square/Square collision
		
		This technique involves checking each side of the square against the other square.
		It makes sense of the positioning of each of the two corner coordinates (upper left and lower right)
		of each square to determine whether there is a collision
	*/
	else if (this->shape == Shape::Square && other.shape == Shape::Square)
	{
		pair<float, float> thisUpperLeftCoordXY = make_pair(xPos - (SIDE / 2), yPos - (SIDE / 2));
		pair<float, float> thisLowerRightCoordXY = make_pair(xPos + (SIDE / 2), yPos + (SIDE / 2));

		pair<float, float> otherUpperLeftCoordXY = make_pair(other.getX() - (SIDE / 2), other.getY() - (SIDE / 2));
		pair<float, float> otherLowerRightCoordXY = make_pair(other.getX() + (SIDE / 2), other.getY() + (SIDE / 2));

			// A.x1 is to the left of B.x2
		if (thisUpperLeftCoordXY.first < otherLowerRightCoordXY.first &&
			// A.y1 is on top of B.y2
			thisUpperLeftCoordXY.second < otherLowerRightCoordXY.second &&
			// A.x2 is to the right of B.x1
			thisLowerRightCoordXY.first > otherUpperLeftCoordXY.first &&
			// A.y2 is on the bottom of B.y1
			thisLowerRightCoordXY.second > otherUpperLeftCoordXY.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	/* 
		Circle/Square collision
		Adapted from https://yal.cc/rectangle-circle-intersection-test/

		Similar to circle/circle collision, this technique involves finding the nearest point of the square
		to the circle, and checking if that point is colliding with the circle
	*/
	else if (this->shape == Shape::Circle && other.shape == Shape::Square)
	{
		float deltaX = xPos - max(other.getX() - (SIDE / 2), min(xPos, other.getX() + (SIDE / 2)));
		float deltaY = yPos - max(other.getY() - (SIDE / 2), min(yPos, other.getY() + (SIDE / 2)));
		return (deltaX * deltaX + deltaY * deltaY) < (RADIUS * RADIUS);
	}
	else if (this->shape == Shape::Square && other.shape == Shape::Circle)
	{
		float deltaX = other.getX() - max(xPos - (SIDE / 2), min(other.getX(), xPos + (SIDE / 2)));
		float deltaY = other.getY() - max(yPos - (SIDE / 2), min(other.getY(), yPos + (SIDE / 2)));
		return (deltaX * deltaX + deltaY * deltaY) < (RADIUS * RADIUS);
	}
	else
	{
		throw invalid_argument("Shape error");
	}
}

void Piece::move(const float newX, const float newY)
{
	// Set new xy coordinates
	this->setX(round(newX * 10) / 10);
	this->setY(round(newY * 10) / 10);
}

ostream& operator<<(ostream& outStream, const Piece& piece)
{
	string str;

	if (piece.type == Piece::Type::Rook)
		str = "Rook";
	else if (piece.type == Piece::Type::Bishop)
		str = "Bishop";
	else
		str = "Queen";

	outStream << str << "(id:"<< piece.id << ",x:" << piece.xPos << ",y:" << piece.yPos << ")";
	return outStream;
}