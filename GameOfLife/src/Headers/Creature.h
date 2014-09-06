#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string> 
#include "Characteristic.h"
#include "LifePolicy.h"
#include "Definitions.h"
#include "Position.h"

class Creature
{
private:
 
	Characteristic m_char;
	bool m_bInLife;

	shPosition m_pos;
	//omp_lock_t LCK;
	
public:

	Creature(unsigned int life, unsigned int speed) : 
		m_bInLife(true),
		m_char( life, speed ){/*omp_init_lock (&LCK);*/}
		
	Creature(Characteristic character) : 
		m_bInLife(true),
		m_char(character){/*omp_init_lock (&LCK);*/}
	
	Creature(
		unsigned int life,
		unsigned int speed,
		unsigned int x,
		unsigned int y) :
		m_pos(new Position(x, y)),
		m_char(life, speed),
		m_bInLife(true){/*omp_init_lock (&LCK);*/}
		
	Creature(Creature& first, Creature& second) :
		m_pos(first.getPosition()),
		m_char(first.getCharasteristic(), second.getCharasteristic()),
		m_bInLife(true) {/*omp_init_lock (&LCK);*/}
/*
	inline omp_lock_t* getLock()
	{
		return &LCK;
	}
*/
// setters
	inline void setInLife(bool val)
	{
		m_bInLife = val;
	}
	
	inline void setPosition(shPosition pos)
	{
		m_pos = pos;
	}

// getters	
	
	inline shPosition getPosition()
	{
		return shPosition(m_pos); 
	}
	
	inline bool isInLife()
	{
		return m_bInLife;
	}
	
	inline unsigned int getLife()
	{
		return m_char.getLife();
	}
	
	inline Characteristic getCharasteristic()
	{
		return m_char;
	}
	
	inline unsigned int getSpeed()
	{
		return m_char.getSpeed();
	}
	
	inline unsigned int getVision()
	{
		return m_char.getVision();
	}
	
	inline unsigned int getStrength()
	{
		return m_char.getStrength();
	}

	inline void increaseStrength()
	{
		m_char.increaseStrength();
	}

	inline LifePolicy::LifePolicyOrientation getLifePolicy()
	{
		return m_char.getLifePolicy();
	}

	inline std::string getLifePolicyStr()
	{
		return m_char.getLifePolicyStr();
	}

	inline bool isOmnivorous()
	{
		return m_char.isOmnivorous();
	}

	inline unsigned int getLifeCycleExtension()
	{
		return m_char.getLifeCycleExtension();
	}

	inline bool isBlackSwan()
	{
		return m_char.isBlackSwan();
	}

//functions

	inline void setLifePolicy(LifePolicy::LifePolicyOrientation or)
	{
		return m_char.setLifePolicy(or);
	}

	inline void decreaseLife()
	{
		m_char.decreaseLife();
	}

	inline bool bestThan(Creature& to)
	{
		return m_char.bestThan(to.getCharasteristic());
	}
};

#endif //CREATURE_H
