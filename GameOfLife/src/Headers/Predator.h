#ifndef PREDATOR_H
#define PREDATOR_H

#include <iostream>
#include "Creature.h"
#include "LifePolicy.h"
#include "Definitions.h"
#include "Position.h"

class Predator: public Creature
{
private:
	
	unsigned int m_hunger;
	unsigned int m_maxHungerExtension;
	unsigned int m_reproductionHunger;
	unsigned int m_cellIndex;
	unsigned int m_oldCellIndex;
	unsigned int m_GroupID;

	bool m_AlreadyHasEaten;
	
public:
		
	Predator(unsigned int x, unsigned int y, unsigned int random, unsigned int groupID ) :
		Creature(PREDATOR_LIFE_CYCLE_EXTENTION, PREDATOR_SPEED, x, y),
		m_GroupID(groupID),
		m_cellIndex(0),	// this constructor called only on first initialization
						// and we allow only one predator in cell on this step
						// and we know that its index is 0
		m_oldCellIndex(0),
		m_hunger(0),
		m_reproductionHunger(0),
		m_maxHungerExtension(MAX_HUNGER_EXTENTION),
		m_AlreadyHasEaten(false)
	{
		((Creature*)this)->setLifePolicy((LifePolicy::LifePolicyOrientation)(random % LifePolicy::NUMBER_OF_ORIENTATIONS));
	}
	
	Predator(Predator& first, Predator& second) :
		Creature(first, second),
		m_GroupID(first.getGroupID()),
		m_cellIndex(2), // this constructor called only when new predator born
						// so we know that his index is 2
		m_hunger(std::max(first.getHunger(), second.getHunger())),
		m_maxHungerExtension(MAX_HUNGER_EXTENTION),
		m_AlreadyHasEaten(false) {}
	
	std::shared_ptr<Predator> nextStep(std::shared_ptr<Predator> pair, bool isPrayOnNewPos, bool areEnemies)
	{		
		m_AlreadyHasEaten = false;
		if(areEnemies || (pair != NULL && pair->isOmnivorous() && !isOmnivorous()))
		{
			war(pair);
			if(!isInLife())
			{
				return NULL;
			}			
		}
	
		if(getLife() == 0 || (m_hunger == m_maxHungerExtension && !isBlackSwan()))
		{
			setInLife(false);
			return NULL;
		}

		std::shared_ptr<Predator> child = NULL;
		if(pair != NULL && pair->isInLife() && !areEnemies && !pair->isBlackSwan() &&
			(isNotHungry() || isPrayOnNewPos ))
		{
			child = getNextGeneration(pair);
			++m_hunger;
			m_reproductionHunger = 0;
		}
		else
		{
			++m_reproductionHunger;
		}
		if(pair != NULL && isOmnivorous())
		{
			war(pair);			
		}
		if(isPrayOnNewPos && !isNotHungry())
		{
			m_hunger = 0;
			m_AlreadyHasEaten = true;
		}
		else
		{
			++m_hunger;
		}
		decreaseLife();
		return child;
	}

	inline void war(std::shared_ptr<Predator> p)
	{
		unsigned int myStrength = getStrength();
		unsigned int enemyStrength = p->getStrength();
		bool iStronger = std::max(myStrength, enemyStrength) == myStrength;
		
		if(std::max(myStrength, enemyStrength) == myStrength)
		{
			unsigned int res = std::abs(std::rand()) % (myStrength+1);
			if(res > enemyStrength)
			{
				p->setInLife(false);
				increaseStrength();
			}
			else
			{
				setInLife(false);
				p->increaseStrength();
			}
		}
		else 
		{
			unsigned int res = std::abs(std::rand()) % (enemyStrength+1);
			if(res < myStrength)
			{
				p->setInLife(false);
				increaseStrength();
			}
			else
			{
				setInLife(false);
				p->increaseStrength();
			}
		}
	}
	
	inline std::shared_ptr<Predator> getNextGeneration(std::shared_ptr<Predator> pair)
	{
		return std::shared_ptr<Predator>(new Predator(*this, *pair));
	}

	inline unsigned int getCellIndex()
	{
		return m_cellIndex;
	}

	inline unsigned int getOldCellIndex()
	{
		return m_oldCellIndex;
	}

	inline void setCellIndex(unsigned int index)
	{
		m_oldCellIndex = m_cellIndex;
		m_cellIndex = index;
	}

	inline bool isNotHungry()
	{
		return (m_hunger <= DOESNT_HUNGRY);
	}

	inline unsigned int getHunger()
	{
		return m_hunger;
	}

	inline unsigned int getReproductionHuner()
	{
		return m_reproductionHunger;
	}

	inline bool isReproductionHungry()
	{
		return m_reproductionHunger > MAX_WITHOUT_REPRODUCTION;
	}

	inline unsigned int getGroupID()
	{
		return m_GroupID;
	}

	inline bool hasEaten()
	{
		return m_AlreadyHasEaten;
	}

};
typedef std::shared_ptr<Predator> shPredator;

#endif // PREDATOR_H
