//#define DF_Debug

#include "prototypes.h"

#include "Imager.h" 
#include <opencv2\opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

broker *(Imager::Bro) = NULL;

Imager::Imager()
{
	MISS;
	
	MISE;
}

Imager::~Imager()
{
	MISS;
	
	MISE;
}


void Imager::test()
{
	MISS;
	Mat3b newPIC(3000, 320*2, Vec3b(0, 0, 0));

	// CHeck if file exist , else download
	Mat3b Card = imread(Tmp_path + "304.png");

	if (Card.empty())
	{
		MISEA("IMG EMPTY")
	}

	Card.copyTo(newPIC(Rect(0, 0, Card.cols, Card.rows)));
	imshow("Result", newPIC);
	waitKey(0);
	imwrite(Tmp_path + "0.png",newPIC);
	MISE;
}