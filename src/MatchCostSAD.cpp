/*
 * MatchCostSAD.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "MatchCostSAD.h"

MatchCostSAD::MatchCostSAD(int aWindowSize, int aNCols): IMatchCost(aWindowSize, aNCols)
{

}

MatchCostSAD::~MatchCostSAD()
{

}


double MatchCostSAD::SAD(int aFirstValue, int aSecondValue)
{
	return std::abs(aFirstValue - aSecondValue);
}

/**
 * Determine match cost based on the Sum of absolute differences.
 */
double MatchCostSAD::Cost(uchar* aLeftPointer, uchar* aRightPointer)
{
	return MapOverWindow(aLeftPointer, aRightPointer, &SAD);
}
