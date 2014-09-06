#ifndef CELL_H
#define CELL_H

#include <iostream> 
#include <sstream>
#include <string>
#include <QPainter>
#include <omp.h>

#include "Creature.h"
#include "Definitions.h"
#include "Predator.h"
#include "Prey.h"

class Cell
{
private:

	bool m_hasPrey;
	bool m_hasFirstPredator;
	bool m_hasSecondPredator;
	bool m_hasChildPredator;
	
	shPosition m_pos;
	shPredator m_firstPredator;
	shPredator m_secondPredator;
	shPredator m_childPredator;
	shPrey m_prey;

//	omp_lock_t LCK;

public:
	
	Cell(unsigned int x, unsigned int y) : 
		m_pos(new Position(x, y)),
		m_hasPrey(false),
		m_hasFirstPredator(false),
		m_hasSecondPredator(false),
		m_hasChildPredator(false),
		m_firstPredator( NULL ),
		m_secondPredator( NULL ),
		m_childPredator( NULL ),
		m_prey( NULL ) {/* omp_init_lock (&LCK);*/}
/*
	inline omp_lock_t* getLock()
	{
		return &LCK;
	}
*/		
	inline int addPredator(shPredator p)
	{
		if(!m_hasFirstPredator)
		{
			m_firstPredator = p;
			m_hasFirstPredator = true;
			return 0;
		}
		else
		{
			m_secondPredator = p;
			m_hasSecondPredator = true;
			return 1;
		}
	}

	inline int addPredatorBlackSwan(shPredator p)
	{
		if(m_hasFirstPredator && m_hasSecondPredator)
		{
			//m_firstPredator->setInLife(false);
			m_firstPredator = p;
			m_hasFirstPredator = true;
			return 0;
		}
		else if(!m_hasFirstPredator && m_hasSecondPredator)
		{
			//m_firstPredator->setInLife(false);
			m_firstPredator = p;
			m_hasFirstPredator = true;
			return 0;
		}
		else if(m_hasFirstPredator && !m_hasSecondPredator)
		{
			//m_secondPredator->setInLife(false);
			m_secondPredator = p;
			m_hasSecondPredator = true;
			return 1;
		}
		else
		{
			//m_secondPredator->setInLife(false);
			m_secondPredator = p;
			m_hasSecondPredator = true;
			return 1;
		}
	}
	
	inline void addChild(shPredator p)
	{
		m_childPredator = p;
		m_hasChildPredator = true;
	}
	
	inline void removePredator(unsigned int i)
	{
		if(i == 0)
		{
			m_firstPredator = NULL;
			m_hasFirstPredator = false;
		}
		else if(i == 1)
		{
			m_secondPredator = NULL;
			m_hasSecondPredator = false;
		}
		else
		{
			m_childPredator = NULL;
			m_hasChildPredator = false;
		}
	}

	inline void removeDeads()
	{
		if(m_hasPrey && !m_prey->isInLife())
		{
			m_prey = NULL;
			m_hasPrey = false;
		}
		if(m_hasFirstPredator && !m_firstPredator->isInLife())
		{
			m_firstPredator = NULL;
			m_hasFirstPredator = false;
		}
		if(m_hasSecondPredator && !m_secondPredator->isInLife())
		{
			m_secondPredator = NULL;
			m_hasSecondPredator = false;
		}
	}
	
	inline void removePrey( )
	{
		m_prey = NULL;
		m_hasPrey = false;
	}
	
	inline void addPrey(shPrey p)
	{
		if(p != NULL)
		{
			m_prey = p;
			m_hasPrey = true;
		}
	}
	
	inline bool hasPredatorBlackSwan( )
	{
		if((m_hasFirstPredator && m_firstPredator->isInLife() && m_firstPredator->isBlackSwan()) ||
			(m_hasSecondPredator && m_secondPredator->isInLife() && m_secondPredator->isBlackSwan()))
		{
			return true;
		}
		return false;
	}

	inline bool hasPreyBlackSwan()
	{
		return m_hasPrey && m_prey->isInLife() && m_prey->isBlackSwan();
	}

	inline shPredator getPair(unsigned int index)
	{
		if(m_hasFirstPredator && m_firstPredator->isInLife() && index == 1)
		{
			return m_firstPredator;
		}
		if(m_hasSecondPredator && m_secondPredator->isInLife() && index == 0)
		{
			return m_secondPredator;
		}
		return NULL;
	}

	inline shPredator getPair( )
	{
		if(m_hasFirstPredator && m_firstPredator->isInLife())
		{
			return m_firstPredator;
		}
		if(m_hasSecondPredator && m_secondPredator->isInLife())
		{
			return m_secondPredator;
		}
		return NULL;
	}

	inline void removePair( )
	{
		if(m_hasFirstPredator && m_firstPredator->isInLife() && !m_hasSecondPredator)
		{
			m_firstPredator = NULL;
			m_hasFirstPredator = false;
		}
		if(m_hasSecondPredator && m_secondPredator->isInLife() && !m_hasFirstPredator)
		{
			m_secondPredator = NULL;
			m_hasSecondPredator = false;
		}
	}
	
	inline shPrey getPrey()
	{
		return m_prey;
	}
	
	inline shPredator getPredator(unsigned int i)
	{
		return (i == 0) ? m_firstPredator : m_secondPredator;
	}

	inline shPosition getPosition()
	{
		return shPosition(m_pos);
	}
	
	inline bool hasPrey()
	{
		return m_hasPrey && m_prey->isInLife();
	}

	inline bool hasChild()
	{
		return m_hasChildPredator && m_childPredator->isInLife();
	}

	inline bool hasPredator()
	{

		return (m_hasFirstPredator && m_firstPredator->isInLife()) || 
				(m_hasSecondPredator && m_secondPredator->isInLife()) ||
				(m_hasChildPredator && m_childPredator->isInLife());
	}
	
	inline bool isEmpty()
	{
		return !m_hasFirstPredator && !m_hasSecondPredator;
	}
	
	inline bool isFull()
	{
		return (m_hasFirstPredator && m_firstPredator->isInLife()) && 
				(m_hasSecondPredator && m_secondPredator->isInLife());
	}

	inline void drawItself(QPainter* painter, Definitions& def)
	{
		unsigned int x = m_pos->getXPosition()*2*def.halfCellSize;
		unsigned int y = m_pos->getYPosition()*2*def.halfCellSize;
		painter->save();
		painter->translate(x, y);
		if(m_hasFirstPredator && m_firstPredator->isInLife())
		{
			setPainterForPredator(painter, def, m_firstPredator, false);
			painter->drawPolygon(def.pointsDown, 3);
		}
		if(m_hasSecondPredator && m_secondPredator->isInLife())
		{
			setPainterForPredator(painter, def, m_secondPredator, false);
			painter->drawPolygon(def.pointsLeft, 3);
		}
		if(m_hasChildPredator && m_childPredator->isInLife())
		{
			setPainterForPredator(painter, def, m_childPredator, true);
			painter->drawPolygon(def.pointsUp, 3);
		}
		if(m_hasPrey && m_prey->isInLife())
		{
			if(m_prey->isBlackSwan())
			{
				painter->setPen(QPen(Qt::black));
				painter->setBrush(def.preyLinearGradient);
			}
			else
			{
				painter->setPen(QPen(Qt::green));
				painter->setBrush(def.preyLinearGradient);
			}
			painter->drawPolygon(def.pointsRight, 3);
		}
		painter->restore();
	}

	inline void setPainterForPredator(
		QPainter* painter,
		Definitions& def,
		shPredator p,
		bool isChild)
	{
		if(p->isOmnivorous())
		{
			painter->setPen(QPen(Qt::yellow));
			painter->setBrush(def.omnivorousLinearGradient);
		}
		else if(p->isBlackSwan())
		{
			painter->setPen(QPen(Qt::black));
			painter->setBrush(def.predatorLinearGradient);
		}
		else if(isChild)
		{
			painter->setPen(QPen(Qt::blue));
			painter->setBrush(def.childLinearGradient);
		}
		else
		{
			painter->setPen(QPen(Qt::red));
			painter->setBrush(def.predatorLinearGradient);
		}
	}

	inline std::string getStringInfo()
	{
		std::stringstream result;
		result << "Cell: x: " << m_pos->getXPosition() << "  y: " << m_pos->getYPosition();
		if(m_hasPrey && m_prey->isInLife())
		{
			result << "\nPrey. " << 
 					"\n\tSpeed: " << m_prey->getSpeed() <<
					"\n\tVision: " << m_prey->getVision() <<
 					"\n\tOrientation: " << m_prey->getLifePolicyStr() ;
		}
		if(m_hasChildPredator && m_childPredator->isInLife())
		{
			result << "\nChild. " << m_childPredator <<
 					"\n\tSpeed: " << m_childPredator->getSpeed() <<
					"\n\tVision: " << m_childPredator->getVision() <<
					"\n\tHungry: " << m_childPredator->getHunger() <<
 					"\n\tOrientation: " << m_childPredator->getLifePolicyStr();
		}
		if(m_hasSecondPredator && m_secondPredator->isInLife())
		{
			result << "\nPredator. " << 
 					"\n\tSpeed: " << m_secondPredator->getSpeed() <<
					"\n\tVision: " << m_secondPredator->getVision() <<
					"\n\tHungry: " << m_secondPredator->getHunger() <<
 					"\n\tOrientation: " << m_secondPredator->getLifePolicyStr();
		}
		if(m_hasFirstPredator && m_firstPredator->isInLife())
		{
			result << "\nPredator. " << 
 					"\n\tSpeed: " << m_firstPredator->getSpeed() <<
					"\n\tVision: " << m_firstPredator->getVision() <<
					"\n\tHungry: " << m_firstPredator->getHunger() <<
 					"\n\tOrientation: " << m_firstPredator->getLifePolicyStr();
		}
		return result.str();
	}

};

typedef std::shared_ptr<Cell> shCell;

#endif // CELL_H
