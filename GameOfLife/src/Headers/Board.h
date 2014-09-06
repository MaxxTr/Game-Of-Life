#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <QPixmap>
#include <QPainter>
#include <QThread>
//#include "CellGuard.h"
//#include "CreatureGuard.h"
#include "Cell.h"
#include "Predator.h"
#include "Prey.h"
#include "Creature.h"
#include "Definitions.h"

class Board : public QThread 
{
	Q_OBJECT

private:

	unsigned int m_iteration;
	unsigned int m_width;
	unsigned int m_height;
	
	std::vector<shCell> m_board; // vertor of Cells
	std::shared_ptr<std::vector<shPredator> > m_predators;
	std::shared_ptr<std::vector<shPrey> > m_preys;

	unsigned int m_PredatorGroupsIndex;
	std::map<std::pair<unsigned int, unsigned int>, bool> m_PredatorGroupsEnmity;

	std::map<unsigned int, unsigned int> m_GroupMembersNumMap;
	shPredator	m_BestPredator;
	shPrey		m_BestPrey;

signals:

	void iterationFinished();

public:

	typedef void (Board::*CreatureFactory)(
		unsigned int,
		unsigned int,
		unsigned int,
		shCell);
	
	Board::Board(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height),
		m_iteration(0),
		m_predators(new std::vector<shPredator>),
		m_preys(new std::vector<shPrey>),
		m_PredatorGroupsIndex(0)
	{
		std::srand(std::time(0)); //use current time as seed for random generator
		for(unsigned int y = 0; y < m_height; ++y)
		{
			for(unsigned int x = 0; x < m_width; ++x)
			{
				m_board.emplace_back(std::shared_ptr<Cell>(new Cell(x, y)));
			}
		}
	}

	void run()
	{
		nextIterationOverPredators();
		nextIterationOverPreys();
		updateIteration();
		emit iterationFinished();
	}
	
	void settleBoardWithPredators(
		unsigned int saturation,
		unsigned int radius,
		unsigned int centralX,
		unsigned int centralY)
	{
		if(radius == 0)
		{
			return;
		}
		settleBoard(saturation, radius, centralX, centralY, &Board::addNewPredator);
		setGroupsEnmity();
		++m_PredatorGroupsIndex;
		m_BestPredator = m_predators->at(0);
	}
	
	void settleBoardWithPreys(
		unsigned int saturation,
		unsigned int radius,
		unsigned int centralX,
		unsigned int centralY)
	{
		if(radius == 0)
		{
			return;
		}
		settleBoard(saturation, radius, centralX, centralY, &Board::addNewPrey);
		m_BestPrey = m_preys->at(0);
	}

	void drawItself(QPainter* p, Definitions& def)
	{
		std::for_each(m_board.begin(),m_board.end(),[&](shCell cell)
		{
			cell->drawItself(p, def);
		});
	}

	inline shCell get(int x, int y)
	{
		return m_board[x + (y*m_width)];
	}

	inline shCell get(shPosition pos)
	{
		return m_board[pos->getXPosition() + (pos->getYPosition()*m_width)];
	}
	
	inline void createHistogram(unsigned int radius, std::map<int, unsigned int>& hist)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<> dist(0, radius);
		for(int n = 0; n < RANDOMIZATOR; ++n)
		{
			++hist[(unsigned int)floor(dist(gen))];
		}
	}	
	
	void settleBoard(
		unsigned int saturation,
		unsigned int radius,
		unsigned int centralX,
		unsigned int centralY,
		Board::CreatureFactory creatureFactory)
	{
		std::map<int, unsigned int> hist;
		std::vector<std::pair<shCell, unsigned int> > squareToSettle;
		createHistogram(radius, hist);
		
		getPartOfBoard(
			radius + radius,
			centralX,
			centralY,
			squareToSettle);
			
		iterateOverNearPoints(
			saturation,
			radius + radius,
			centralX,
			centralY,
			hist,
			squareToSettle,
			creatureFactory);
	}

	inline void updateIteration()
	{
		++m_iteration;
		/*
		std::for_each(m_board.begin(),m_board.end(),[&](shCell cell)
		{
			cell->removeDeads();
		});
		*/
		std::shared_ptr<std::vector<shPredator> > toSwapPredators(new std::vector<shPredator>());
		for(int i = 0; i < m_PredatorGroupsIndex; ++i)
		{
			m_GroupMembersNumMap[i] = 0;
		}
		std::for_each(m_predators->begin(), m_predators->end(), [&](shPredator c)
		{
			if(c->isInLife())
			{
				m_GroupMembersNumMap[c->getGroupID()]++;
				toSwapPredators->emplace_back(c);
			}
		});
		m_predators = toSwapPredators;
		std::shared_ptr<std::vector<shPrey> > toSwapPreys(new std::vector<shPrey>());
		std::for_each(m_preys->begin(),m_preys->end(),[&](shPrey c)
		{
			if(c->isInLife())
			{
				toSwapPreys->emplace_back(c);
			}
		});
		m_preys = toSwapPreys;
	}
	
	inline void iterateOverNearPoints(
		unsigned int saturation,
		unsigned int radius,
		unsigned int centralX,
		unsigned int centralY,
		std::map<int, unsigned int>& hist,
		std::vector<std::pair<shCell, unsigned int> >& squareToSettle,
		Board::CreatureFactory creatureFactory)
	{
		std::for_each(
				squareToSettle.begin(),
				squareToSettle.end(),
				[&centralX, &centralY, &hist, &creatureFactory, &saturation, &radius, this](std::pair<shCell, unsigned int>& pair)
		{
			shPosition position = pair.first->getPosition();
			unsigned int distance = pair.second;
			if(!pair.first->isFull() && distance < radius)
			{
				unsigned int randomNum = std::abs( std::rand() ) % saturation;
				if(randomNum < hist[distance])
				{
					(this->*creatureFactory)(position->getXPosition(), position->getYPosition(), randomNum, pair.first);
				}
			}
		});
	}
	
	inline void addNewPredator(
		unsigned int x,
		unsigned int y,
		unsigned int randomNum,
		shCell cell)
	{
		if(cell->isFull())
		{
			return;
		}
		shPredator c = std::shared_ptr<Predator>(new Predator(x, y, randomNum, m_PredatorGroupsIndex));
		++m_GroupMembersNumMap[m_PredatorGroupsIndex];
		unsigned int index = cell->addPredator(c);
		c->setCellIndex(index);
		m_predators->emplace_back( c);
	}
	
	inline void addNewPrey(
		unsigned int x,
		unsigned int y,
		unsigned int randomNum,
		shCell cell)
	{
		if(cell->hasPrey())
		{
			return;
		}
		shPrey c = std::shared_ptr<Prey>(new Prey(x, y, randomNum));
		cell->addPrey(c);
		m_preys->emplace_back( c);
	}

	inline void getPartOfBoard(
		int radius,
		unsigned int xCent,
		unsigned int yCent,
		std::vector<std::pair<shCell, unsigned int> >& result)
	{
		unsigned int place = 0;
		for(int i = -radius; i < radius; ++i)
		{
			for(int j = -radius; j < radius; ++j)
			{	
				unsigned int x = computeAbsoluteXCoordinate(xCent+i);
				unsigned int y = computeAbsoluteYCoordinate(yCent+j);
				unsigned int place = x+(m_width*y);
				result.emplace_back(std::make_pair(m_board[place], Position::getDistance(std::abs(i), std::abs(j))));
			}
		}
	}

	void nextIterationOverPredators()
	{
		std::vector<shPredator> children;
		std::for_each(m_predators->begin(), m_predators->end(), [&](shPredator c)
		//#pragma omp parallel for
		//for(int i = 0; i < m_predators->size(); ++i)
		{
			//shPredator c = m_predators->at(i);
			if(c->isInLife())
			{
				shPosition currentPosition = c->getPosition();
				bool newPositionAvaliable = false;
				shPosition newPos = NULL;
				shSmartSquare sVisionSquare = getSurroundInformation(c->getVision(), currentPosition, true);
				
				if(sVisionSquare->m_PredatorBlackSwan != NULL && !c->isBlackSwan())
				{
					if(sVisionSquare->m_length != 0)
					{
						newPos = getNotTakenCellNearTarget(
							sVisionSquare->m_PredatorBlackSwan, sVisionSquare->m_emptyCoordArray, sVisionSquare->m_length);
						newPositionAvaliable = true;
					}
				}
				else
				{
					if(	c->isBlackSwan() )
					{
						newPos = getPositionForBlackSwan(currentPosition, c->getVision()); // Black Swan doesn't need empty cell)
						newPositionAvaliable = true;
					}
					else
					{
						shSmartSquare sSquare = getSurroundInformation(c->getSpeed(), currentPosition, true);
						if(sSquare->m_length != 0)
						{
							newPos = getBestPosition(
								sSquare, currentPosition, c->getSpeed(), true, c->getLifePolicy());
							newPositionAvaliable = true;
						}
					}
				}
				if(newPositionAvaliable)
				{
					if(newPos == NULL)
					{
						newPos = currentPosition;
					}
					shCell newCell = get(newPos);
					shPredator pair = newCell->getPair( );
					bool hasPray = newCell->hasPrey();
					if(c->isOmnivorous() == true && pair != NULL)
					{
						hasPray = true;
						c->increaseStrength();
					}
					bool bAreEnemies = areEnemies(c, pair);
					shPredator newc = c->nextStep(
							pair,
							hasPray,
							bAreEnemies);

					setNewPositionForPredator(
						c,
						pair,
						newc,
						get(currentPosition),
						newCell,
						currentPosition,
						newPos,
						children);

					if(newc != NULL)
					{	
						if(!m_BestPredator->bestThan((Creature&)newc))
						{
							m_BestPredator = newc;
						}
						children.emplace_back(newc);
					}
				}
			}
		});
		for(auto cIter = children.begin(); cIter != children.end(); cIter++)
		{
			m_predators->emplace_back(*cIter);
		}
	}

	void nextIterationOverPreys()
	{
		std::vector<shPrey> children;
		std::for_each(m_preys->begin(), m_preys->end(), [&](shPrey c)
		{
			if(c->isInLife())
			{
				shPosition currentPosition = c->getPosition();
				shPosition newPos = NULL;
				std::vector<shPrey> nearPreys;
				getNearPreys(currentPosition, nearPreys);
				shSmartSquare sVisionSquare = getSurroundInformation(c->getVision(), currentPosition, false);
				if(sVisionSquare->m_PreyBlackSwan != NULL && !c->isBlackSwan())
				{
					
					if(sVisionSquare->m_length!= 0)
					{
						newPos = getNotTakenCellNearTarget(
							sVisionSquare->m_PreyBlackSwan, sVisionSquare->m_emptyCoordArray, sVisionSquare->m_length);
					}
				}
				else
				{
					if(	c->isBlackSwan() )
					{
						newPos = getPositionForBlackSwan(currentPosition, c->getVision()); // Black Swan doesn't need empty cell)
					}
					else
					{
						unsigned int speed = c->getSpeed();
						shSmartSquare sSquare = getSurroundInformation(speed, currentPosition, false);
						if(sSquare->m_length != 0)
						{
							newPos = getBestPosition(
								sSquare, currentPosition, speed, false, c->getLifePolicy());
						}
					}
				}

				shPrey newc = c->nextStep(
					Prey::getRandomPair(nearPreys),
					nearPreys.size());
				
				if(newPos == NULL)
				{
					newPos = currentPosition;
				}
				setNewPositionForPrey(
					c,
					newc,
					get(currentPosition),
					get(newPos),
					currentPosition,
					newPos,
					children);
			}
		});
		for(auto cIter = children.begin(); cIter != children.end(); cIter++)
		{
			m_preys->emplace_back(*cIter);
		}
	}

	inline shPosition getBestPositionForFoodOriented(
		shPosition myPos, shSmartSquare& sq, unsigned int speed)
	{
		return myPos->getClosestPosition(sq->m_PreysCenter, speed, m_width, m_height);
	}

	inline shPosition getBestPositionForReproductionOriented
		(shPosition myPos, shSmartSquare sq, unsigned int speed, bool isPredator)
	{
		return isPredator ?
			myPos->getClosestPosition(sq->m_PredatorsCenter, speed, m_width, m_height) : 
			myPos->getClosestPosition(sq->m_PreysCenter, speed, m_width, m_height);
	}

	inline shPosition getBestPositionForSinglenessOriented(
		shPosition myPos, shSmartSquare sq, unsigned int speed)
	{
		return myPos->getFurthestPosition(sq->m_PredatorsCenter, speed, m_height, m_width);
	}

	inline shPosition getBestPositionForRandomOriented(
		shPosition myPos, unsigned int speed)
	{
		return myPos->getClosestPosition(myPos->getRandomPosition(speed, m_height, m_width), speed, m_width, m_height);
	}
	
	inline shPosition getBestPositionForSafetyOriented(
		shPosition myPos, shSmartSquare sq, unsigned int speed, bool isPredator)
	{
		return isPredator ? 
			myPos->getClosestPosition(sq->m_PredatorsCenter, speed, m_width, m_height) :
			myPos->getFurthestPosition(sq->m_PredatorsCenter, speed, m_height, m_width);
	}

	inline shPosition getPositionForBlackSwan(shPosition myPos, unsigned int radius)
	{
		return myPos->computeNextPositionForBlackSwan(
			myPos, radius,
			m_width, m_height);
	}

	inline void getNearPreys(shPosition pos, std::vector<shPrey>& result)
	{
		int xCent = pos->getXPosition();
		int yCent = pos->getYPosition();
		for(int i = -1; i < 1; ++i)
		{
			for(int j = -1; j < 1; ++j)
			{
				unsigned int place = 
					computeAbsoluteXCoordinate(xCent+i) + (computeAbsoluteYCoordinate(yCent+j)*m_width);
				if(m_board[place]->hasPrey())
				{
					result.emplace_back(m_board[place]->getPrey());
				}
			}
		}
	}

	inline std::pair<bool, shPosition> hasPredatorBlackSwan(shSquare sq)
	{
		for(auto i = sq->m_leftDownY; i < sq->m_leftUpY; ++i)
		{
			for(auto j = sq->m_leftDownX; j < sq->m_rightDownX; ++j)
			{
				if(m_board[j+(i*m_width)]->hasPredatorBlackSwan())
				{
					return std::make_pair(true, shPosition(new Position(j, i)));
				}
			}
		}
		return std::make_pair(false, shPosition());
	}

	inline std::pair<bool, shPosition > hasPreyBlackSwan(shSquare sq)
	{
		for(auto i = sq->m_leftDownY; i < sq->m_leftUpY; ++i)
		{
			for(auto j = sq->m_leftDownX; j < sq->m_rightDownX; ++j)
			{
				if(m_board[j+(i*m_width)]->hasPreyBlackSwan())
				{
					return std::make_pair(true, shPosition(new Position(j, i)));
				}
			}
		}
		return std::make_pair(false, shPosition());
	}

	inline unsigned int getHeight()
	{
		return m_height;
	}

	inline unsigned int getWidth()
	{
		return m_width;
	}

	inline shPosition getBestPosition(
		shSmartSquare sq,
		shPosition myPos,
		unsigned int speed,
		bool isPredator,
		LifePolicy::LifePolicyOrientation orientation)
	{
		if(sq->m_length == 0)
		{
			return myPos;
		}
		shPosition targetPosition = NULL;
		switch(orientation)
		{
			case LifePolicy::FOOD_ORIENTED:
				targetPosition = getBestPositionForFoodOriented(myPos, sq, speed);
				break;
			case LifePolicy::REPRODUCTION_ORIENTED:
				targetPosition = getBestPositionForReproductionOriented(myPos, sq, speed, isPredator);
				break;
			case LifePolicy::SINGLENESS_ORIENTED:
				targetPosition = getBestPositionForSinglenessOriented(myPos, sq, speed);
				break;
			case LifePolicy::RANDOM_ORIENTED:
				targetPosition = getBestPositionForRandomOriented(myPos, speed);
				break;
			case LifePolicy::SAFETY_ORIENTED:
				targetPosition = getBestPositionForSafetyOriented(myPos, sq, speed, isPredator);
				break;
		}
		if(targetPosition == NULL) 
		{
			targetPosition = getBestPositionForRandomOriented(myPos, speed);
		}
		if(isPredator)
		{
			if(!get(targetPosition)->isFull())
			{
				return targetPosition;
			}
		}
		else
		{
			if(!get(targetPosition)->hasPrey())
			{
				return targetPosition;
			}
		}
		return getNotTakenCellNearTarget(targetPosition, sq->m_emptyCoordArray, sq->m_length);
	}

	inline shPosition getNotTakenCellNearTarget(
		shPosition target, 
		std::pair<unsigned int, unsigned int> notTakenCoordinates[],
		unsigned int& length)
	{
		if(target == NULL)
		{
			return NULL;
		}
		unsigned int x = target->getXPosition();
		unsigned int y = target->getYPosition();

		// computing distances from Non Tacken Cells to the Target
		int min = MAX_DISTANCE;
		int minPos = 0;
		int res = 0;
		for(int i = 0; i < length; ++i)
		{
			std::pair<unsigned int, unsigned int> p = notTakenCoordinates[i];
			res = Position::getDistance(x, y, p.first, p.second);
			if(res < min)
			{
				min = res;
				minPos = i;
			}
		}
		std::pair<unsigned int, unsigned int> p = notTakenCoordinates[minPos];
		return shPosition(new Position(p.first, p.second));
	}

	inline shSmartSquare getSurroundInformation(int radius, shPosition pos, bool forPredator)
	{
		int xCent = pos->getXPosition();
		int yCent = pos->getYPosition();
		unsigned int xPredatorSum = 0, xPreySum = 0; 
		unsigned int yPredatorSum = 0, yPreySum = 0;
		unsigned int predatorCounter = 0, preyCounter = 0;
		unsigned int minDistanceToPrey = MAX_DISTANCE;
		unsigned int minDistanceToPredator = MAX_DISTANCE;
		int place = 0;
		coordPtr arrayCoord = Definitions::allocateArray(radius);
		coord nearestPrey, nearestPredator;
		coord preyBlackSwan, predatorBlackSwan;
		bool hasPreyBlackSwan = false, hasPredatorBlackSwan = false;
		for(int i = -radius; i < radius; ++i)
		{
			for(int j = -radius; j < radius; ++j)
			{
				if(i == 0 && j == 0) continue;
				unsigned int x = computeAbsoluteXCoordinate(xCent+i);
				unsigned int y = computeAbsoluteYCoordinate(yCent+j);
				unsigned int distance = Position::getDistance(i, j);
				shCell cell = m_board[x+(y*m_width)];
				if(cell->isFull())
				{
					updateSum(xPredatorSum, yPredatorSum, (x<<1), (y<<1));
					predatorCounter += 2;
					updateMinDistance(distance, minDistanceToPredator, nearestPredator, x, y);
				}
				else if(cell->hasPredator())
				{
					updateSum(xPredatorSum, yPredatorSum, x, y);
					predatorCounter++;
					updateMinDistance(distance, minDistanceToPredator, nearestPredator, x, y);
				}
				if(forPredator && !cell->isFull())
				{
					arrayCoord[place] = std::make_pair(x, y);
					++place;
				}
				if(cell->hasPrey())
				{
					updateBlackSwan(cell->hasPreyBlackSwan(), x, y, preyBlackSwan, hasPreyBlackSwan);
					updateSum(xPreySum, yPreySum, x, y);
					preyCounter++;
					updateMinDistance(distance, minDistanceToPrey, nearestPrey, x, y);
				}
				else if(!forPredator)
				{
					arrayCoord[place] = std::make_pair(x, y);
					++place;
				}
				updateBlackSwan(cell->hasPredatorBlackSwan(), x, y, predatorBlackSwan, hasPredatorBlackSwan);
			}
		}
		return shSmartSquare(new SmartSquare(
			place,
			arrayCoord,
			setCenterPosition(predatorCounter, xPredatorSum, yPredatorSum),
			setCenterPosition(preyCounter, xPreySum, yPreySum),
			setNearestPosition( minDistanceToPredator, nearestPredator),
			setNearestPosition( minDistanceToPrey, nearestPrey),
			setBlackSwan(hasPredatorBlackSwan, predatorBlackSwan),
			setBlackSwan(hasPreyBlackSwan, preyBlackSwan)));
	}

	inline void updateMinDistance(unsigned int& dist, unsigned int& minDist, coord& nearestCreature,
					unsigned int&x, unsigned int& y)
	{
		if(dist < minDist)
		{
			minDist = dist;
            nearestCreature = std::make_pair(x, y);
		}
	}

	inline void updateSum(unsigned int& xSum, unsigned int& ySum, unsigned int xUpdate, unsigned int yUpdate)
	{
		xSum += xUpdate;
		ySum += yUpdate;
	}

	inline void updateBlackSwan(bool exist, unsigned int x, unsigned int y, coord& balckSwan, bool& existsUpdate)
	{
		if(exist)
		{
            balckSwan = std::make_pair(x, y);
			existsUpdate = true;
		}
	}

	inline shPosition setCenterPosition(unsigned int counter, unsigned int xSum, unsigned int ySum)
	{
		return (counter == 0) ? NULL : 
			shPosition(new Position(xSum/counter, ySum/counter));
	}

	inline shPosition setNearestPosition(unsigned int minDistance, std::pair<unsigned int, unsigned int>& pair)
	{
		return (minDistance == MAX_DISTANCE) ? NULL : 
			shPosition(new Position(pair.first, pair.second));
	}

	inline shPosition setBlackSwan(bool exists, std::pair<unsigned int, unsigned int>& pair)
	{
		return exists ? shPosition(new Position(pair.first, pair.second)) : NULL;
	}

	inline unsigned int computeAbsoluteXCoordinate(int temp)
	{
		unsigned int xTmp = std::abs((int)(temp))%m_width;
		return (temp < 0) ? m_width-1-xTmp : xTmp;
	}

	inline unsigned int computeAbsoluteYCoordinate(int temp)
	{
		unsigned int xTmp = std::abs((int)(temp))%m_height;
		return (temp < 0) ? m_height-1-xTmp : xTmp;
	}

	inline void setNewPositionForPredator(
		shPredator p,
		shPredator pair,
		shPredator child,
		shCell oldCell,
		shCell newCell,
		shPosition oldPosition,
		shPosition newPosition,
		std::vector<shPredator>& children)
	{
		if(p->isOmnivorous() == true && pair != NULL)
		{
			pair->setInLife(false);
		}
		if(!(oldPosition == newPosition))
		{			
			oldCell->removePredator(p->getCellIndex());
			if(newCell->hasPrey() && p->hasEaten())
			{
				shPrey p = newCell->getPrey();
				newCell->removePrey();
				if(p != NULL)
				{
					p->setInLife(false);
				}
			}
			if(p->isBlackSwan())
			{
				p->setCellIndex(newCell->addPredatorBlackSwan(p));
			}
			else
			{
				p->setCellIndex(newCell->addPredator(p));
			}
			p->setPosition(newPosition);
			if(child != NULL)
			{
				//children.emplace_back(child);
				newCell->addChild(child);
				child->setPosition(newPosition);
				/*
				shSquare sq = getPartOfBoard(1, newPosition);
				coordPtr preyArround = new coord[9];
				unsigned int preyLength = 0;
				getNotTakenCoordinatesForPreysInArray(sq, preyArround, preyLength);
				coordPtr predatorsArround = new coord[9];
				unsigned int predatorLength = 0;
				getNotTakenCoordinatesForPredatorsInArray(sq, predatorsArround, predatorLength);
				if(preyLength > 7 && predatorLength > 6) // in the case the predator has enough prey and hasn't a big number
				{										// of other predators near it can give a pair of children
					shPredator newChild  = new Predator(*child);
					children.emplace_back(newChild);
					Cell* additionalCell = get(predatorsArround[0].first, predatorsArround[0].second);
					newChild->setCellIndex(additionalCell->addPredator(newChild));
					newChild->setPosition(additionalCell->getPosition());
				}
				delete[] preyArround;
				delete[] predatorsArround;
				*/
			}
		}
	}

	inline void setNewPositionForPrey(
		shPrey p,
		shPrey child,
		shCell oldCell,
		shCell newCell,
		shPosition oldPosition,
		shPosition newPosition,
		std::vector<shPrey>& children)
	{
		if(newPosition == oldPosition)
		{
			if(child != NULL)
			{
				shSmartSquare sSquare = getSurroundInformation(1, newPosition, false);
				if(sSquare->m_length != 0)
				{
					coord emptyCoord = sSquare->m_emptyCoordArray[sSquare->m_length-1];
					shCell newCellForChild = get(emptyCoord.first, emptyCoord.second);
					newCellForChild->addPrey(child);
					children.emplace_back(child);
				}
			}
		}
		else
		{
			oldCell->removePrey();
			if(child != NULL)
			{
				if(!m_BestPrey->bestThan((Creature&)child))
				{
					m_BestPrey = child;
				}
				oldCell->addPrey(child);
				child->setPosition(oldPosition);
				children.emplace_back(child);
			}
			newCell->addPrey(p);
			p->setPosition(newPosition);
		}
	}

	inline void setGroupsEnmity()
	{
		for(int i = 0; i < m_PredatorGroupsIndex; ++i)
		{
			unsigned int d = (std::abs(std::rand())) % 2;
			m_PredatorGroupsEnmity.insert(std::make_pair(std::make_pair(i, m_PredatorGroupsIndex), (d == 0)));
		}
	}

	inline bool areEnemies(shPredator p1, shPredator p2)
	{
		if(p2 == NULL || p1 == NULL)
		{
			return false;
		}
		unsigned int group1 = p1->getGroupID();
		unsigned int group2 = p2->getGroupID();
		if(group1 == group2)
		{
			return false;
		}
		return m_PredatorGroupsEnmity[std::make_pair(std::min(group1, group2), std::max(group1, group2))];
	}
	std::map<unsigned int, unsigned int>& getPredatorGroupMembersNumMap(){return m_GroupMembersNumMap;}
	shPredator getBestPredator(){return m_BestPredator;}
	shPrey getBestPrey(){return m_BestPrey;}

	int getPredatorsNum(){return m_predators->size();}
	int getPreysNum(){return m_preys->size();}
};

#endif // BOARD_H
