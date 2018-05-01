#include "macd.h"
int main() {
	std::string data;
	std::string macdTxt;
	std::string signal;

	std::cin >> data;
	std::cin >> macdTxt;
	std::cin >> signal;
	
	Macd* macd = new Macd(1000, data, macdTxt, signal);
	macd->readData();
	macd->ema(12, macd->getEma12(), macd->getData());
	macd->ema(26, macd->getEma26(), macd->getData());
	macd->calculateMacd();
	macd->ema(9, macd->getSignal(), macd->getMacd());
	macd->sendData();
	macd->gral();
	delete macd;
	return 0;
}
