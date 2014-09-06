#ifndef LIFEPOLICY_H
#define LIFEPOLICY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Definitions.h"
#include "Cell.h"


class LifePolicy
{

public:

	#define ORIENTATION_NUMBER_FOR_PRAY 3
	
	typedef enum
	{
		SAFETY_ORIENTED			= 0, // only for preys, others could be for prey and for predators
		RANDOM_ORIENTED			= 1,
		REPRODUCTION_ORIENTED	= 2, 
		SINGLENESS_ORIENTED		= 3, // this and the next orientations only for predators
		FOOD_ORIENTED			= 4,
		NUMBER_OF_ORIENTATIONS	= 5,
		BLACK_SPAWN				= 6
		
	} LifePolicyOrientation;
	
private:

	bool maxFoodOriented();
};
/*
class MaxAppropriate : public unary_function<Cell&, void>
{
public:
	MaxAppropriate(ComparatorFunctionType compareFunction) : 
		m_firstBetterThanSecond(compareFunction);
	
	void operator()(Cell& elem);
	
	Cell& getMax()
	{
		return m_maxCell;
	}

private:

	Cell& m_maxCell;
	bool m_first;
	ComparatorFunctionType m_firstBetterThanSecond;
};

MaxAppropriate::MaxAppropriate(ComparatorFunctionType compareFunction) : 
		m_firstBetterThanSecond(compareFunction), m_maxIndex(-1), m_first(true){}

void MaxAppropriate::operator()(Cell& elem)
{
	if (first) 
	{
		m_maxCell = elem;
		first = false;
	}
	else if (m_firstBetterThanSecond(m_maxCell, elem)) 
	{
		m_maxCell = elem;
	}
}
*/

#endif // LIFEPOLICY_H
