#include<iostream>
#include<vector>
#include<fstream>
#include"sor.h"

int main(int argc, char **argv){
	std::vector<std::vector<double>> A;
	std::vector<double> x;
	std::vector<double> b;
	if(argc != 2){
		std::cout << "Useage:\n command [file]" << std::endl;
		return 1;
	}
	std::ifstream in{argv[1]};
	int row_size;
	int col_size;
	in >> row_size;
	in >> col_size;
	A.resize(row_size);
	b.resize(row_size);
	x.resize(row_size);
	for(int i = 0; i < row_size; i++) A[i].resize(col_size);
	for(int i = 0; i < row_size; i++){
		for(int j = 0; j < col_size; j++)
			in >> A[i][j];
		in >> b[i];
	}
	//show_problem(A, b);
	sor(A, x, b);
	return 0;
}
