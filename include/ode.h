#ifndef ODE_H
#define ODE_H

#include "utils.h"

#include <functional>
#include <vector>

typedef std::vector<double> state_vector;
typedef std::vector<std::function<double(state_vector,double)>> ode_system;

class Ode{
public:
	Ode( ode_system s ): system(s) {}

	virtual void integrate( state_vector &x, 
							const double t, const double step ) const = 0;

public:
	ode_system system;


};

class Euler: public Ode{
public:
	Euler( ode_system s ): Ode(s) {}

	virtual void integrate ( state_vector &x,
							const double t, const double step  
	) const override {
		for ( int i = 0; i<x.size(); i++) x[i] = x[i] + step * system[i](x,t);
		return;

	}

};

class RungeKutta2: public Ode{
public:
	RungeKutta2( ode_system s ): Ode(s) {}

	virtual void integrate ( state_vector &x,
							const double t, const double step  
	) const override {
		state_vector k1,x1;
		state_vector k2;
		for ( int i = 0; i<x.size(); i++) k1.push_back(step * system[i](x,t));
		for ( int i = 0; i<x.size(); i++) x1.push_back(x[i] + 0.5 * k1[i]);
		for ( int i = 0; i<x.size(); i++) k2.push_back(step * system[i](x1,t + 0.5 * step));

		for ( int i = 0; i<x.size(); i++) x[i] = x[i] + k2[i];
		return;

	}

};

#endif