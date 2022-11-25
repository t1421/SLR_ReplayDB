#ifndef BROKER_H
#define BROKER_H

#ifdef DF_Debug 
#define MISD(___Mes___) Bro->B_StatusNew(__FUNCTION__, ___Mes___);
#define MISERROR(___Mes___)Bro->B_StatusE("E", __FUNCTION__, ___Mes___);
#define MISS MISD("-->");
#define MISE MISD("<--");
#define MISEA(___Mes___) MISD("<-- " ___Mes___);

#else
#define MISD(___Mes___); 
#define MISERROR(___Mes___)Bro->B_StatusE("E", __FUNCTION__, ___Mes___);
#define MISS
#define MISE
#define MISEA(___Mes___);
#endif

#include <string>

class DEBUG;
class SQL_MIS_New;
class CardBase;
class Replay;
class LOAD;
class Manager;
class Imager;
class WEB_Main;

class broker
{
public:
	broker();
	~broker();

	DEBUG* B;
	SQL_MIS_New* N;
	CardBase* C;	
	LOAD* L;
	Manager* M;
	Imager* I;
	WEB_Main *W;
	
	broker* Bro;

	bool bAktive;

#if defined BrokerParser || defined BrokerWeb
	unsigned char C_GetActionOrbForCardID(unsigned short CardID);
#endif

#ifdef BrokerNormal
	unsigned char C_GetActionOrbForCardID(unsigned short CardID);
	bool C_DownloadPNG(unsigned short CardID);
#endif

#if defined BrokerNormal || defined BrokerWeb
	std::string L_getSQL_Server();
	std::string L_getSQL_User();
	std::string L_getSQL_PW();
	std::string L_getSQL_DB();
	std::string L_getPMV_PATH();
	std::string L_getPMV_AUTO_PATH();
	std::string L_getPMV_ARCH_PATH();
	std::string L_getTMP_PATH();
	std::string L_getFFMPEG();
#endif	

	void B_StatusNew(std::string Fun, std::string Wert);
	void B_StatusE(std::string Modul, std::string Funktion, std::string Wert);


protected:
	

private:
	
};

#endif //BROKER_H


