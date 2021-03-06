#ifndef HF_AUX_H
#define HF_AUX_H
#include <iostream>
#include <iomanip> 
#include <cstdlib> 
#include <vector>
#include <cmath>
#include "Dense"
#include "Eigenvalues"
#include "Cholesky"
#include "Core"

using namespace std;
//////Here are the functions required for HF

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix;
typedef std::vector<vector<double> > Real_Matrix;
typedef std::vector<vector<vector<vector<double> > > > Real_4dMatrix;

double read_nuc_en(char* Path);

void read_T(int ao, Matrix& T_int,char* Path);

void read_S(int ao, Matrix& S, char* Path);

void read_v_nuc(int ao, Matrix& v_nuc, char* Path);

void build_H_core(int ao, Matrix& v_nuc, Matrix& T_int, Matrix& H_core);

void read_v_int(int ao, Matrix& V, char* Path);

void calculate_S12(int ao, Matrix& S, Matrix& S12, Matrix& Xmat);

void diagonalize_Fock(int ao, Matrix& H_core, Matrix& Xmat, Matrix& C_ao, Matrix& evals, Matrix& evecs);

void build_P(int ao, int occ, Matrix& C_ao, Matrix &P0);

double calculate_En_elec(int ao, Matrix& P0, Matrix& H_core, Matrix& Fock);

void build_new_Fock(int ao, Matrix& P0, Matrix& v_int, Matrix&H_core, Matrix&Fock);

#endif
