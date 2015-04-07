/*
 * MatchCostSAD.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef MATCHCOSTSAD_H_
#define MATCHCOSTSAD_H_

#include "IMatchCost.h"

class MatchCostSAD: public IMatchCost
{
public:
	MatchCostSAD(int aWindowSize, int aNCols);
	virtual ~MatchCostSAD();
	double Cost(uchar* aLeftPointer, uchar* aRightPointer);
private:
	static double SAD(int aFirstValue, int aSecondValue);
};

#endif /* MATCHCOSTSAD_H_ */
