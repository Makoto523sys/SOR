#ifndef _SOR_H_
#define _SOR_H_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

void sor(std::vector<std::vector<double>>&, std::vector<double>&, std::vector<double>&);
bool is_convergence(const std::vector<double>&, const std::vector<double>&);
void show_problem(const std::vector<std::vector<double>>&, std::vector<double>&);

/******************************************
 * sor method for linear problem
 * when you use this method,
 * osr(std::vector<std::vector<double>>& coefficient_matrix, std::vector<double>& X, std::vector<double>& b)
 ******************************************/
inline void sor(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>&  b){
	const double omega = 1.1;
	unsigned int iter = 0;
	int rows = A.size();//行
	int cols = A[0].size();//列
	std::fill(x.begin(), x.end(), 0);
	std::vector<double> prex(x.size());
	//prex.resize(rows);
	double tmp = 0.0f;
	//std::copy(x.begin(), x.end(), prex.begin());
	bool did_finish = false;

	while(!did_finish){
		for(int i = 0; i < rows; i++){
			double tmp = 0;
			for(int j = 0; j < cols; j++)
			       if(j != i) tmp += A[i][j] * x[j];
			tmp = (b[i] - tmp) / A[i][i];
			std::copy(x.begin(), x.end(), prex.begin());
			x[i] = x[i] + omega * (tmp - x[i]);
		}
		did_finish = is_convergence(x, prex);
		iter++;
	}

	std::cout << "Show Results" << std::endl;
	std::cout << "Repetition Count:" << std::setw(6) << iter << std::endl;
	std::cout << "Answer:" << std::endl;
	for(int i = 0; i < rows; i++) std::cout << "\tx" << i + 1 << " = " << x[i] << std::endl;
}

inline bool is_convergence(const std::vector<double>& x, const std::vector<double>& prex){
	static const double eps = 1e-10;
	for(int i = 0; i < x.size(); i++)
		if(std::fabs(x[i] - prex[i]) > eps) return false;
	return true;
}

inline void show_problem(const std::vector<std::vector<double>>& A, std::vector<double>& b){
	int rows = A.size();
	int cols = A[0].size();
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols - 1; j++){
			std::cout << A[i][j] << "x_" << j+1 << " + ";
		}
		std::cout << A[i][A[i].size() - 1] << "x_" << cols << " = " << b[i] << std::endl;
	}
}

#endif 
