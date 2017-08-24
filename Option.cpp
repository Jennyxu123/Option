#include "Option.hpp"
#include "iostream"
#include <vector>
#include <cmath>

using namespace std;
//#include <boost/math/distributions/normal.hpp>
//#include <boost/math/distributions.hpp> // For non-member functions of distributions
//using namespace boost::math;

//Default constructor
Option::Option()
{
	r = 0.04;
	sig = 0.2;
	K = 65;
	T = 1;
	b = 0.0;
	optType = "C";
}

//Copy constructor
Option::Option(const Option& option)
{
	r = option.r;
	sig = option.sig;
	K = option.K;
	T = option.T;
	b = option.b;
	optType = option.optType;
}

//Set option type
Option::Option(const string& optionType)
{
	optType = optionType;
}

double Option::Price(double U) const
{
	if (optType == "C")
	{
		return CallPrice(U);
	}
	else
	{
		return PutPrice(U);
	}
}

vector<double> Option::PriceVector(vector<double> vtr) const
{
	if (optType == "C")
	{
		return CallPriceVector(vtr);
	}
	else
	{
		return PutPriceVector(vtr);
	}
}

//Derived class default constructor
EuroOptionPricing::EuroOptionPricing() :Option()
{
}

//Derived class Copy constructor
EuroOptionPricing::EuroOptionPricing(const EuroOptionPricing& option2) : Option(option2)
{
}

//Set option type
EuroOptionPricing::EuroOptionPricing(const string& optionType) : Option(optionType)
{
}

//Overwrite CallPrice in base class
double EuroOptionPricing::CallPrice(double U) const
{
	double tmp = sig*sqrt(T);	
	double d1 = (log(U / K) + (r + (sig*sig)*0.5)*T) / tmp;
	double d2 = d1 - tmp;
	return (U*N(d1) - K*exp(-r*T)*N(d2));
}


double EuroOptionPricing::PutPrice(double U) const
{
	double tmp = sig*sqrt(T);

	double d1 = (log(U / K) + (r + (sig*sig)*0.5)*T) / tmp;
	double d2 = d1 - tmp;

	return (K* exp(- r*T)*N(-d2) - U*N(-d1));
}

//Using std::vector to calculate option price, overwrite CallPriceVector in base class
vector<double> EuroOptionPricing::CallPriceVector(vector<double> vtr) const
{
	vector<double> call;
	double tmp = sig*sqrt(T);
	for (int i = 0; i < vtr.size(); i++)
	{
		double d1 = (log(vtr[i] / K) + (r + (sig*sig)*0.5)*T) / tmp;
		double d2 = d1 - tmp;
		call.push_back(vtr[i] * N(d1) - K*exp(-r*T)*N(d2));
	}
	return call;
}

vector<double> EuroOptionPricing::PutPriceVector(vector<double> vtr) const
{
	vector<double> put;
	double tmp = sig*sqrt(T);
	for (int i = 0; i < vtr.size(); i++)
	{
		double d1 = (log(vtr[i] / K) + (r + (sig*sig)*0.5)*T) / tmp;
		double d2 = d1 - tmp;
		put.push_back(K* exp(-r*T)*N(-d2) - vtr[i] * N(-d1));
	}
	return put;
}

//calculate option sensitivies for European options only
double EuroOptionPricing::CallDelta(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	return  N(d1);
}

double EuroOptionPricing::PutDelta(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig*sig)*0.5) * T) / tmp;
	return (N(d1) - 1.0);
}

//use std::vector to calculate option sensitivies
vector<double> EuroOptionPricing::CallDelta1(vector<double> vtr) const
{
	vector<double> callDelta;
	double tmp = sig*sqrt(T);
	for (int i = 0; i < vtr.size(); i++)
	{
		double d1 = (log(vtr[i] / K) + (r + (sig*sig)*0.5)*T) / tmp;
		callDelta.push_back(N(d1));
	}
	return callDelta;
}

vector<double> EuroOptionPricing::PutDelta1(vector<double> vtr) const
{
	vector<double> putDelta;
	double tmp = sig * sqrt(T);
	for (int i = 0; i < vtr.size(); i++)
	{
		double d1 = (log(vtr[i] / K) + (r + (sig*sig)*0.5)*T) / tmp;
		putDelta.push_back(N(d1)-1.0);
	}
	return  putDelta;
}


//Public function for option pricing and sensetivities
double EuroOptionPricing::Delta(double U) const
{
	if (optType == "C")
		return CallDelta(U);
	else
		return PutDelta(U);
}

vector<double> EuroOptionPricing::Delta1(vector<double> vtr) const
{
	if (optType == "C")
		return CallDelta1(vtr);
	else
		return PutDelta1(vtr);
}

//Default constructor
perpetualAmerican::perpetualAmerican():Option()
{
}

//Copy constructor
perpetualAmerican::perpetualAmerican(const perpetualAmerican& option2) : Option(option2)
{

}

//Set option type
perpetualAmerican::perpetualAmerican(const string& optionType):Option(optionType)
{
}

//Overwrite private member functions in the base class 
double perpetualAmerican::CallPrice(double U) const
{
	double tmp = 0.5 - b / (sig*sig);
	double y1 = tmp + sqrt(tmp*tmp + 2 * r / (sig*sig));
	double tmp2 = pow((y1 - 1)*U / (y1*K), y1);
	return (K / (y1 - 1)*tmp2);
}

double perpetualAmerican::PutPrice(double U) const
{
	double tmp = 0.5 - b / (sig*sig);
	double y2 = tmp - sqrt(tmp*tmp + 2 * r / (sig*sig));
	double tmp2 = pow((y2 - 1)*U / (y2*K), y2);
	return (K / (1 - y2)*tmp2);
}
vector<double> perpetualAmerican::CallPriceVector(vector<double> vtr) const
{
	vector<double> call;
	double tmp = 0.5 - b / (sig*sig);
	double y1 = tmp + sqrt(tmp*tmp + 2 * r / (sig*sig));
	for (int i = 0; i < vtr.size(); i++)
	{
		double tmp2 = pow((y1 - 1)*vtr[i] / (y1*K), y1);
		call.push_back(K / (y1 - 1)*tmp2);
	}
	return call;
}

vector<double> perpetualAmerican::PutPriceVector(vector<double> vtr) const
{
	vector<double> put;
	double tmp = 0.5 - b / (sig*sig);
	double y2 = tmp - sqrt(tmp*tmp + 2 * r / (sig*sig));
	for (int i = 0; i < vtr.size(); i++)
	{
		double tmp2 = pow((y2 - 1)*vtr[i] / (y2*K), y2);
		put.push_back(K / (1- y2)*tmp2);
	}
	return put;
}

// The approximation to the normal pdf
double n(double x)
{
	double A = 1.0 / sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);
}

// The approximation to the cumulative normal distribution
double N(double x)
{
	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0 / (1.0 + (0.33267 * x));

	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - N(-x);
	}

}

//Global function to generate vectors
vector<double> generateVector(double start, double end, double interval)
{
	vector<double> vtr;
	for (int i = 0; i <= (end - start) / interval; i++)
	{
		vtr.push_back(start + interval*i);
	}
	return vtr;
}
