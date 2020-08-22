#ifndef _SOR_H_
#define _SOR_H_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

void sor(std::vector<std::vector<double>>&, std::vector<double>&, std::vector<double>&, const double);
bool is_convergence(const std::vector<double>&, const std::vector<double>&);
void show_problem(const std::vector<std::vector<double>>&, std::vector<double>&);
void pivot(const int row, std::vector<std::vector<double>>& A, std::vector<double>& b);

/******************************************
 * sor method for linear problem
 * when you use this method,
 * osr(std::vector<std::vector<double>>& coefficient_matrix, std::vector<double>& X, std::vector<double>& b)
 ******************************************/
inline void sor(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>&  b, const double omega){
	unsigned int iter = 0;
	int rows = A.size();//行
	int cols = A[0].size();//列
	std::fill(x.begin(), x.end(), 0);
	std::vector<double> prex(x.size());
	//prex.resize(rows);
	//std::copy(x.begin(), x.end(), prex.begin());
	bool did_finish = false;

	while(!did_finish){
		for(int i = 0; i < rows; i++){
			pivot(i, A, b);
			double tmp = 0;
			for(int j = 0; j < cols; j++)
			       if(j != i) tmp += A[i][j] * x[j];
			tmp = (b[i] - tmp) / A[i][i];
			std::copy(x.begin(), x.end(), prex.begin());
			x[i] = omega * tmp + (1.0 - omega) * x[i];
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
			std::cout << A[i][j] << " x_" << j+1 << " + ";
		}
		std::cout << A[i][A[i].size() - 1] << "x_" << cols << " = " << b[i] << std::endl;
	}
}

void pivot(const int row, std::vector<std::vector<double>>& A, std::vector<double>& b){
	int n = b.size();
	double max_diagonal = std::abs(A[row][row]);
	double max_row = row;
	for(int i = row; i < n; i++){
		if(max_diagonal < std::abs(A[i][row])){
			max_row = i;
			max_diagonal = std::abs(A[i][row]);
		}
	}
	if(max_row == row) return;
	else{
		std::vector<double> tmp(n);
		std::copy(A[row].begin(), A[row].end(), tmp.begin());
		std::copy(A[max_row].begin(), A[max_row].end(), A[row].begin());
		std::copy(tmp.begin(), tmp.end(), A[max_row].begin());
	}
}

#endif 
