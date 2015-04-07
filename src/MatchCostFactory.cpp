/*
 * MatchCostFactory.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "MatchCostFactory.h"

#include "MatchCostNCC.h"
#include "MatchCostSAD.h"
#include "MatchCostSSD.h"

MatchCostFactory::MatchCostFactory(eMatchCostTypes aType): mType(aType)
{


}

IMatchCost* MatchCostFactory::CreateMatchCost(int aWindowSize, int aNCols)
{
	IMatchCost* lResult;
	if(mType == MatchCostFactory::NCC)
	{
		lResult = new MatchCostNCC(aWindowSize, aNCols);
	}
	else if(mType == MatchCostFactory::SAD)
	{
		lResult = new MatchCostSAD(aWindowSize, aNCols);
	}
	else
	{
		lResult = new MatchCostSSD(aWindowSize, aNCols);
	}
	return lResult;
}

MatchCostFactory::~MatchCostFactory()
{

}

