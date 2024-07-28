#define DF_Debug

#include "..\incl\Broker.h" 

#include "..\incl\Imager.h" 
#include "..\incl\Replay.h" 

#include "..\incl\Utility.h" 

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
	unsigned int iTimeMax = RR->Playtime * 4;
	Mat Card;

	//Mat newPIC(iTimeMax + 320, 320 * 2, CV_8UC4,  cv::Scalar(0, 0, 0, 0)); 
	//line(newPIC, Point(0, 320 / 2), Point(320 * 2, 320 / 2), Scalar(255, 255, 255,255), 2); //Start
	//line(newPIC, Point(0, iTimeMax + 320 / 2), Point(320 * 2, iTimeMax + 320 / 2), Scalar(255, 255, 255, 255), 2); //End
	Mat newPIC(iTimeMax + 320, 320 + 80, CV_8UC4,  cv::Scalar(0, 0, 0, 0)); 
	line(newPIC, Point(0, 320 / 2), Point(320 * 2, 320 / 2), Scalar(255, 255, 255,255), 2); //Start
	line(newPIC, Point(0, iTimeMax + 320 / 2), Point(320 * 2, iTimeMax + 320 / 2), Scalar(255, 255, 255, 255), 2); //End

	for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
	{		
		putText(newPIC,
			RR->SwitchType(RR->ActionMatrix[i]->Type),
			Point(0, 320 / 2 + RR->ActionMatrix[i]->Time * 4),
			FONT_HERSHEY_TRIPLEX, //FONT_HERSHEY_DUPLEX,
			1,
			SwitchTypeColor(RR->ActionMatrix[i]->Type),
			1);

		if (RR->ActionMatrix[i]->Type == 4009 //Unit
			|| RR->ActionMatrix[i]->Type == 4010 //Spell
			|| RR->ActionMatrix[i]->Type == 4011 //Line Spell
			|| RR->ActionMatrix[i]->Type == 4012 //Building			
			|| RR->ActionMatrix[i]->Type == 4044) //TW Switch 
		{
			if (!File_exists(Bro->L_getSMJIMG_PATH() + std::to_string(RR->ActionMatrix[i]->Card) + ".png"))
			{
				if (Bro->J_GetImgOnly(RR->ActionMatrix[i]->Card) == "")
				{
					MISE("Error during DOwnload of: " + std::to_string(RR->ActionMatrix[i]->Card));
				}
			}

			Card = imread(Bro->L_getSMJIMG_PATH() + std::to_string(RR->ActionMatrix[i]->Card) + ".png", IMREAD_UNCHANGED);
			Card.copyTo(newPIC(Rect(240, RR->ActionMatrix[i]->Time * 4 + 120, Card.cols, Card.rows)));
		}

		if (RR->ActionMatrix[i]->Type == 4030) //WELL			
		{		
			//MISD("WELL");
			Card = imread(Bro->L_getSMJIMG_PATH() +  "W.png", IMREAD_UNCHANGED);
			Card.copyTo(newPIC(Rect(240, RR->ActionMatrix[i]->Time * 4 + 120, Card.cols, Card.rows)));
		}

		if (RR->ActionMatrix[i]->Type == 4031) //ORB
		{
			//MISD("ORB");
			Card = imread(Bro->L_getSMJIMG_PATH() + "O.png", IMREAD_UNCHANGED);
			Card.copyTo(newPIC(Rect(240, RR->ActionMatrix[i]->Time * 4 + 120, Card.cols, Card.rows)));
		}
	}

	if (RR->sSQLGameID != "")IMG_Path = Bro->L_getSMJIMG_PATH() + "GAME_" + RR->sSQLGameID + ".png";
	else IMG_Path = Bro->L_getSMJIMG_PATH() + "GAME_" + RR->FileName + ".png";
	
	imwrite(IMG_Path, newPIC);
	if (!File_exists(IMG_Path))
	{
		MISEA(" IMG not Saved!");
		return false;
	}
		
	MISE;
	return true;
}

bool Imager::MakeMOV()
{
	MISS;
	if (IMG_Path == "")
	{
		MISEA("No Image Generated");
		return false;
	}

	if (RR->sSQLGameID != "")MOV_Path = Bro->L_getTMP_PATH() + "GAME_" + RR->sSQLGameID + ".mov";
	else MOV_Path = Bro->L_getTMP_PATH() + "GAME_" + RR->FileName + ".mov";

	IMG_Path = ReplaceString(IMG_Path, "\\", "/");
	IMG_Path = ReplaceString(IMG_Path, ":/", "\\\\:/");
	
	std::stringstream ssCMD;

	ssCMD << " call \"" << Bro->L_getFFMPEG() << "\" ";
	ssCMD << " -y -f lavfi -i ";
	ssCMD << " \"color = black@0.0";
	ssCMD << " :d = " << int(RR->Playtime / 10);
	//ssCMD << " :s = 640x1080,format=rgba";
	ssCMD << " :s = 400x1080,format=rgba";
	ssCMD << " [background]; ";
	ssCMD << " movie = \"" << IMG_Path << "\"";
	ssCMD << " [overlay]; ";
	ssCMD << " [background][overlay]";
	ssCMD << " overlay = '(W-w)/2:H-n*1.6-" << 1080 / 2 << "-" << 320 / 2 << "'\"";
	ssCMD << " -c:v png -r 25 " << "\"" << MOV_Path << "\"";

	MISD(ssCMD.str());
	system(ssCMD.str().c_str());

	MISE;
	return true;
}


CvScalar Imager::SwitchTypeColor(unsigned long inType)
{
	//MISS;

	switch (inType)
	{
	
	//ROT
	case 4015://"Attack";
	case 4041://"Kill own unit";
		return cvScalar((0), (0), (255), 255);

	//GELB
	case 4004://"12Player sync";		
	case 4006://"Open Gold";
	case 4007://"Objective OK";
	case 4027://"Ping";
	case 4043://"Cant collect Gold";
		return cvScalar((0), (255), (255), 255);

	//BLAU
	case 4009://"Summon unit";
	case 4010://"Cast spell";
	case 4011://"Cast line spell";
	case 4012://"Cast building";	
	case 4030://"Build well";
	case 4031://"Build orb";
	case 4044://"TW SWITCH";
		return cvScalar((255), (0), (0), 255);		
	
	//GR�N
	case 4013://"Move unit";
	case 4019://"Stop unit";
	case 4020://"Hold position";
	case 4033://"Move units on wall";
	case 4036://"Move unit into Decomposer";
	case 4038://"Use tunnel";
		return cvScalar((0), (255), (0), 255);

	//T�RKIS
	case 4014://"Use ability";
	case 4028://"Switch Gate";	
	case 4029://"Build/Rep. wall";
	case 4034://"Switch ability";
	case 4035://"Start repair";
	case 4037://"Place Nexus exit";
	case 4039://"Switch tunnel";
	case 4040://"Deaktiviert Nexus exit";
	case 4042://"Placing Altar Of Chaos Totem";	
	//case 4044://"Switch TW";
		return cvScalar((255), (255), (0), 255);

	//Transparent
	case 4001://"?4001 ?";
	case 4002://"Leave game";
	case 4003://"Desync";
	case 4005://"?4005 Loot";
	case 4008://"?4008 Map Debug";
	case 4016://"?4016 ?";
	case 4017://"?4017 GM Stuff";
	case 4018://"old KillEntity";
	case 4021://"old PlaceSqua";
	case 4022://"Mapscripts";
	case 4023://"StopCutScene";
	case 4024://"4024 Forge";
	case 4025://"4025 Forge";
	case 4026://"SetDifficulty";
	case 4032://"SquadRefill";
	case 4045://"Desync Check";
	default:
		return cvScalar((255), (255), (255), 0); // Nicht anzeigen
	}

	//Wei�
	return cvScalar((255), (255), (255), 255);

	//MISE;
}

void Imager::Echo()
{
	printf("IMG_Path:   %s\n", IMG_Path.c_str());
	printf("MOV_Path:   %s\n", MOV_Path.c_str());
}