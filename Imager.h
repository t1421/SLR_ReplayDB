#ifndef Imager_H
#define Imager_H

#include <opencv2\opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class Replay;

class Imager
{
public:
	Imager();
	~Imager();

	bool UseThisPMV(Replay * inReplay);
	bool MakeIMG();
	bool MakeMOV();
	CvScalar SwitchTypeColor(unsigned long inType);

	void Echo();

	string IMG_Path;
	string MOV_Path;
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:


private:
	Replay * RR;
};

#endif //Imager_H


