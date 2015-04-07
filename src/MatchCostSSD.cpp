/*
 * MatchCostSSD.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "MatchCostSSD.h"

MatchCostSSD::MatchCostSSD(int aWindowSize, int aNCols): IMatchCost(aWindowSize, aNCols)
{

}

MatchCostSSD::~MatchCostSSD() {

}

double MatchCostSSD::SSD(int aFirstValue, int aSecondValue)
{
	return (aFirstValue - aSecondValue)*(aFirstValue - aSecondValue);
}

/**
 * Determine match cost based on the Sum of squared differences.
 */
double MatchCostSSD::Cost(uchar* aLeftPointer, uchar* aRightPointer)
{
	return MapOverWindow(aLeftPointer, aRightPointer, &SSD);
}
