#ifndef BROKER_H
#define BROKER_H

class DEBUG;
class SQL_MIS_New;
class CardBase;
class Replay;
//class PMV_to_SQL;

class broker
{
public:
	broker();
	~broker();

	DEBUG* B;
	SQL_MIS_New* N;
	CardBase* C;
	Replay* R;
	//PMV_to_SQL* P;
	broker* Bro;

	bool bAktive;

	unsigned char C_GetActionOrbForCardID(unsigned short CardID);
	
protected:
	

private:
	
};

#endif //BROKER_H


