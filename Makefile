CC = g++
CFLAGS = -g -Wall -pthread 
Const = 

###OUTS
Parser: SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o
	$(CC) $(CFLAGS) -o Parser SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o $(Const)
	
DB: SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o Imager.o LOAD.o Manager.o PMV_to_SQL.o Reader.o Replay.o Thread_MIS.o Utility.o SQL_MIS_New.o
	$(CC) $(CFLAGS) -o DB SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o Imager.o LOAD.o Manager.o PMV_to_SQL.o Reader.o Replay.o Thread_MIS.o Utility.o SQL_MIS_New.o $(Const)

###Main OBJs
SLR_ReplayParser.o: SLR_ReplayParser.cpp Broker.h DEBUG.h Replay.h
	$(CC) -c SLR_ReplayParser.cpp $(Const)

SLR_ReplayDB.o: SLR_ReplayDB.cpp Broker.h DEBUG.h SQL_MIS_New.h CardBase.h LOAD.h Manager.h Replay.h PMV_to_SQL.h Imager.h  Utility.h
	$(CC) -c SLR_ReplayDB.cpp $(Const)
	
###Global Classes
Thread_MIS.o: Broker.h Thread_MIS.h Thread_MIS.cpp
	$(CC) -c Thread_MIS.cpp $(Const)	

DEBUG.o:  Broker.h DEBUG.h DEBUG.cpp
	$(CC) -c DEBUG.cpp $(Const)

Utility.o: Utility.h Utility.cpp
	$(CC) -c Utility.cpp $(Const)

###Brokers
BrokerParser.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp
	$(CC) -c Broker.cpp -o BrokerParser.o -D BrokerParser $(Const)

BrokerDB.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp LOAD.h SQL_MIS_New.h CardBase.h Imager.h PMV_to_SQL.h Manager.h
	$(CC) -c Broker.cpp -o BrokerDB.o -D BrokerNormal $(Const)

###Rest
Replay.o: Broker.h Replay.h Replay.cpp Reader.h
	$(CC) -c Replay.cpp $(Const)

Reader.o: Broker.h Reader.h Reader.cpp
	$(CC) -c Reader.cpp $(Const)

SQL_MIS_New.o: Broker.h SQL_MIS_New.h SQL_MIS_New.cpp
	$(CC) -c SQL_MIS_New.cpp $(Const)

PMV_to_SQL.o: Broker.h PMV_to_SQL.h PMV_to_SQL.cpp SQL_MIS_New.h Replay.h
	$(CC) -c PMV_to_SQL.cpp $(Const)

Manager.o: Broker.h Manager.h Manager.cpp Replay.h PMV_to_SQL.h SQL_MIS_New.h Utility.h
	$(CC) -c Manager.cpp $(Const)

LOAD.o: Broker.h LOAD.h LOAD.cpp
	$(CC) -c LOAD.cpp $(Const)

Imager.o: Broker.h Imager.h Imager.cpp Replay.h Utility.h
	$(CC) -c Imager.cpp $(Const)

CardBaseDB.o: Broker.h CardBase.h CardBase.cpp SQL_MIS_New.h
	$(CC) -c CardBase.cpp -o CardBaseDB.o -D BrokerNormal $(Const)

clean:
	rm *.o Parser