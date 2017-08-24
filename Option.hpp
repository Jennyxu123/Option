#ifndef Option_hpp
#define Option_hpp
#include<vector>
#include <string>
using namespace std;

//Base class
class Option
{
private:
	//Private functions to calculate option price and sensitivities
	virtual double CallPrice(double U) const = 0;
	virtual double PutPrice(double U) const = 0;

	virtual vector<double> CallPriceVector(vector<double> vtr) const = 0;
	virtual vector<double> PutPriceVector(vector<double> vtr) const = 0;


public:
	Option();                                 //Default constructor
	Option(const Option& option);             //Copy constructor
	Option(const string& optionType);         //Set optionType

	double r;    //Interest rate
	double sig;  //Volatility
	double K;    //Strike price
	double T;	 //Expiry date
	double b;	 //Cost of carry

	string optType; //Option name (call, put)
	string unma;    //Name of underlying asset

	//Calculate option price and sensitivities
	double Price(double U) const;

	//Calculate option price and sensitivities for a range of monotonically increasing S
	vector<double> PriceVector(vector<double> vtr) const;
};

//Derived class for European Options
class EuroOptionPricing:public Option
{
private:
	//Overwrite private functions for price calculations
	double CallPrice(double U) const; 
	double PutPrice(double U) const;
	vector<double> CallPriceVector(vector<double> vtr) const;
	vector<double> PutPriceVector(vector<double> vtr) const;
	
	//Calculate sensitivities for European options 
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	vector<double> CallDelta1(vector<double> vtr) const;
	vector<double> PutDelta1(vector<double> vtr) const;

public:
	EuroOptionPricing();                                 //Default constructor
	EuroOptionPricing(const EuroOptionPricing& option2); //Copy constructor
	EuroOptionPricing(const string& optionType);         //Set optionType

	//Calculate sensitivities
	double Delta(double U) const;

	//Calculate sensitivities for a range of monotonically increasing S
	vector<double> Delta1(vector<double> vtr) const;
};

//Derived class for perpetual American options
class perpetualAmerican :public Option
{
private:
	//Overwrite private functions for price calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	vector<double> CallPriceVector(vector<double> vtr) const;
	vector<double> PutPriceVector(vector<double> vtr) const;
public:
	perpetualAmerican();                                 //Default constructor
	perpetualAmerican(const perpetualAmerican& option3); //Copy constructor
	perpetualAmerican(const string& optionType);         //Set optionType
};

//Global functions: gaussian functions
double n(double x);
double N(double x);

//Global function to generate a vector
vector<double> generateVector(double start, double end, double interval); 

#pragma once
#endif