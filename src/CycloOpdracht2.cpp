
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <limits>
#include <iostream>
#include "StereoMatcher.h"
#include "MatchCostFactory.h"
#include "MatchCostNCC.h"
#include "MatchCostSAD.h"
#include "MatchCostSSD.h"

void ShowImageWindow(cv::Mat aImage, std::string aWindowName)
{
  cv::namedWindow(aWindowName,cv::WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
  cv::resizeWindow(aWindowName,384,288);
  imshow(aWindowName, aImage);
}

int main()
{
	// Cyclomedia test images
	cv::Mat lFirstImage = cv::imread( "a.tif", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat lSecondImage = cv::imread( "b.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Tsukuba test images
	//cv::Mat lFirstImage = cv::imread( "test_left.tif", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat lSecondImage = cv::imread( "test_right.tif", CV_LOAD_IMAGE_GRAYSCALE);

	if (lFirstImage.empty() || lSecondImage.empty())
	{
		std::cout << "Cannot open images!" << std::endl;
		return -1;
	}

	StereoMatcher lMatcher(lFirstImage, lSecondImage);

	ShowImageWindow(lFirstImage, "First image");
	ShowImageWindow(lSecondImage, "Second image");

	int lWindowSize = 32;
	int lMaxDisparity = 700;

	// With factory
	//MatchCostFactory lFactory(MatchCostFactory::NCC);
	//lMatcher.MatchFactory(lWindowSize, lMaxDisparity, lFactory);

	// With template
	lMatcher.MatchTemplate<MatchCostNCC>(lWindowSize, lMaxDisparity);

	cv::Mat lDisparityImageResult = lMatcher.ComputeResultImage();

	imwrite("result_Cyclo_NCC_window32_maxdisparity700.tiff", lDisparityImageResult);
	ShowImageWindow(lDisparityImageResult,"Disparity image");
	cv::waitKey(0);

	lDisparityImageResult.release();
	return 0;
}


