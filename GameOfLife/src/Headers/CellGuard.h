#ifndef CELL_GUARD_H
#define CELL_GUARD_H

#include "Cell.h"

class CellGuard
{
private:
	shCell m_guarded;
public:
	bool guard;

	CellGuard(shCell cell) : m_guarded(cell), guard(false)
	{
		if(cell != NULL)
		{
			omp_set_lock(m_guarded->getLock());
			guard = true;
		}
	}

	~CellGuard()
	{
		if(guard)
		{
			omp_unset_lock(m_guarded->getLock());
		}
	}

};

typedef std::shared_ptr<CellGuard> shCellGuard;

#endif
