#define DF_Debug

#include "Broker.h"

#include "WEB_MCB.h"

#include <Wt/WContainerWidget.h>

broker *(WEB_MCB::Bro) = NULL;

WEB_MCB::WEB_MCB()
{
	MISS;

	cMain = new Wt::WContainerWidget();
	
	MISE;
}



