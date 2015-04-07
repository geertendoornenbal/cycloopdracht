/*
 * StereoMatcher.h
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#ifndef STEREOMATCHER_H_
#define STEREOMATCHER_H_

#include "opencv2/core/core.hpp"
#include "IMatchCost.h"
#include "MatchCostFactory.h"

class StereoMatcher
{
	public:
		StereoMatcher(cv::Mat& aLeftImage, cv::Mat& aRightImage);
		virtual ~StereoMatcher();
		// needs to be in header to be found by files that use it
		template<class T> void MatchTemplate(int aWindowSize, int aMaxDisparity)
		{
			mCostFunction = new T(aWindowSize, mNCols);
			Match(aWindowSize, aMaxDisparity);
		}
		void MatchFactory(int aWindowSize, int aMaxDisparity, MatchCostFactory& aFactory);
		cv::Mat ComputeResultImage();
	private:
		cv::Mat& mLeftImage;
		cv::Mat& mRightImage;
		cv::Mat mDisparityImage;
		int mHighestDisparity;
		int mLowestDisparity;
		int mNRows;
		int mNCols;
		//MatchCostFactory& mCostFactory;
		IMatchCost* mCostFunction;
		void Match(int aWindowSize, int aMaxDisparity);
		cv::Mat* MatchImages(cv::Mat& aLeftImage, cv::Mat& aRightImage, int aWindowSize,int aMaxDisparity);
		void CrossChecking();
};

#endif /* STEREOMATCHER_H_ */
