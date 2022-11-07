#ifndef WEB_MC_H
#define WEB_MC_H

#define IMG_SIZE 300
#define Xoffset -304
#define Yoffset -199

struct Marker
{
	unsigned short Type;
	unsigned long Unit;
	WText *Time;
	WImage *IMG;

	Marker(unsigned short _Type,
		unsigned long _Unit,
		short _X,
		short _Y):
		Type(_Type),
		Unit(_Unit),
		Time(new WText("XX:XX")),
		IMG(new WImage("./resources/M.png"))
	{
		IMG->setHidden(true);
		IMG->setHeight(10);
		IMG->setWidth(10);
		IMG->resize(10, 10);
		IMG->setMaximumSize(10, 10);
		IMG->setPositionScheme(PositionScheme::Relative);
		IMG->setOffsets(_X + Xoffset, Side::Left);
		IMG->setOffsets(_Y + Yoffset, Side::Top);	
	}
};

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
	vector <Marker *> vMarker;

	WContainerWidget *cMain;
	WContainerWidget *cResult;
	
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MC();
	string showResults();
	void addUnitToFirstOrb();
	void addStartingWells();
	void InitVector();
	

};


#endif // WEB_MC
