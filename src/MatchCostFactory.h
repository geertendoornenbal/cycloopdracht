/*
 * MatchCostFactory.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef MATCHCOSTFACTORY_H_
#define MATCHCOSTFACTORY_H_

#include "IMatchCost.h"

class MatchCostFactory
{
public:
	enum eMatchCostTypes { SSD, SAD, NCC };

	MatchCostFactory(eMatchCostTypes aType);
	virtual ~MatchCostFactory();

	IMatchCost* CreateMatchCost(int aWindowSize, int aNCols);
private:
	eMatchCostTypes mType;
};

#endif /* MATCHCOSTFACTORY_H_ */
