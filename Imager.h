#ifndef Imager_H
#define Imager_H

class Replay;

class Imager
{
public:
	Imager();
	~Imager();

	void test();
	bool UseThisPMV(Replay * inReplay);
	bool MakeIMG();
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:


private:
	Replay * RR;
};

#endif //Imager_H


