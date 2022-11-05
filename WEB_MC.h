#ifndef WEB_MC_H
#define WEB_MC_H

#define IMG_SIZE 300

class WEB_MC
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


	WContainerWidget *cMain;
	WContainerWidget *cResult;
	
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MC();
	string showResults();
	void addUnitToFirstOrb();
	void addStartingWells();

};


#endif // WEB_MC
