#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Dense"
#include "Eigenvalues"
#include "Cholesky"
#include "Core"
#include <iomanip>



typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix;
//typedef std::vector<vector<double> > Real_Matrix;
//typedef std::vector<vector<vector<vector<double> > > > Real_4dMatrix;

void transform_v_int(int ao, Matrix& C, Matrix& v_int, Matrix& v_int_mo){

   int i, j, k, l;
   int a,b,c,d;
 
   std::clock_t start;
   start = std::clock();
 
   for(a=0; a < ao; a++) {
     for(b=0; b < ao; b++) {
       for(c=0; c < ao; c++) {
         for(d=0; d < ao; d++) {
  
           for(i=0; i < ao; i++) {
             for(j=0; j < ao; j++) {
               for(k=0; k < ao; k++) {
                 for(l=0; l < ao; l++) {
  
                   v_int_mo(a*ao+b,c*ao+d) += C(i,a) * C(j,b) * C(k,c) * C(l,d)*v_int(i*ao+j,k*ao+l); 
		   //cout << v_int_mo[a][b][b][d] << endl;
                 }
               }
             }
           }  
         }
       }
     }
   }

   std::cout << "\t" << "Time in N^8: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC/1000) << "ms" << std::endl;  
   return;
};

void transform_v_int_2(int ao, Matrix& v_int, Matrix& v_int_mo_2, Matrix& C_mo){
  int a,b,c,d,e;


  Matrix v1 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v2 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v3 = Matrix::Zero(ao*ao,ao*ao);

  std::clock_t start;
  start = std::clock();

  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<ao;c++){	
	for (d=0;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v1(a*ao+b,c*ao+d) += v_int(a*ao+b,c*ao+e)*C_mo(e,d);
	  }
	}
      }
    }
  }
  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<ao;c++){
	for (d=0;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v2(a*ao+b,c*ao+d) += v1(a*ao+b,e*ao+d)*C_mo(e,c);
	  }
	}
      }
    }
  }
  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<ao;c++){
	for (d=0;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v3(a*ao+b,c*ao+d) += v2(a*ao+e,c*ao+d)*C_mo(e,b);
	  }
	}
      }
    }
  }
  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<ao;c++){
	for (d=0;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v_int_mo_2(a*ao+b,c*ao+d) += v3(e*ao+b,c*ao+d)*C_mo(e,a);
	  }
	}
      }
    }
  }

  std::cout << "\t" << "Time in N^5: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC/1000) << "ms" << std::endl;

  return;
}


//Sahil's addition

void transform_v_int_Sahil_parallel_try(int ao, Matrix& v_int, Matrix& v_int_mo_2, Matrix& C_mo){
  int a,b,c,d,e,r,s,t,u;


  Matrix v1 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v2 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v3 = Matrix::Zero(ao*ao,ao*ao);

  std::clock_t start;
  start = std::clock();

  for (r=0;r<ao;r++){
    for (s=0;s<ao;s++){
      for (t=0;t<ao;t++){
        for (u=0;u<ao;u++){
          for (d=0;d<ao;d++){
            v_int(r*ao+s,t*ao+d) += v_int(r*ao+s,t*ao+u)*C_mo(u,d);
          }
        }
      }
    }
  }
  for (r=0;r<ao;r++){
    for (s=0;s<ao;s++){
      for (d=0;d<ao;d++){
        for (t=0;t<ao;t++){
          for (c=0;c<ao;c++){
            v_int(r*ao+s,c*ao+d) += v_int(r*ao+s,t*ao+d)*C_mo(t,c);
          }
        }
      }
    }
  }
  for (r=0;r<ao;r++){
    for (s=0;s<ao;s++){
      for (d=0;d<ao;d++){
        for (c=0;c<ao;c++){
	for (b=0;b<ao;b++){
            v_int(r*ao+b,c*ao+d) += v_int(r*ao+s,c*ao+d)*C_mo(s,b);
          }
        }
      }
    }
  }
  for (r=0;r<ao;r++){
    for (t=0;t<ao;t++){
      for (d=0;d<ao;d++){
        for (c=0;c<ao;c++){
          for (b=0;b<ao;b++){
	    for (a=0;a<ao;a++){
            	v_int(a*ao+b,c*ao+d) += v_int(r*ao+b,t*ao+d)*C_mo(r,a);
		v_int_mo_2(a*ao+b,c*ao+d) = v_int(a*ao+b,c*ao+d);
	    }
          }
        }
      }
    }
  }
   
  std::cout << "\t" << "Time in N^5: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC/1000) << "ms" << std::endl;

  return;
}

//Sahil's done here




void transform_v_int_3(int occ, int ao, Matrix& v_int, Matrix& v_int_mo_2, Matrix& C_mo){
  int a,b,c,d,e;


  Matrix v1 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v2 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v3 = Matrix::Zero(ao*ao,ao*ao);

  std::clock_t start;
  start = std::clock();


  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<ao;c++){	
	for (d=occ;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v1(a*ao+b,c*ao+d) += v_int(a*ao+b,c*ao+e)*C_mo(e,d);
	  }
	}
      }
    }
  }
  for (a=0;a<ao;a++){
    for (b=0;b<ao;b++){
      for (c=0;c<occ;c++){
	for (d=occ;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v2(a*ao+b,c*ao+d) += v1(a*ao+b,e*ao+d)*C_mo(e,c);
	  }
	}
      }
    }
  }
  for (a=0;a<ao;a++){
    for (b=occ;b<ao;b++){
      for (c=0;c<occ;c++){
	for (d=occ;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v3(a*ao+b,c*ao+d) += v2(a*ao+e,c*ao+d)*C_mo(e,b);
	  }
	}
      }
    }
  }
  for (a=0;a<occ;a++){
    for (b=occ;b<ao;b++){
      for (c=0;c<occ;c++){
	for (d=occ;d<ao;d++){
	  for (e=0;e<ao;e++){
	    v_int_mo_2(a*ao+b,c*ao+d) += v3(e*ao+b,c*ao+d)*C_mo(e,a);
	  }
	}
      }
    }
  }

  std::cout << "\t" << "Time in v^2o^2: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC/1000) << "ms" << std::endl;

  return;
}


void transform_v_int_CD(int ao, Matrix& v_int, Matrix& v_int_mo_2, Matrix& C_mo){
  int a,b,c,d,e;

  Matrix v1 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v2 = Matrix::Zero(ao*ao,ao*ao);
  Matrix v3 = Matrix::Zero(ao*ao,ao*ao);

  std::clock_t start;
  start = std::clock();


  std::cout << "Cholesky Decomp" << std::endl;

  Eigen::LLT<Matrix> lltOfC_mo(C_mo);
  Matrix L = lltOfC_mo.matrixL();
//  Matrix D = ldltOfC_mo.vectorD();

  std::cout << "L is: " << L << std::endl;
  std::cout << "L^T is: " << L.transpose() << std::endl;
  std::cout << "the shape of L is: " << L.size() << L.cols() << L.rows() << std::endl;

//  std::cout << "D is: " << D << std::endl;

//  Eigen::LLT<Matrix> lltOfL(L);
//  Matrix LL = lltOfL.matrixL();
//
//  Eigen::LLT<Matrix> lltOfLT(L.transpose());
//  Matrix LT = lltOfLT.matrixL();
////  Matrix D = ldltOfC_mo.vectorD();
//
//
//  std::cout << "LL is: " << LL << std::endl;
//  std::cout << "LL^T is: " << LL.transpose() << std::endl;
//
//  std::cout << "LT is: " << LT << std::endl;
//  std::cout << "LT^T is: " << LT.transpose() << std::endl;

  Matrix tempA = Matrix::Zero(ao,ao);
  Matrix tempB = Matrix::Zero(ao,ao);
  Matrix tmpLT = L.transpose();
  for (int i=0;i<ao;i++){
    for (int j=0;j<ao;j++){
      for (int sig=0;sig<ao;sig++){
        for (int rho=0;rho<ao;rho++){
           tempA(i,j) += C_mo(sig,i)*C_mo(rho,j)*tmpLT(sig,rho);
        }
      }
    }
  }
  

  for (int a=0;a<ao;a++){
    for (int b=0;b<ao;b++){
      for (int mu=0;mu<ao;mu++){
        for (int nu=0;nu<ao;nu++){
           tempB(a,b) += C_mo(a,mu)*C_mo(b,nu)*L(mu,nu)*tempA(a,b);
        }
      }
    }
  }

  for (int a=0;a<ao;a++){
    for (int b=0;b<ao;b++){
      for (int i=0;i<ao;i++){
        for (int j=0;j<ao;j++){
           v_int_mo_2(a*ao+b,i*ao+j) += tempB(a,b)*tempA(i,j);
        }
      }
    }
  }

  std::cout << "\t" << "Time in N^4: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC/1000) << "ms" << std::endl;
  return;
}


double calculate_E_mp2(int ao, int occ, Matrix& evals, Matrix& v_int_mo, char* sname){
   double E_mp2 = 0.0;

   for(int i=0; i < occ; i++) {
       for(int j=0; j < occ; j++) {
	 for(int a=occ; a < ao; a++) {
	   for(int b=occ; b < ao; b++) {

            E_mp2 += v_int_mo(i*ao+a,j*ao+b)*(2*v_int_mo(i*ao+a,j*ao+b)-v_int_mo(i*ao+b,j*ao+a))/(evals(i)+evals(j)-evals(a)-evals(b));

         }
       }
     }
   }

   std::cout << "\t" << sname << " MP2 energy: " << E_mp2 << std::endl;
   return E_mp2;
};


double mp2_main(int ao, int occ, char* Path, Matrix& V, Matrix& C_mo, Matrix& evals, double En_total){ 

  std::cout << "Transforming to MO basis" << std::endl;
  Matrix V_mo = Matrix::Zero(ao*ao,ao*ao);
  Matrix V_mo_2 = Matrix::Zero(ao*ao,ao*ao);
  Matrix V_mo_sahil = Matrix::Zero(ao*ao,ao*ao);
  Matrix V_mo_3 = Matrix::Zero(ao*ao,ao*ao);
  //Matrix V_mo_CD = Matrix::Zero(ao*ao,ao*ao); 
  
  transform_v_int(ao, C_mo, V, V_mo);
  transform_v_int_2(ao, V, V_mo_2, C_mo);
  transform_v_int_3(occ, ao, V, V_mo_3, C_mo);
  //transform_v_int_CD(ao, V, V_mo_CD, C_mo);                                        
  transform_v_int_Sahil_parallel_try(ao, V, V_mo_sahil, C_mo);

  //calculate MP2 energy                         
  ////////we want to get Emp2 = -0.049149636120            
  std::cout << "Calculating MP2 energy" << std::endl;
  double Emp2 = calculate_E_mp2(ao, occ, evals, V_mo, "N^8");
  double Emp2_2 = calculate_E_mp2(ao, occ, evals, V_mo_2, "N^5");
  double Emp2_3 = calculate_E_mp2(ao, occ, evals, V_mo_3, "v^2o^2");
  double Emp2_sahil = calculate_E_mp2(ao, occ, evals, V_mo_sahil, "sahil");
  //double Emp2_CD = calculate_E_mp2(ao,occ,evals, V_mo_CD, "CD");

  std::cout << "Calculating total energy with MP2 correction" << std::endl;
  std::cout << "\t" << "The final energy is: " << En_total + Emp2 <<std::endl;
  std::cout << "\t" << "The final energy with the N^5 v_int_mo is: " << En_total + Emp2_2 << std::endl;
  std::cout << "\t" << "The final energy with SAHIL's v_int_mo is: " << En_total + Emp2_sahil << std::endl;
  std::cout << "\t" << "The final energy with the o^2v^2N v_int_mo is: " << En_total + Emp2_3 << std::endl;
  //cout << "The final energy with the N^3 v_int_mo is: " << En_total + Emp2_CD << endl;

  return Emp2;
}
