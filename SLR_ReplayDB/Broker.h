#ifndef BROKER_H
#define BROKER_H

class DEBUG;
class SQL_MIS_New;
class CardBase;
class Replay;
class LOAD;
class Manager;

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
	
	broker* Bro;

	bool bAktive;

	unsigned char C_GetActionOrbForCardID(unsigned short CardID);
	string L_getSQL_Server();
	string L_getSQL_User();
	string L_getSQL_PW();
	string L_getSQL_DB();
	string L_getPMV_PATH();
	string L_getPMV_AUTO_PATH();
	string L_getPMV_ARCH_PATH();
	
protected:
	

private:
	
};

#endif //BROKER_H


