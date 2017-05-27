#ifndef __STRATEGY_H
#define __STRATEGY_H

#include "pfile.h"

class PStrategy
{
	public:
		PStrategy();
		~PStrategy();
		virtual compare(const PFile &f1,const PFile &f2);
};

#endif
