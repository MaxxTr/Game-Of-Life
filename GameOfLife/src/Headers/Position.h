#ifndef POSITION_H
#define POSITION_H

#include <iostream> 
#include <math.h>
#include <stdlib.h>

class Position
{
private:

	int m_X;
	int m_Y;
	
public:

	Position(Position* src) : m_X(src->getXPosition()), m_Y(src->getYPosition()){}
	Position(Position& src) : m_X(src.getXPosition()), m_Y(src.getYPosition()){}
	Position(int x = -1, int y = -1) : m_X(x), m_Y(y){}
	
	Position& operator=(Position& p) 
	{
		m_X = p.getXPosition();
		m_Y = p.getYPosition();
		return *this;
	}

	bool operator==(Position& p) 
	{
		return (m_X == p.getXPosition()) && (m_Y == p.getYPosition());
	}

	bool operator==(std::shared_ptr<Position> p) 
	{
		return (m_X == p->getXPosition()) && (m_Y == p->getYPosition());
	}
	
	void setXYCoordinates(unsigned int x, unsigned int y)
	{
		m_X = x;
		m_Y = y;
	}
	
	inline unsigned int getXPosition()
	{
		return m_X; 
	}
	
	inline unsigned int getYPosition()
	{
		return m_Y;
	}
	
	static inline unsigned int getDistance(Position& first, Position& second)
	{
		return getDistance(
			first.getXPosition(),
			first.getYPosition(),
			second.getXPosition(),
			second.getYPosition());
	}
	
	static inline unsigned int getDistance(
		unsigned int x1,
		unsigned int y1,
		unsigned int x2,
		unsigned int y2)
	{
		int xDist = x1 - x2;
		int yDist = y1 - y2;
		return getDistance(xDist, yDist);
	}

	static inline unsigned int getDistance(
		unsigned int xDelta,
		unsigned int yDelta)
	{
		if(xDelta == 0 && yDelta == 0)
		{
			return 0;
		}
		return (unsigned int)floor(sqrt( (double)((xDelta*xDelta) + (yDelta*yDelta)) ));
	}

	static inline bool isDistanceLegal(Position& first, Position& second, unsigned int limit)
	{
		return  std::abs((int)(first.getXPosition() - second.getXPosition())) <= limit && 
			std::abs((int)(first.getYPosition() - second.getYPosition())) <= limit;
	}

	static inline int sign(int num)
	{
		return num < 0 ? -1 : 1;
	}

	static inline int neg_sign(int num)
	{
		return num < 0 ? 1 : -1;
	}

	inline std::shared_ptr<Position> getRandomPosition(
			unsigned int speed,
			unsigned int yUpLimit,
			unsigned int xUpLimit)
	{
		unsigned int x = (std::rand() % speed)+1;
		unsigned int y = (std::rand() % speed)+1;
		unsigned int xSign = std::rand() & 0x1;
		unsigned int ySign = std::rand() & 0x1;
		int newX = computeAbsoluteCoordinate(m_X+(xSign*x), xUpLimit);
		int newY = computeAbsoluteCoordinate(m_Y+(ySign*y), yUpLimit);
		return std::shared_ptr<Position>(new Position(newX, newY));
	}

	inline std::shared_ptr<Position> getFurthestPosition(
		std::shared_ptr<Position> target,
		unsigned int speed,
		unsigned int yUpLimit,
		unsigned int xUpLimit)
	{
		if(target == NULL) return NULL;
		int xDir = target->getXPosition() - m_X;
		int yDir = target->getYPosition() - m_Y;
		xDir = xDir > speed ? Position::sign(xDir)*speed : xDir;
		yDir = yDir > speed ? Position::sign(yDir)*speed : yDir;
		int newX = computeAbsoluteCoordinate(m_X-xDir, xUpLimit);
		int newY = computeAbsoluteCoordinate(m_Y-yDir, yUpLimit);
		return std::shared_ptr<Position>(new Position(newX, newY));
	}

	inline std::shared_ptr<Position> getClosestPosition(
		std::shared_ptr<Position> target,
		unsigned int speed,
		unsigned int& xLimit,
		unsigned int& yLimit)
	{
		if(target == NULL) return NULL;
		int wholeXDistance = getDelta(m_X, target->getXPosition(), xLimit);
		int wholeYDistance = getDelta(m_Y, target->getYPosition(), xLimit);
		int distanceX = (std::abs(wholeXDistance) < speed) ? wholeXDistance : speed*Position::sign(wholeXDistance);
		int distanceY = (std::abs(wholeYDistance) < speed) ? wholeYDistance : speed*Position::sign(wholeYDistance);
		return std::shared_ptr<Position>(
			new Position(
				computeAbsoluteCoordinate(m_X+distanceX, xLimit), 
				computeAbsoluteCoordinate(m_Y+distanceY,yLimit)));
	}

	inline unsigned int getDelta(int myCoord, int targetCoord, int limit)
	{
		int straight = myCoord - targetCoord;
		return (straight < 0) ? std::min(straight, limit - straight) : std::max(straight, -limit + straight);
	}

	inline unsigned int computeAbsoluteCoordinate(int temp, unsigned int limit)
	{
		unsigned int xTmp = std::abs((int)(temp))%limit;
		return (temp < 0) ? limit-xTmp : xTmp;
	}

	inline std::shared_ptr<Position> computeNextPositionForBlackSwan(
		std::shared_ptr<Position> center,
		unsigned int radius,
		unsigned int boardXLimit,
		unsigned int boardYLimit)
	{
		unsigned int range = radius;
		double xProportion = (X_UP_LIMIT-X_DOWN_LIMIT)/(range);
		double yProportion = (Y_UP_LIMIT-Y_DOWN_LIMIT)/(range);

		double prevRangedX = X_DOWN_LIMIT + (m_X-radius)*xProportion;
		double prevRangedY = Y_DOWN_LIMIT + (m_Y-radius)*yProportion;
		double x = (A*prevRangedX) + prevRangedY;
		double y = B + (prevRangedX*prevRangedX);

		unsigned int newX = computeAbsoluteCoordinate(
			((x - X_DOWN_LIMIT)/xProportion) + radius, boardXLimit);
		unsigned int newY = computeAbsoluteCoordinate(
			((y - Y_DOWN_LIMIT)/yProportion) + radius, boardYLimit);
		
		return std::shared_ptr<Position>(new Position(newX, newY));
	}
};

typedef std::shared_ptr<Position> shPosition;


class SmartSquare
{
public:
	unsigned int m_length;
	coordPtr m_emptyCoordArray;
	shPosition m_PredatorsCenter;
	shPosition m_PreysCenter;
	shPosition m_ClosestPredator;
	shPosition m_ClosestPrey;
	shPosition m_PredatorBlackSwan;
	shPosition m_PreyBlackSwan;

	~SmartSquare()
	{
		delete[] m_emptyCoordArray;
	}

	SmartSquare(
		unsigned int coordArrayLength,
		coordPtr coordArray,
		shPosition predatorsCenter,
		shPosition preyCenter,
		shPosition closestPredator,
		shPosition closestPrey,
		shPosition predatorBlackSwan,
		shPosition preyBlackSwan) :
		m_length(coordArrayLength),
		m_emptyCoordArray(coordArray),
		m_PredatorsCenter(predatorsCenter),
		m_PreysCenter(preyCenter),
		m_ClosestPredator(closestPredator),
		m_ClosestPrey(closestPrey),
		m_PredatorBlackSwan(predatorBlackSwan),
		m_PreyBlackSwan(preyBlackSwan){}
};

typedef std::shared_ptr<SmartSquare> shSmartSquare;

#endif // POSITION_H
