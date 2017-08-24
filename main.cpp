#include "Option.hpp"
#include <iostream>
using namespace std;
int main()
{
	//Input the data of 5 options
	EuroOptionPricing Batch1("C");
	Batch1.T = 0.25;
	Batch1.K=65;
	Batch1.sig = 0.3;
	Batch1.r = 0.08;

	EuroOptionPricing Batch2("C");
	Batch2.T = 1.0;
	Batch2.K = 100;
	Batch2.sig = 0.2;
	Batch2.r = 0.0;

	EuroOptionPricing Batch3("C");
	Batch3.T = 1.0;
	Batch3.K = 10;
	Batch3.sig = 0.5;
	Batch3.r = 0.12;

	EuroOptionPricing Batch4("P");
	Batch4.T = 30.0;
	Batch4.K = 100;
	Batch4.sig = 0.30;
	Batch4.r = 0.08;

	perpetualAmerican Batch5("P");
	Batch5.K = 100;
	Batch5.sig = 0.1;
	Batch5.r = 0.1;
	Batch5.b = 0.02;

	//print out the price and delta
	cout<<"The price of Batch 1 when S=60 is: "<< Batch1.Price(60.0)<<endl;
	cout <<"The delta of Batch 2 when S=100 is: "<<Batch2.Delta(100.0) << endl;
	
	//Use std::vector to calculate option price and delta
	vector<double> vtr3 = generateVector(5, 6, 0.1);
	vector<double> vtr4 = generateVector(100, 110, 1);
	vector<double> vtr5 = generateVector(110, 120, 1);
	cout <<"The price of Batch 3 when S=5 is: "<<  Batch3.PriceVector(vtr3)[0] << endl;
	cout << "The delta of Batch 4 when S=100 is: "<<Batch4.Delta1(vtr4)[0] << endl;
	cout << "The price of Batch 5 when S=110 is: " << Batch5.PriceVector(vtr5)[0] << endl;
	return 0;
}