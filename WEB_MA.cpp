//#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MA.h"

broker *(WEB_MA::Bro) = NULL;

WEB_MA::WEB_MA()
{
	MISS;

	WColor wTemp;

	cMain = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	wfuDropZone = new WFileUpload();
	wtStatus	= new WText();
	Head		= new WText();
	

	Head->setText("<h1><b>PMV Action Counter</b></h1>");
	wtStatus->setText("Select PMV (or drag and drop on the button)");
	
	
	MISD("#1");

	wfuDropZone->setFilters(".pmv");

	MISD("#3");

	MISD("#4");

	wfuDropZone->changed().connect([=] {
		wfuDropZone->upload();
		wtStatus->setText("New File");
	});
	
	MISD("#5");
	
	wfuDropZone->uploaded().connect([=] {
		wtStatus->setText("Upload done");

		R = new Replay();
		
		if (R->LoadPMV(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			wtStatus->setText("PMV OK");

			wtStatus->setText("<h3> The restult is: " + to_string(R->CountActions()) + "</h3>");
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> <h3> Your Temporarily result is: " + to_string(R->CountActions()) + "</h3> " );

	});

	MISD("#6");

	wfuDropZone->fileTooLarge().connect([=] {
		wtStatus->setText("File is too large.");
	});

	MISD("#6");
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Head)), 0, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)), 1, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 2, 0, 0, 1);

	MISE;
}


