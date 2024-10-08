#ifndef WEB_Analyser_Head_H
#define WEB_Analyser_Head_H

#include "../WEB/WEB_Utility.h"
#include <Wt/Chart/WCartesianChart.h>

class WEB_Analyser;

class WEB_Analyser_Head : public WebRefresh
{
public:

	bool newData;

	WEB_Analyser *WA;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Head(WEB_Analyser *WA_);
	void WRefresh();
	

	private:
		Wt::WText		 *Playtime;		
		Wt::WText		 *MapName;
		Wt::WText		 *Seed;
		Wt::WText		 *MapID;
		Wt::WText		 *DifficultyID;
		Wt::WText		 *PlayModeID;
		Wt::WText		 *PMVPlayerID;
		
		
		Wt::WText		 *WinningTeam;
		//Wt::WText		 *FileName;

		Wt::WText		 *FileVersion;
		Wt::WText		 *GameVersion;
		Wt::WText		 *GroupCount;
		Wt::WText		 *DifficultyID2;
		Wt::WText		 *Playtime2;		
		Wt::WText		 *PlayModeID2;
		Wt::WText		 *PMVPlayerID2;
		Wt::WText		 *ActionBlock;
		Wt::WText		 *Unknow3;
		Wt::WText		 *Unknow4;
		Wt::WText		 *Power;
		
		Wt::WText		 *MatrixCount;
		Wt::WText		 *TeamCount;

		Wt::WText		 *SSS3;
		Wt::WText		 *SSS5;
		Wt::Chart::WCartesianChart *Chart;
		Wt::WText		 *SSS7;
		
			
	

};


#endif // WEB_Analyser_Head
