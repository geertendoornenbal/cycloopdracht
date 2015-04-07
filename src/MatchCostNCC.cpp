/*
 * MatchCostNCC.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "MatchCostNCC.h"

MatchCostNCC::MatchCostNCC(int aWindowSize, int aNCols): IMatchCost(aWindowSize, aNCols)
{

}

MatchCostNCC::~MatchCostNCC()
{

}

/**
 * Compute the cost using normalized cross correlation.
 * Function could be refactored/optimized a bit more (similar to the map function for SAD en SSD).
 */
double MatchCostNCC::Cost(uchar* aLeftPointer, uchar* aRightPointer)
{
	long double lSumRight = 0;
	long double lSumLeft = 0;
	for(int lWindowY = -mWindowSize; lWindowY <= mWindowSize; lWindowY++)
	{
	  for(int lWindowX = -mWindowSize; lWindowX <= mWindowSize; lWindowX++)
	  {
		  int lPointerIndex = lWindowY*mNCols + lWindowX;

		  lSumLeft += aLeftPointer[lPointerIndex];
		  lSumRight += aRightPointer[lPointerIndex];
	  }
	}
	long double lTotalPixels = mWindowSize*2 + 1;
	long double lMeanLeft = lSumLeft / lTotalPixels;
	long double lMeanRight = lSumRight / lTotalPixels;

	long double lSumTotal = 0;
	long double lSumLeftSquared = 0;
	long double lSumRightSquared = 0;
	for(int lWindowY = -mWindowSize; lWindowY <= mWindowSize; lWindowY++)
	{
	  for(int lWindowX = -mWindowSize; lWindowX <= mWindowSize; lWindowX++)
	  {
		  int lPointerIndex = lWindowY*mNCols + lWindowX;
		  long double lFirstValue = aLeftPointer[lPointerIndex];
		  long double lSecondValue = aRightPointer[lPointerIndex];
		  long double lDiffLeft = (lFirstValue - lMeanLeft);
		  long double lDiffRight = (lSecondValue - lMeanRight);
		  lSumTotal += lDiffLeft*lDiffRight;
		  lSumLeftSquared += lDiffLeft*lDiffLeft;
		  lSumRightSquared += lDiffRight*lDiffRight;
	  }
	}
	return -1*( lSumTotal / (std::sqrt(lSumLeftSquared)*std::sqrt(lSumRightSquared)));
}
