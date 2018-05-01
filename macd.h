#ifndef MACD
#define MACD

#include <fstream>
#include <iostream>
#include <string>
class Macd {
private:
	double* ema12;
	double* ema26;
	double* data;
	double* macd;
	double* signal;
	int n;
	double money;
	int howMany;
	std::string pathIn;
	std::string pathOutMacd;
	std::string pathOutSignal;
public:
	Macd(int, std::string, std::string, std::string);
	~Macd();
	void readData();
	void ema(int, double*, double*);
	void calculateMacd();
	double* getEma12();
	double* getEma26();
	double* getData();
	double* getMacd();
	double* getSignal();
	void sendData();
	void gral();
};

#endif