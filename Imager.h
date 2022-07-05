#ifndef Imager_H
#define Imager_H

class Imager
{
public:
	Imager();
	~Imager();

	void test();
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:


private:
	
};

#endif //Imager_H


