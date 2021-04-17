#ifndef INTEGRAL_H
#define INTEGRAL_H

#include "utils.h"

#include <functional>

class Integral{
public:
	Integral( std::function<double(double)> f): func(f) {}

	virtual double integrate( double a, double b, int nSteps ) const = 0;

public:
	std::function<double(double)> func;


};

class Trapezoidal: public Integral{
public:
	Trapezoidal( std::function<double(double)> f ): Integral(f) {}

	virtual double integrate ( double a, double b, int nSteps 
	) const override {
		const double h = ( b - a )/ (double)nSteps;
		
		double sum = 0;

		for(int i = 1; i <= (nSteps - 1); i++){ sum += func( a + i * h ); }
		
		return h * ( func(a)/2 + func(b)/2 +  sum );
	}

};

class Simpson: public Integral{
public:
	Simpson( std::function<double(double)> f ): Integral(f) {}

	virtual double integrate ( double a, double b, int nSteps 
	) const override {
		const double h = ( b - a )/ (double)nSteps;
		
		double sumOdd = 0;
		double sumEven = 0;

		for(int i = 1; i <= (nSteps/2 - 1); i++){ sumEven += func( a + 2 * i * h ); }
		for(int i = 1; i <= (nSteps/2 ); i++){ sumOdd += func( a + ( 2 * i - 1 ) * h ); }
		
		return h / 3 * ( func(a) + func(b) + ( 4 * sumOdd ) + ( 2 * sumEven ) );
	}

};

#endif