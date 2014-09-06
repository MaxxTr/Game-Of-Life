#ifndef CREATURE_GUARD_H
#define CREATURE_GUARD_H

#include "Creature.h"

class CreatureGuard
{
private:
	Creature* m_guarded;
public:
	bool guard;

	CreatureGuard(Creature* c) : m_guarded(c), guard(false)
	{
		if(c != NULL)
		{
			omp_set_lock(m_guarded->getLock());
			guard = true;
		}
	}

	~CreatureGuard()
	{
		if(guard)
		{
			omp_unset_lock(m_guarded->getLock());
		}
	}

};

typedef std::shared_ptr<CreatureGuard> shCreatureGuard;

#endif