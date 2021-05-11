#include "utils.h"

#include <gsl.h>
#include <iostream>

std::vector<double> CrankNicolson(std::vector<double> f, double alpha, std::vector<double> QDeltat) {
	
	auto N = f.size();
	std::vector<double> fNew(N);

	std::vector<double> centralDiagonal(N - 2);
	std::vector<double> rhs(N - 2);
	std::vector<double> lowerDiagonal(N - 3);
	std::vector<double> upperDiagonal(N - 3);

	std::fill(centralDiagonal.begin(), centralDiagonal.end(), 1.0 + 2.0 * alpha);
	std::fill(lowerDiagonal.begin(), lowerDiagonal.end(), -1.0 * alpha);
	std::fill(upperDiagonal.begin(), upperDiagonal.end(), -1.0 * alpha);

	for (size_t i = 1; i < N - 1; ++i) {
		rhs[i - 1] = (1.0 - 2.0 * alpha) * f[i] +  alpha * (f[i + 1] + f[i - 1]) + QDeltat[i];
	}

	std::vector<double> solution(N - 2);
	GSL::gsl_linalg_solve_tridiag(centralDiagonal, upperDiagonal, lowerDiagonal, rhs, solution);

	for (size_t i = 1; i < N - 1; ++i) fNew[i] = solution[i - 1];
	fNew[0] = 0.;
	fNew[N - 1] = 0.;
	return fNew;
}

double computeRMSError( std::vector<double> x, std::vector<double> v) {
	auto N = x.size();
	double sum = 0.0;
	for (size_t i = 0; i < N; i++) sum += pow(x[i] - v[i], 2.0);
	return std::sqrt(sum / (double) N);
}

int main(){

	const double H = 1.0;
	const double D = 0.1;
	const double Dt = 1.0e-3;
	const double xMin = -1.0;
	const double xMax = 1.0;
	const size_t N = std::pow(2, 9);

	const auto x = linspace(xMin, xMax, N);
	const auto dx = x[1] - x [0];

	const double alpha = D * Dt / (2 * dx * dx);
	
	//std::cout<< alpha << std::endl;

	std::vector<double> f(N, 0.0);
	
	std::vector<double> QDeltat;
	QDeltat.reserve(N);
	for (auto xi : x) {
		const auto value = Dt * ( D * pi * pi * 0.25) * std::cos( pi * xi * 0.5 );
		QDeltat.emplace_back(value);
	}

	std::vector<double> fAsympt;
	fAsympt.reserve(N);
	for (auto xi : x) {
		const auto value = std::cos( pi * xi * 0.5 );
		fAsympt.emplace_back(value);
	}

	double t = 0;

	//for (size_t i = 0; i < N; i++) std::cout << x[i] << " " << fAsympt[i] << std::endl;

	while (t<20) {
		f = CrankNicolson(f, alpha, QDeltat);
		t += Dt;

	}
	while (t<80) {
		f = CrankNicolson(f, alpha, QDeltat);
		t += Dt;
		std::cout << t << " " << computeRMSError(f, fAsympt) << std::endl;

	}


}