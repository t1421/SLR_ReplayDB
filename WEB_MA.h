#ifndef WEB_MA_H
#define WEB_MA_H

class WEB_MA
{
public:

	WContainerWidget *cMain;

	WPushButton *wbPrev;
	WPushButton *wbStop;
	WPushButton *wbPlay;
	WPushButton *wbNext;
	WPushButton *wbSync;

	WLineEdit *leBarcode;
	WPushButton *wbBarcode;

	WImage *wiCover[2];
	string sCover_ID[2];
	
	WSlider *wsPos;
	WComboBox *cbNote;
	WComboBox *cbCopy;

	WPushButton *wbKopf;
	WPushButton *wbTitel;
	WPushButton *wbSongNr;	
	WImage *wiStar[5];
	WImage *wiREP;
	WImage *wiMAS;

	WPushButton			*wbColorAnz;
	WLineEdit			*weColorAnz;
	WPushButton			*wbColorOffset; 
	WLineEdit			*weColorOffset;
	

	vector<vector<pair<WWidget*, string>>> &VVPWSWid;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MA(vector<vector<pair<WWidget*, string>>> &VVPWSWid_) ;	

	void Update_Pic(string sFrom, string sTo, int Alpha);
	void Update_Kopf(string _Kopf);
	void Update_Pos(int _Pos);
	void Update_DS(string sInput);
	void UpdateColorValues(string iAnz, string iOffset);
};


#endif // WEB_MA
