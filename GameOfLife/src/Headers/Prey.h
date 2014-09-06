#ifndef PREY_H
#define PREY_H

#include <iostream>
#include "Creature.h"
#include "LifePolicy.h"
#include "Definitions.h"
#include "Position.h"

class Prey : public Creature
{
public:

	Prey(unsigned int x, unsigned int y, unsigned int random) : 
		Creature(PREY_LIFE_CYCLE_EXTENTION, PREY_SPEED, x, y)
	{
		setLifePolicy((LifePolicy::LifePolicyOrientation)(random % ORIENTATION_NUMBER_FOR_PRAY));
	}

	Prey(Prey& first, Prey& second) : 
		Creature(first, second){ }

	std::shared_ptr<Prey> nextStep(std::shared_ptr<Prey> pair, int numberOfNeighbourhoods)
	{		
		if(getLife() == 0 || 
			(numberOfNeighbourhoods >= MAX_NUMBER_OF_NEIGHBOURHOODS_FOR_LIVE && !isBlackSwan()))
		{
			setInLife(false);
			return NULL;
		}
		
		std::shared_ptr<Prey> child = NULL;
		if(pair != NULL && !pair->isBlackSwan() &&
			numberOfNeighbourhoods >= MIN_NUMBER_OF_NEIGHBOURHOODS_TO_REPRODUCE &&
			numberOfNeighbourhoods <= MAX_NUMBER_OF_NEIGHBOURHOODS_TO_REPRODUCE)
		{
			child = getNextGeneration(pair);
		}
		decreaseLife();
		return child;
	}

	inline std::shared_ptr<Prey> getNextGeneration(std::shared_ptr<Prey> pair)
	{
		return std::shared_ptr<Prey>(new Prey(*this, *pair));
	}

	static inline std::shared_ptr<Prey> getRandomPair(std::vector<std::shared_ptr<Prey> >& nearPreys)
	{
		if(nearPreys.empty())
		{
			return NULL;
		}
		return std::shared_ptr<Prey>(nearPreys.at((std::abs( std::rand() ) % nearPreys.size()))); 
	}
};

typedef std::shared_ptr<Prey> shPrey;

#endif // PREY_H
