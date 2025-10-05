//#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\LOAD.h" 

#include "..\incl\SQL_MIS_New.h"

broker *(SQL_MIS_New::Bro) = NULL;

SQL_MIS_New::SQL_MIS_New(std::string _Name) :sName(_Name)
{
	MISD("--> " + _Name);
	
	ConnectOptionsMap connection_properties;
	connection_properties["hostName"] = sql::SQLString(Bro->L->sSQL_Server);
	connection_properties["userName"] = sql::SQLString(Bro->L->sSQL_User);
	connection_properties["password"] = sql::SQLString(Bro->L->sSQL_PW);
	connection_properties["CLIENT_MULTI_STATEMENTS"] = (true);

	try
	{
		driver = get_driver_instance();
		con = driver->connect(connection_properties);

		con->setSchema(Bro->L->sSQL_DB);
	}
	catch (sql::SQLException &e)
	{
		Bro->B_StatusE("E", "0SQL_ERROR: ", sName);
		Bro->B_StatusE("E", "1SQL_ERROR: ", e.what());
		Bro->B_StatusE("E", "2SQL_ERROR: ", std::to_string(e.getErrorCode()));
		Bro->B_StatusE("E", "3SQL_ERROR: ", e.getSQLState());
		Bro->B_StatusE("E", "4SQL_ERROR: ", "While connecting");
	}
	MISE;
}

SQL_MIS_New::~SQL_MIS_New()
{
	MISS;
	delete res;
	delete stmt;
	delete con;
	MISE;
}

int SQL_MIS_New::send()
{
	MISS;

	// Upper und Trimmen 
	int ireturn;

	std::string sSTMT = ssSQL.str(); //boost::to_upper_copy(ssSQL.str());
	sSTMT.erase(0, sSTMT.find_first_not_of(" "));
	ssSQL.str("");

	try
	{
		if (!con->isValid())con->reconnect();

		stmt = con->createStatement();

		if (sSTMT[0] == 'U' || sSTMT[0] == 'u' ||
			sSTMT[0] == 'D' || sSTMT[0] == 'd' ||
			sSTMT[0] == 'I' || sSTMT[0] == 'i')
		{
			ireturn = stmt->executeUpdate(sSTMT);
		}

		if (sSTMT[0] == 'S' || sSTMT[0] == 's')
		{
			if (res != NULL)delete res;
			res = stmt->executeQuery(sSTMT);
			ireturn = res->rowsCount();
		}

		delete stmt;
	}

	catch (sql::SQLException &e)
	{
		Bro->B_StatusE("E", "0SQL_ERROR: ", sName);
		Bro->B_StatusE("E", "1SQL_ERROR: ", e.what());
		Bro->B_StatusE("E", "2SQL_ERROR: ", std::to_string(e.getErrorCode()));
		Bro->B_StatusE("E", "3SQL_ERROR: ", e.getSQLState());
		Bro->B_StatusE("E", "4SQL_ERROR: ", sSTMT);
	}

	MISE;
	return ireturn;
}


std::string SQL_MIS_New::get_LAST_INSERT_ID()
{
	MISS;
	std::string sTemp;
	ssSQL << " SELECT LAST_INSERT_ID() ";
	send();
	res->first();
	sTemp = res->getString(1);

	MISE;
	return sTemp;
}


std::string SQL_MIS_New::clearString(std::string changeString)
{
	MISS;

	unsigned int start_pos = 0;
	for (start_pos = 0; start_pos <= changeString.length(); start_pos++)if (changeString[start_pos] == char(39))
	{
		//MISD(to_string(start_pos));
		changeString.insert(start_pos, "'");
		start_pos++;
	}
	/*
	start_pos = 0; /// -> |
	while ((start_pos = changeString.find(char(124), start_pos)) != changeString.npos)changeString.replace(start_pos, 1, "");
	*/
	for (start_pos = 0; start_pos <= changeString.length(); start_pos++)if (changeString[start_pos] == char(92))
	{
		changeString.insert(start_pos, "\\");
		start_pos++;
	}

	MISE;
	return changeString;
}



bool SQL_MIS_New::SendBLOB(std::string sBlob)
{
	MISS;

	std::string sSTMT = ssSQL.str(); //boost::to_upper_copy(ssSQL.str());
	sSTMT.erase(0, sSTMT.find_first_not_of(" "));
	ssSQL.str("");
	try
	{
		if (!con->isValid())con->reconnect();

		//stmt = con->createStatement();
		PreparedStatement *pstmt = con->prepareStatement(sSTMT.c_str());
		std::istringstream iss(sBlob);
		pstmt->setBlob(1, &iss);		
		pstmt->executeUpdate();

		delete pstmt;
	}

	catch (sql::SQLException &e)
	{
		Bro->B_StatusE("E", "0SQL_ERROR: ", sName);
		Bro->B_StatusE("E", "1SQL_ERROR: ", e.what());
		Bro->B_StatusE("E", "2SQL_ERROR: ", std::to_string(e.getErrorCode()));
		Bro->B_StatusE("E", "3SQL_ERROR: ", e.getSQLState());
		Bro->B_StatusE("E", "4SQL_ERROR: ", sSTMT);
	}

	MISE;
	return true;
}
