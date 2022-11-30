CC = g++
CFLAGS = -g -Wall -pthread 
Const = -D DF_Debug

#noManager -lboost_filesystem
#noImager  -lopencv_imgcodecs -lopencv_core -lopencv_imgproc -lopencv_highgui 
#CardBaseUpdater -lcurl -ljsoncpp 

DBLIBS = -lmysqlcppconn 
 
###OUTS
Parser: SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o
	$(CC) $(CFLAGS) -o Parser SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o $(Const)
	
DB: SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o LOAD.o PMV_to_SQL.o Reader.o Replay.o Thread_MIS.o Utility.o SQL_MIS_New.o
	$(CC) $(CFLAGS) -o DB SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o LOAD.o PMV_to_SQL.o Reader.o Replay.o Thread_MIS.o Utility.o SQL_MIS_New.o $(DBLIBS) $(Const)
#Imager.o 
#Manager.o

###Main OBJs
SLR_ReplayParser.o: SLR_ReplayParser.cpp Broker.h DEBUG.h Replay.h
	$(CC) -c SLR_ReplayParser.cpp -D noManager -D noImager $(Const)

SLR_ReplayDB.o: SLR_ReplayDB.cpp Broker.h DEBUG.h SQL_MIS_New.h CardBase.h LOAD.h Replay.h PMV_to_SQL.h  Utility.h
	$(CC) -c SLR_ReplayDB.cpp -D BrokerNormal -D noManager -D noImager $(Const)
#Imager.h 
#Manager.h

###Global Classes
Thread_MIS.o: Broker.h Thread_MIS.h Thread_MIS.cpp
	$(CC) -c Thread_MIS.cpp $(Const)	

DEBUG.o:  Broker.h DEBUG.h DEBUG.cpp
	$(CC) -c DEBUG.cpp $(Const)

Utility.o: Utility.h Utility.cpp
	$(CC) -c Utility.cpp $(Const)

###Brokers
BrokerParser.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp
	$(CC) -c Broker.cpp -o BrokerParser.o -D BrokerParser -D noManager -D noImager $(Const)

BrokerDB.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp LOAD.h SQL_MIS_New.h CardBase.h PMV_to_SQL.h
	$(CC) -c Broker.cpp -o BrokerDB.o -D BrokerNormal -D noManager -D noImager $(Const)
#Imager.h 
#Manager.h
###Rest
Replay.o: Broker.h Replay.h Replay.cpp Reader.h
	$(CC) -c Replay.cpp $(Const)

Reader.o: Broker.h Reader.h Reader.cpp
	$(CC) -c Reader.cpp $(Const)

SQL_MIS_New.o: Broker.h SQL_MIS_New.h SQL_MIS_New.cpp
	$(CC) -c SQL_MIS_New.cpp -D BrokerNormal $(Const)

PMV_to_SQL.o: Broker.h PMV_to_SQL.h PMV_to_SQL.cpp SQL_MIS_New.h Replay.h
	$(CC) -c PMV_to_SQL.cpp $(Const)

LOAD.o: Broker.h LOAD.h LOAD.cpp
	$(CC) -c LOAD.cpp $(Const)

#Imager.o: Broker.h Imager.h Imager.cpp Replay.h Utility.h
#$(CC) -c Imager.cpp -D BrokerNormal $(Const)

#Manager.o: Broker.h Manager.h Manager.cpp Replay.h Utility.h
#$(CC) -c Manager.cpp -D BrokerNormal $(Const)

CardBaseDB.o: Broker.h CardBase.h CardBase.cpp SQL_MIS_New.h
	$(CC) -c CardBase.cpp -o CardBaseDB.o -D BrokerNormal $(Const)

clean:
	rm *.o Parser DB