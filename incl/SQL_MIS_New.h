#ifndef SQL_MIS_NEW_H
#define SQL_MIS_NEW_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <boost/algorithm/string.hpp>

#include <string>
#include <sstream>

using namespace sql;
class SQL_MIS_New
{
public:

	Driver *driver  = NULL;
	Connection *con = NULL;
	Statement *stmt = NULL;	
	ResultSet *res  = NULL;
	

	std::string sName;

	std::stringstream ssSQL;

	//-------------------------------------

	SQL_MIS_New(std::string _Name);
	~SQL_MIS_New();


	int send();	
	std::string clearString(std::string changeString);
	std::string get_LAST_INSERT_ID();
	bool SendBLOB(std::string sBlob);
	
	//BROKER
	static broker* Bro;
	void teachN() { Bro->N = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

};

#endif // SQL_MIS_New_H
