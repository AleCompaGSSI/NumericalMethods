#ifndef PENDULUM_H
#define PENDULUM_H

#include "utils.h"
#include "ode.h"

class Pendulum{
public:
	Pendulum(double g, double l) {

		auto dthetadt = [] (state_vector state, double t ){ return state[1]; };
		auto domegadt_gl = [] (state_vector state, double t, double g, double l ){ return -1.0 * g / l * std::sin(state[0]);};
		auto domegadt = std::bind(domegadt_gl, _1, _2, g, l);
		
		system.push_back(dthetadt);
		system.push_back(domegadt);
	}

public:
	ode_system system;
};

#endif