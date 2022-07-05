#ifndef SQL_MIS_NEW_H
#define SQL_MIS_NEW_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


#include <boost/algorithm/string.hpp>

using namespace sql;
class SQL_MIS_New
{
public:

	Driver *driver  = NULL;
	Connection *con = NULL;
	Statement *stmt = NULL;	
	ResultSet *res  = NULL;
	

	string sName;

	stringstream ssSQL;

	//-------------------------------------

	SQL_MIS_New(string _Name);
	~SQL_MIS_New();


	int send();	
	string clearString(string changeString);
	string get_LAST_INSERT_ID();
	bool SendBLOB(string sBlob);
	
	//BROKER
	static broker* Bro;
	void teachN() { Bro->N = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

};

#endif // SQL_MIS_New_H
