#define DF_Debug

#include "prototypes.h"

#include "Replay.h" 

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
	Mat3b Card = imread(Bro->L_getTMP_PATH() + "304.png");

	if (Card.empty())
	{
		MISEA("IMG EMPTY")
	}

	Card.copyTo(newPIC(Rect(0, 0, Card.cols, Card.rows)));
	putText(newPIC,
		"Hallo Welt Was geht ab",
		Point(320, 320 / 2),
		FONT_HERSHEY_TRIPLEX, //FONT_HERSHEY_DUPLEX,
		0.5,
		CV_RGB(118, 185, 0),
		1);

	imshow("Result", newPIC);
	waitKey(0);
	imwrite(Bro->L_getTMP_PATH() + "0.png",newPIC);
	MISE;
}

bool Imager::UseThisPMV(Replay * inReplay)
{
	MISS;
	RR = inReplay;
	if (!RR->OK)
	{
		MISEA("Replay not OK");
		return false;
	}
	MISE;
	return true;
}


bool Imager::MakeIMG()
{
	MISS;
	unsigned int iTimeMax = RR->Playtime * 2;
	Mat3b Card;
	

	Mat3b newPIC(iTimeMax + 320, 320 * 2, Vec3b(0, 0, 0));

	for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
	{
		putText(newPIC,
			to_string(RR->ActionMatrix[i]->Type),
			Point(320, 320 / 2 + RR->ActionMatrix[i]->Time * 2),
			FONT_HERSHEY_TRIPLEX, //FONT_HERSHEY_DUPLEX,
			0.5,
			CV_RGB(118, 185, 0),
			1);

		if (RR->ActionMatrix[i]->Type == 4009 //Unit
			|| RR->ActionMatrix[i]->Type == 4010 //Spell
			|| RR->ActionMatrix[i]->Type == 4011 //Line Spell
			|| RR->ActionMatrix[i]->Type == 4012) //Building			
		{
			if (!File_exists(Bro->L_getTMP_PATH() + to_string(RR->ActionMatrix[i]->Card) + ".png"))
			{
				if (Bro->C_DownloadPNG(RR->ActionMatrix[i]->Card))
				{
					MISE("Error during DOwnload of: " + to_string(RR->ActionMatrix[i]->Card));
				}
			}
			Card = imread(Bro->L_getTMP_PATH() + to_string(RR->ActionMatrix[i]->Card) + ".png");
			Card.copyTo(newPIC(Rect(0, RR->ActionMatrix[i]->Time * 2, Card.cols, Card.rows)));

		}
	}

	imwrite(Bro->L_getTMP_PATH() + "GAME_" + RR->sSQLGameID + ".png", newPIC);
		
	MISE;
	return true;
}