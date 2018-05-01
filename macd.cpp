#include "macd.h"

Macd::Macd(int n, std::string pathIn, std::string pathOutMacd, std::string pathOutSignal) {
	this->n = n;
	this->pathIn = pathIn;
	this->pathOutMacd = pathOutMacd;
	this->pathOutSignal = pathOutSignal;
	data = new double[n];
	ema12 = new double[n];
	ema26 = new double[n];
	macd = new double[n];
	signal = new double[n];
}

Macd::~Macd() {
	delete[] data;
	delete[] ema12;
	delete[] ema26;
	delete[] macd;
	delete[] signal;
}

void Macd::readData() {
	FILE* file = fopen(pathIn.c_str(), "r");
	for (int i = 0; i < n; i++) {
		fscanf(file, "%lf", &data[i]);
	}
	fclose(file);
	howMany = 1000;
	money = 0;
}

void Macd::ema(int count, double* ema, double* data) {
	double counter;
	double denominator;
	double alpha = 1 - (2 / double(count - 1));
	double* alphaHelper = new double[count + 1];
	alphaHelper[0] = 1;
	for (int i = 1; i <= count; i++) {
		alphaHelper[i] = alphaHelper[i - 1] * alpha;
	}
	for (int i = 0; i < n; i++) {
		counter = data[i];
		denominator = 1;
		if (i < count) {
			for (int j = 1; j <= i; j++) {
				counter += data[i - j] * alphaHelper[j];
				denominator += alphaHelper[j];
			}
		}
		else {
			for (int j = 1; j <= count; j++) {
				counter += data[i - j] * alphaHelper[j];
				denominator += alphaHelper[j];
			}
		}
		ema[i] = counter / denominator;
	}
	delete[] alphaHelper;
}

void Macd::calculateMacd() {
	for (int i = 0; i < n; i++) {
		macd[i] = ema12[i] - ema26[i];
	}
}

double* Macd::getEma12() {
	return ema12;
}

double* Macd::getEma26() {
	return ema26;
}

double * Macd::getData()
{
	return data;
}

double * Macd::getMacd()
{
	return macd;
}

double * Macd::getSignal()
{
	return signal;
}

void Macd::sendData() {
	FILE* fileMacd = fopen(pathOutMacd.c_str(), "w");
	FILE* fileSignal = fopen(pathOutSignal.c_str(), "w");
	for (int i = 0; i < n; i++) {
		fprintf(fileMacd, "%lf, ", macd[i]);
		fprintf(fileSignal, "%lf, ", signal[i]);
	}
	fclose(fileMacd);
	fclose(fileSignal);
}

void Macd::gral() {
	std::cout << "I've had " << (int)(howMany * data[0]) << std::endl;
	for (int i = 1; i < n; i++) {
		//Sell
		if (macd[i - 1] < signal[i - 1] && macd[i] > signal[i]) {
			money += howMany *= data[i];
			howMany = 0;
		}
		//Buy
		else if (macd[i - 1] > signal[i - 1] && macd[i] < signal[i]) {
			while (money > data[i]) {
				howMany++;
				money -= data[i];
			}
		}
	}
	money += howMany *= data[n - 1];
	howMany = 0;
	std::cout << "Now i have " << (int)money << std::endl;
}


