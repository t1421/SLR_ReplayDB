#define DF_Debug

#include "prototypes.h"
#include "WEB_Main.h"
#include "WEB_MCB.h"

broker *(WEB_MCB::Bro) = NULL;

WEB_MCB::WEB_MCB()
{
	MISS;

	cMain = new WContainerWidget();
	
	MISE;
}



