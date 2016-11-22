#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
//#include <lapacke.h>
#include "../ScientificComputingProject/HF_source/Eigen/Eigen/Dense"
#include "../ScientificComputingProject/HF_source/Eigen/Eigen/Eigenvalues"
#include "../ScientificComputingProject/HF_source/Eigen/Eigen/Cholesky"
#include "../ScientificComputingProject/HF_source/Eigen/Eigen/Core"
#include "hf_aux.cpp"
//#include "hf_main.cpp"

////note, must include -Wno-write-strings in test command
using namespace std;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix;
typedef std::vector<vector<double> > Real_Matrix;
typedef std::vector<vector<vector<vector<double> > > > Real_4dMatrix;


void test_En_nuc();
void test_HF_en();
void test_dens_mat();
void test_failed(string tname);
void test_passed(string tname);


int main(){

  test_En_nuc();
  test_HF_en();
  test_dens_mat();


}

void test_failed(string tname){
  cout << tname << " ...Test Failed." << endl;

  return;
}

void test_passed(string tname){
  cout << tname << " ...Test Passed." << endl;
}


void test_HF_en(){

  int ao = 7;
  int occ = 5;
  char *path ="/export/zgid/bawinogr/Test/test/Water_STO-3G";
  Matrix V = Matrix::Zero(ao*ao,ao*ao);
  Matrix C_mo = Matrix::Zero(ao,ao);
  Matrix evals = Matrix::Zero(ao,ao);

  double En = hf_main(ao,occ,path,V,C_mo,evals);

  if (abs(abs(En)-74.9421)<=pow(10,-4)){
    test_passed("HF Energy       ");
  }
  else{
    test_failed("HF Energy       ");
  }
  
  return;
}

void test_dens_mat(){
  int ao = 3;
  int occ = 2;
  Matrix C_ao = Matrix::Zero(ao,ao);
  Matrix P0 = Matrix::Zero(ao,ao);
  double Ptrace = 0;

  C_ao(0,0) = 1; C_ao(0,1) = 2; C_ao(0,2) = 3;
  C_ao(1,0) = 3; C_ao(1,1) = 1; C_ao(1,2) = 2;
  C_ao(2,0) = 2; C_ao(2,1) = 3; C_ao(2,2) = 1;

  build_P(ao, occ, C_ao, P0);
  
  for (int i=0; i<ao; i++){
    Ptrace += P0(i,i);
  }
  
  if (Ptrace==28){
    test_passed("Density Matrix  ");
  }
  else{
    test_failed("Density Matrix  ");
  }

  return;
}

void test_En_nuc(){
  int ao = 7;
  int occ = 5;
  char *path = "/export/zgid/bawinogr/Test/test/Water_STO-3G";


  double En_nuc = read_nuc_en(path);

  if (abs(abs(En_nuc)-8.002367061810450)<=pow(10,-8)){
    test_passed("Nuclear Energy  ");
  }
  else{
    test_failed("Nuclear Energy  ");
  }

  return;
}

