CC = g++
CFLAGS = -g -Wall -pthread 
Const = 
#-D DF_Debug

#noManager -lboost_filesystem
#noImager  -lopencv_imgcodecs -lopencv_core -lopencv_imgproc -lopencv_highgui 
#noSQL     -lmysqlcppconn 
#CardBaseUpdater -lcurl -ljsoncpp 


#DBLIBS = -lmysqlcppconn 
DBLIBS  = 
WEBLIBS = -lwt -lwthttp
 
###OUTS
Parser: SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o
	$(CC) $(CFLAGS) -o Parser SLR_ReplayParser.o BrokerParser.o DEBUG.o Reader.o Replay.o Thread_MIS.o $(Const)
	
DB: SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o LOAD.o Reader.o Replay.o Thread_MIS.o Utility.o 
	$(CC) $(CFLAGS) -o DB SLR_ReplayDB.o BrokerDB.o DEBUG.o CardBaseDB.o LOAD.o Reader.o Replay.o Thread_MIS.o Utility.o $(DBLIBS) $(Const)

WEB: BrokerWEB.o DEBUG.o LOAD.o MIS_Rank.o Reader.o Replay.o SLR_ReplayParserWeb.o Thread_MIS.o Utility.o WEB_Main.o WEB_CONTAINER.o WEB_MA.o WEB_MAA.o WEB_MB.o WEB_MBA.o WEB_MC.o WEB_MCA.o WEB_Rank.o WEB_Replay.o WEB_Toolbar.o WEB_Utility.o 
	$(CC) $(CFLAGS) -o WEB BrokerWEB.o DEBUG.o LOAD.o MIS_Rank.o Reader.o Replay.o SLR_ReplayParserWeb.o Thread_MIS.o Utility.o WEB_Main.o WEB_CONTAINER.o WEB_MA.o WEB_MAA.o WEB_MB.o WEB_MBA.o WEB_MC.o WEB_MCA.o WEB_Rank.o WEB_Replay.o WEB_Toolbar.o WEB_Utility.o  $(WEBLIBS) $(Const) 
 

###Main OBJs
SLR_ReplayParser.o: SLR_ReplayParser.cpp Broker.h DEBUG.h Replay.h
	$(CC) -c SLR_ReplayParser.cpp -D noManager -D noImager $(Const)

SLR_ReplayDB.o: SLR_ReplayDB.cpp Broker.h DEBUG.h CardBase.h LOAD.h Replay.h  Utility.h
	$(CC) -c SLR_ReplayDB.cpp -D BrokerNormal -D noManager -D noImager -D noSQL $(Const)

SLR_ReplayParserWeb.o: SLR_ReplayParserWeb.cpp Broker.h DEBUG.h LOAD.h WEB_Main.h
	$(CC) -c SLR_ReplayParserWeb.cpp -D BrokerWeb -D noManager -D noImager $(Const)
#Imager.h 
#Manager.h

###Global Classes
Thread_MIS.o: Broker.h Thread_MIS.h Thread_MIS.cpp
	$(CC) -c Thread_MIS.cpp $(Const)	

DEBUG.o:  Broker.h DEBUG.h DEBUG.cpp
	$(CC) -c DEBUG.cpp $(Const)

Utility.o: Utility.h Utility.cpp
	$(CC) -c Utility.cpp $(Const)

WEB_Utility.o: WEB_Utility.h WEB_Utility.cpp
	$(CC) -c WEB_Utility.cpp $(Const)

###Brokers
BrokerParser.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp
	$(CC) -c Broker.cpp -o BrokerParser.o -D BrokerParser -D noManager -D noImager $(Const)

BrokerDB.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp LOAD.h CardBase.h 
	$(CC) -c Broker.cpp -o BrokerDB.o -D BrokerNormal -D noManager -D noImager -D noSQL $(Const)

BrokerWEB.o: Broker.h DEBUG.h Thread_MIS.h Replay.h Reader.h Broker.cpp LOAD.h CardBase.h WEB_Main.h WEB_CONTAINER.h WEB_MA.h WEB_MB.h WEB_MBA.h WEB_MC.h WEB_MCA.h WEB_Toolbar.h WEB_Replay.h 
	$(CC) -c Broker.cpp -o BrokerWEB.o -D BrokerWeb -D noManager -D noImager -D noSQL $(Const)	

###Rest
Replay.o: Broker.h Replay.h Replay.cpp Reader.h
	$(CC) -c Replay.cpp $(Const)

Reader.o: Broker.h Reader.h Reader.cpp
	$(CC) -c Reader.cpp $(Const)

#SQL_MIS_New.o: Broker.h SQL_MIS_New.h SQL_MIS_New.cpp
#	$(CC) -c SQL_MIS_New.cpp -D BrokerNormal $(Const)

#PMV_to_SQL.o: Broker.h PMV_to_SQL.h PMV_to_SQL.cpp SQL_MIS_New.h Replay.h
#	$(CC) -c PMV_to_SQL.cpp $(Const)

LOAD.o: Broker.h LOAD.h LOAD.cpp
	$(CC) -c LOAD.cpp $(Const)

#Imager.o: Broker.h Imager.h Imager.cpp Replay.h Utility.h
#$(CC) -c Imager.cpp -D BrokerNormal $(Const)

#Manager.o: Broker.h Manager.h Manager.cpp Replay.h Utility.h
#$(CC) -c Manager.cpp -D BrokerNormal $(Const)

CardBaseDB.o: Broker.h CardBase.h CardBase.cpp SQL_MIS_New.h
	$(CC) -c CardBase.cpp -o CardBaseDB.o -D BrokerNormal -D noSQL $(Const)

MIS_Rank.o: Broker.h MIS_Rank.h MIS_Rank.cpp
	$(CC) -c MIS_Rank.cpp -D BrokerWeb $(Const)

### WEB
WEB_Main.o: Broker.h WEB_Main.h WEB_Main.cpp Utility.h WEB_CONTAINER.h Thread_MIS.h
	$(CC) -c WEB_Main.cpp $(Const)

WEB_CONTAINER: Broker.h WEB_CONTAINER.h WEB_CONTAINER.cpp WEB_Utility.h WEB_MA.h WEB_MB.h WEB_MC.h WEB_Toolbar.h WEB_Replay.h
	$(CC) -c WEB_CONTAINER.cpp  $(Const)

WEB_Toolbar.o: Broker.h WEB_Toolbar.h WEB_Toolbar.cpp WEB_Utility.h
	$(CC) -c WEB_Toolbar.cpp $(Const)

WEB_Rank.o: Broker.h WEB_Rank.h MIS_Rank.h WEB_Rank.cpp Utility.h WEB_Utility.h
	$(CC) -c WEB_Rank.cpp $(Const)	

WEB_Replay.o: Broker.h WEB_Replay.h WEB_Replay.cpp WEB_Utility.h Replay.h LOAD.h
	$(CC) -c WEB_Replay.cpp  $(Const)

WEB_MA.o: Broker.h WEB_MA.h WEB_MAA.h WEB_MA.cpp WEB_Rank.h WEB_Toolbar.h WEB_Replay.h
	$(CC) -c WEB_MA.cpp  $(Const)

WEB_MAA.o: Broker.h WEB_MAA.h WEB_MAA.cpp WEB_Replay.h WEB_Utility.h
	$(CC) -c WEB_MAA.cpp -D BrokerWeb $(Const)	

WEB_MB.o: Broker.h WEB_MB.h WEB_MBA.h WEB_MB.cpp WEB_Rank.h WEB_Toolbar.h WEB_Replay.h
	$(CC) -c WEB_MB.cpp  $(Const)	

WEB_MBA.o: Broker.h WEB_MBA.h WEB_MBA.cpp WEB_Replay.h WEB_Utility.h Utility.h
	$(CC) -c WEB_MBA.cpp -D BrokerWeb $(Const)		

WEB_MC.o: Broker.h WEB_MC.h WEB_MCA.h WEB_MC.cpp WEB_Rank.h WEB_Toolbar.h WEB_Replay.h
	$(CC) -c WEB_MC.cpp  $(Const)	

WEB_MCA.o: Broker.h WEB_MCA.h WEB_MCA.cpp WEB_Replay.h WEB_Utility.h Utility.h
	$(CC) -c WEB_MCA.cpp -D BrokerWeb $(Const)	

clean:
	rm *.o Parser DB WEB