/*
 * MatchCost.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "IMatchCost.h"

IMatchCost::IMatchCost(int aWindowSize, int aNCols): mWindowSize(aWindowSize), mNCols(aNCols)
{


}

/**
 * Map a given function of the window around it and sum the results. The total sum is returned.
 */
double IMatchCost::MapOverWindow(uchar* aLeftPointer, uchar* aRightPointer, double (*aMapFunction)(int, int))
{
	double lSum = 0;
	for(int lWindowY = -mWindowSize; lWindowY <= mWindowSize; lWindowY++)
	{
	  for(int lWindowX = -mWindowSize; lWindowX <= mWindowSize; lWindowX++)
	  {
		  int lPointerIndex = lWindowY*mNCols + lWindowX;

		  int lLeftValue =aLeftPointer[lPointerIndex];
		  int lRightValue = aRightPointer[lPointerIndex];
		  lSum += aMapFunction(lLeftValue,lRightValue);
	  }
	}
	return lSum;
}

IMatchCost::~IMatchCost()
{

}

