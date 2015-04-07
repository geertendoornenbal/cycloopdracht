/*
 * MatchCostNCC.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef MATCHCOSTNCC_H_
#define MATCHCOSTNCC_H_

#include "IMatchCost.h"

class MatchCostNCC: public IMatchCost
{
public:
	MatchCostNCC(int aWindowSize, int aNCols);
	virtual ~MatchCostNCC();
	double Cost(uchar* aLeftPointer, uchar* aRightPointer);
};

#endif /* MATCHCOSTNCC_H_ */
