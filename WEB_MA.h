#ifndef WEB_MA_H
#define WEB_MA_H

class WEB_MA
{
public:

	Replay* R;

	WFileUpload  *wfuDropZone;	
	WText		 *wtStatus;
	WText		 *Head;
	

	WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MA();	

};


#endif // WEB_MA
