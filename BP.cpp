#include <vector>
#include <iomanip>
#include <iostream>
#include "rtm.h"

double a = 1.1;
double b = 1.4;
double h = 0.01;
int N = (b - a) / h;

double S = 1;
double R = -0.5;
double T = 2;

double W = 0;
double V = 1;
double Z = 4;

std::vector<double> x;
std::vector<double> ci;
std::vector<double> di;
std::vector<double> y(N + 1);
Matrix mtrx(N + 1);

double K(double x){
	return x;
}

double L(double x){
	return - x;
}

double M(double x){
	return 2 / x;
}

double F(double x){
	return x + 0.4;
}



void find_xi(){
	for(double xi = a; xi < b; xi += h){
		x.push_back(xi);
	}
	if(x.size() > N + 1){
		std::cerr << " aaaaaa ";
	}
}

void create_matrix(){
	for(int i = 0; i < N + 1; i++){
		for (int j = 0; j < N + 2; j++){
			if (i == 0){
				if(j == i){
					mtrx[i][j] = - R / h + S;
				} else if (j == i + 1){
					mtrx[i][j] = R / h;
				} else if (j == N + 1){
					mtrx[i][j] = T;
				} else {
					mtrx[i][j] = 0;
				}
			} else if (i == N){
				if(j == i){
					mtrx[i][j] = - V / h - W;
				} else if (j == i - 1){
					mtrx[i][j] = V / h;
				} else if (j == N + 1){
					mtrx[i][j] = - Z;
				} else {
					mtrx[i][j] = 0;
				}
			} else {
				if (j == i - 1){
					mtrx[i][j] = K(x[i]) / (h * h) - L(x[i]) / (2 * h);
				} else if (j == i){
					mtrx[i][j] = - 2 * K(x[i]) / (h * h) + M(x[i]);
				} else if (j == i + 1){
					mtrx[i][j] = K(x[i]) / (h * h) + L(x[i]) / (2 * h);
				} else {
					mtrx[i][j] = 0;
				}
			}
		}
	}
//	std::cout << mtrx << std::endl;
}

int main(){
	find_xi();
	create_matrix();
	rtm(mtrx);

	return 0;
}


