/*
 * MatchCost.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef IMATCHCOST_H_
#define IMATCHCOST_H_

#include "opencv2/core/core.hpp"

class IMatchCost
{
public:
	IMatchCost(int aWindowSize, int aNCols);
	virtual ~IMatchCost();
	virtual double Cost(uchar* aLeftPointer, uchar* aRightPointer) = 0;
protected:
	double MapOverWindow(uchar* aLeftPointer, uchar* aRightPointer, double (*aMapFunction)(int, int));
	int mWindowSize;
	int mNCols;
};

#endif /* IMATCHCOST_H_ */
