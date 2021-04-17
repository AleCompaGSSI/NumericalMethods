#include "utils.h"

#include "integral.h"

#include <iostream>
#include <iomanip>
#include <cmath>

auto f = [] (double x){ return std::pow(x, 4) - 2 * x + 1;};

int main(){

	const int nDivision = 20;
	Simpson simpson(f);
	Trapezoidal trapezoidal(f);
	for(int i = 1; i <= nDivision; i++){
		double E_t_i = std::abs( trapezoidal.integrate( 0, 2, pow( 2,i ) ) - 4.4 ); 
		double E_s_i = std::abs( simpson.integrate( 0, 2, pow( 2,i ) ) - 4.4 );
		std::cout << i << "\t" << std::setprecision(10) << E_t_i << "\t" << E_s_i << std::endl;
	}

}