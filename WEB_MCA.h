#ifndef WEB_MCA_H
#define WEB_MCA_H

#include "WEB_MC.h"

class WEB_MCA
{
public:

	Replay* R;

	WFileUpload  *wfuDropZone;	
	WText		 *wtStatus;
	WText		 *wtMap;
	WText		 *wtDif;
	WText		 *wtTime;
	WText		 *Head;

	WContainerWidget *cMap;
	WImage       *wiMap;
	vector <Marker *> vMarker;

	WContainerWidget *cMain;
	WContainerWidget *cReplay;
	WContainerWidget *cReplayResult;
	WContainerWidget *cRank;
	
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MCA();
	void showResults();
	void addUnitToFirstOrb();
	void addStartingWells();
	void InitVector();
};


#endif // WEB_MCA
