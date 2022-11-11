#ifndef WEB_MB_H
#define WEB_MB_H

#include "WEB_Toolbar.h"
class WEB_MBA;
class WEB_MBB;

#define IMG_SIZE 50

struct WebCard {
	unsigned short CardID;
	unsigned int   playCount;
	unsigned int   iFire;
	unsigned int   iFrost;
	unsigned int   iShadow;
	unsigned int   iNature;
	unsigned int   iNeutral;
	bool		   bUnit;
	bool		   bSpell;
	bool		   bBuilding;

	WImage		  *IMG[3];
};

class WEB_MB : public WEB_Toolbar
{
public:

	WEB_MBA *A;
	WEB_MBB *B;

	WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MB();
	
};


#endif // WEB_MB
