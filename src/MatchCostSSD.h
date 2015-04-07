/*
 * MatchCostSSD.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef MATCHCOSTSSD_H_
#define MATCHCOSTSSD_H_

#include "IMatchCost.h"

class MatchCostSSD: public IMatchCost
{
public:
	MatchCostSSD(int aWindowSize, int aNCols);
	virtual ~MatchCostSSD();
	double Cost(uchar* aLeftPointer, uchar* aRightPointer);
private:
	static double SSD(int aFirstValue, int aSecondValue);
};

#endif /* MATCHCOSTSSD_H_ */
