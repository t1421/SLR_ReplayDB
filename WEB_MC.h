#ifndef WEB_MC_H
#define WEB_MC_H

class WEB_MC
{
public:

	Replay* R;

	WFileUpload  *wfuDropZone;	
	WText		 *wtStatus;
	WText		 *wtMap;
	WText		 *wtTime;
	WText		 *Head;


	WContainerWidget *cMain;
	WContainerWidget *cResult;
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MC();
	string showResults();

};


#endif // WEB_MC