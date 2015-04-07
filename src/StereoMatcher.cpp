/*
 * StereoMatcher.cpp
 *
 *  Created on: 4 apr. 2015
 *      Author: Geerten.Doornenbal
 */

#include "StereoMatcher.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <limits>
#include "MatchCostSAD.h"

StereoMatcher::StereoMatcher(cv::Mat& aLeftImage, cv::Mat& aRightImage): mLeftImage(aLeftImage), mRightImage(aRightImage)
{
	mCostFunction = NULL;
	mHighestDisparity = 0;
	mLowestDisparity = std::numeric_limits<int>::max();

	mNRows = mLeftImage.rows;
	mNCols = mLeftImage.cols * mLeftImage.channels();
}

void StereoMatcher::MatchFactory(int aWindowSize, int aMaxDisparity, MatchCostFactory& aFactory)
{
	mCostFunction = aFactory.CreateMatchCost(aWindowSize,mNCols);
	Match(aWindowSize, aMaxDisparity);
}

void StereoMatcher::Match(int aWindowSize, int aMaxDisparity)
{
	mHighestDisparity = 0;
	mLowestDisparity = std::numeric_limits<int>::max();;
	mDisparityImage = *MatchImages(mLeftImage, mRightImage, aWindowSize, aMaxDisparity);
	CrossChecking();
}

cv::Mat* StereoMatcher::MatchImages(cv::Mat& aLeftImage, cv::Mat& aRightImage, int aWindowSize,int aMaxDisparity)
{
	cv::Mat* lDisparityImage = new cv::Mat(aLeftImage.rows, aLeftImage.cols, CV_32S);
	lDisparityImage->setTo(0);
	//IMatchCost* lCost = mCostFactory.CreateMatchCost(aWindowSize, mNCols);
	for(int lY = aWindowSize; lY < mNRows - aWindowSize; lY++)
	{
	  uchar* lLeftPointer = mLeftImage.ptr<uchar>(lY);
	  uchar* lRightPointer = mRightImage.ptr<uchar>(lY);
	  for(int lX = aWindowSize; lX < mNCols - aWindowSize; lX++)
	  {
		  double lLowestSum = std::numeric_limits<double>::max();
		  int lBestDisparity = 0;
		  int lStartX = std::max(lX-aMaxDisparity,aWindowSize);
#pragma omp parallel for
		  for(int lSecondX = lStartX; lSecondX <= lX; lSecondX++)
		  {
			  int lDisparity = lX - lSecondX;

			  double lSum = mCostFunction->Cost(lLeftPointer+lX, lRightPointer+lSecondX);
			  if(lLowestSum > lSum)
			  {
				  lLowestSum = lSum;
				  lBestDisparity = lDisparity;
			  }
		  }
		  int* lDisparityPointer = lDisparityImage->ptr<int>(lY);
		  if(lBestDisparity > mHighestDisparity)
		  {
			  mHighestDisparity = lBestDisparity;
		  }
		  if(lBestDisparity < mLowestDisparity)
		  {
			  mLowestDisparity = lBestDisparity;
		  }
		  lDisparityPointer[lX] = lBestDisparity;
	  }
	}
	//delete lCost;
	return lDisparityImage;
}

/**
 * Use cross checking to determine occluded areas. Unknown disparities are set to -1.
 */
void StereoMatcher::CrossChecking()
{
	for(int lY = 0; lY < mNRows; lY++)
	{
	  int* lLeftRightPointer = mDisparityImage.ptr<int>(lY);
#pragma omp parallel for
	  for(int lX = 0; lX < mNCols; lX++)
	  {
		  if(lLeftRightPointer[lX] < lLeftRightPointer[lX + lLeftRightPointer[lX]])
		  {
			  lLeftRightPointer[lX] = -1;
		  }
	  }
	}
}

/**
 * Compute the result image to be able to display the results of the match.
 * Unknown disparities are set to red. Disparities are scaled to 0-255.
 */
cv::Mat StereoMatcher::ComputeResultImage()
{
	cv::Mat lDisparityImageResult(mLeftImage.rows, mLeftImage.cols, CV_8UC3);
	int lNRows = lDisparityImageResult.rows;

	for(int lY = 0; lY < lNRows; lY++)
	{
	  int* lLeftRightPointer = mDisparityImage.ptr<int>(lY);
	  uchar* lResultPointer = lDisparityImageResult.ptr<uchar>(lY);
#pragma omp parallel for
	  for(int lX = 0; lX < mNCols; lX++)
	  {
		  if(lLeftRightPointer[lX] == -1)
		  {
			  lResultPointer[lX*3] = 0;
			  lResultPointer[lX*3 + 1] = 0;
			  lResultPointer[lX*3 + 2] = 255;
		  }
		  else
		  {
			  lResultPointer[lX*3] = (((float)(lLeftRightPointer[lX]-mLowestDisparity))/(float)(mHighestDisparity-mLowestDisparity)) * 255;
			  lResultPointer[lX*3 + 1] = (((float)(lLeftRightPointer[lX]-mLowestDisparity))/(float)(mHighestDisparity-mLowestDisparity)) * 255;
			  lResultPointer[lX*3 + 2] = (((float)(lLeftRightPointer[lX]-mLowestDisparity))/(float)(mHighestDisparity-mLowestDisparity)) * 255;
		  }
	  }
	}
	return lDisparityImageResult;
}

StereoMatcher::~StereoMatcher()
{
	if(mCostFunction != NULL)
	{
		delete mCostFunction;
	}

	if(!mDisparityImage.empty())
	{
		mDisparityImage.release();
	}
	if(!mLeftImage.empty())
	{
		mLeftImage.release();
	}
	if(!mRightImage.empty())
	{
		mRightImage.release();
	}
}
