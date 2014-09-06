#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include <random>
#include <ctime>
#include <string>
#include "LifePolicy.h"

class Characteristic
{
private:

	unsigned int m_speed;
	unsigned int m_strength;
	unsigned int m_vision;
	unsigned int m_life;
	unsigned int m_lifeCycleExtension;
	
	LifePolicy::LifePolicyOrientation m_policy;
	
	bool m_bIsOmnivorous; // can eat the creatures of it's kind

public:
	
	Characteristic(unsigned int life , unsigned int speed) :
		m_speed(speed),
		m_strength(1),
		m_vision(DEFAULT_VISION),
		m_life(life),
		m_lifeCycleExtension(life),
		m_policy(LifePolicy::RANDOM_ORIENTED),
		m_bIsOmnivorous(false){ }
		
	Characteristic(Characteristic& first, Characteristic& second)
	{
		m_speed = getNewProperty(first.getSpeed(), second.getSpeed(), SPEED_MUTATION_PROBABILITY);
		m_strength = getNewProperty(first.getStrength(), second.getStrength(), STRANGTH_MUTATION_PROBABILITY);
		m_vision = getNewProperty(first.getVision(), second.getVision(), VISION_MUTATION_PROBABILITY);
		m_policy = getNewPolicy(first.getLifePolicy(), second.getLifePolicy(), ORIENTATION_MUTATION_PROBABILITY);
		m_lifeCycleExtension = getNewProperty(first.getLifeCycleExtension(), second.getLifeCycleExtension(), LIFE_MUTATION_PROBABILITY);
		m_life = m_lifeCycleExtension;
		m_bIsOmnivorous = getOmnivorousMutation(first.isOmnivorous(), second.isOmnivorous(), OMNIVOROUS_PROBABILITY);
		if(isBlackSwanHere())
		{
			m_policy = LifePolicy::BLACK_SPAWN;
			m_speed = m_speed << 1; // m_speed = 2*m_speed
			m_vision = m_vision << 2;
			m_strength = m_strength << 1;
			m_life = m_life << 2;
			m_bIsOmnivorous = false;
		}	
	}
	
	inline unsigned int getOmnivorousMutation(bool first, bool second, unsigned int mutationProbability)
	{
		if(first || second)
		{
			return true;
		}
		unsigned int mut = (std::abs( std::rand() ) & mutationProbability);
		return mut == 0 ? true : false;
	}
	
	inline unsigned int getNewProperty(unsigned int first, unsigned int second, unsigned int mutationProbability)
	{
		bool getFirst = ((std::abs( std::rand() ) & PARENT_PROBABILITY) == 0); // 50x50 to take one of the parent Characteristic
        unsigned int mut = (std::abs( std::rand() ) & mutationProbability);
		bool signPlus = true;//((std::abs( std::rand() ) & 0x1) == 0);
		if(mut == 0)
		{
			if(signPlus)
			{
				return getFirst ? ++first : ++second;
			}
			else
			{
				if(getFirst)
				{
					return (first-1) <= 0 ? 1 : --first;
				}
				else
				{
					return (second-1) <= 0 ? 1 : --second;
				}
			}
		}
		else
		{
			return getFirst ? first : second;
		}
	}
	
	inline LifePolicy::LifePolicyOrientation getNewPolicy(
		LifePolicy::LifePolicyOrientation first,
		LifePolicy::LifePolicyOrientation second,
		unsigned int mutationProbability)
	{
		bool getFirst = ((std::abs( std::rand() ) & PARENT_PROBABILITY) == 0); // 50x50 to take one of the parent Characteristic
		return getFirst ? first : second;
	}

	inline bool isBlackSwanHere()
	{
		return (std::abs( std::rand() ) & BLACK_SPAWN_PROBABILITY) == 0 ? true : false;
	}

	inline bool isOmnivorous()
	{
		return m_bIsOmnivorous;
	}
		
	inline unsigned int getLife()
	{
		return m_life;
	}

	inline void decreaseLife()
	{
		--m_life;
	}
	
	inline unsigned int getSpeed()
	{
		return m_speed;
	}
	
	inline unsigned int getVision()
	{
		return m_vision;
	}
	
	inline unsigned int getStrength()
	{
		return m_strength;
	}

	inline void increaseStrength()
	{
		m_strength += 1;
	}
	
	inline LifePolicy::LifePolicyOrientation getLifePolicy()
	{
		return m_policy;
	}

	inline bool isBlackSwan()
	{
		return m_policy == LifePolicy::BLACK_SPAWN;
	}

	inline std::string getLifePolicyStr()
	{
		switch(m_policy)
		{
			case LifePolicy::FOOD_ORIENTED:
				return "FOOD_ORIENTED";
			case LifePolicy::REPRODUCTION_ORIENTED:
				return "REPRODUCTION_ORIENTED";
			case LifePolicy::SINGLENESS_ORIENTED:
				return "SINGLENESS_ORIENTED";
			case LifePolicy::RANDOM_ORIENTED:
				return "RANDOM_ORIENTED";
			case LifePolicy::SAFETY_ORIENTED:
				return "SAFETY_ORIENTED";
			case LifePolicy::BLACK_SPAWN:
				return "BLACK_SPAWN";
		}
		return "ERROR";
	}

	inline void setLifePolicy(LifePolicy::LifePolicyOrientation or)
	{
		m_policy = or;
	}

	inline unsigned int getLifeCycleExtension()
	{
		return m_lifeCycleExtension;
	}

	inline bool bestThan(Characteristic& to)
	{
		unsigned int myScore = m_speed*m_strength*m_vision;
		unsigned int toScore = (to.getSpeed())*(to.getStrength())*(to.getVision());
		return myScore > toScore;
	}
};

#endif //CHARACTERISTIC_H

