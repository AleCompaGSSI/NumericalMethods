#include "utils.h"

#include "ode.h"
#include "pendulum.h"

#include <iostream>

int main(){

	//define pendulum sistem of equations

	const double g = 10.0;
	const double l = 0.1;

	Pendulum pendulum( g, l );

	ode_system sys = pendulum.system;

	const int steps = 20000;
	const double step_size = 0.01;

	double t = 0.0;
	state_vector state{degrees_to_radians(170.0), 0.0};
	//Euler eu(sys);
	RungeKutta2 rk2(sys);

	for(int i = 1; i <= steps; i++){
		rk2.integrate(state, t, step_size);
		t += step_size;
		std::cout << t << " " << fmod(state[0] , (2*pi)) << " " << state[1] << std::endl;
		//std::cout << t << " " << (0.5 * std::pow(state[1],2) * l * l )+ (g * l * (1-std::cos(state[0]))) << std::endl;		
	}

}