#include <iostream>
#include <Eigen>
#include <math.h>
#include "optimizer.hpp"

using namespace std;
using namespace Eigen;

double fun_eval(VectorXf &);
void grad_eval(VectorXf &, VectorXf &);

int main(int argc, char* argv[0])
{
  if(argc < 3)
  {
    printf("incorrect usage, please specify problem dimension and tolerance\n");
    return 1;
  }
  const int n = std::stod(argv[1]); // user specifies problem dimension
  const double tol = std::stod(argv[2]);
  const int max_iter = 1000;
  VectorXf x0 = VectorXf::Zero(n);
  VectorXf x  = VectorXf::Zero(n);
  VectorXf g  = VectorXf::Zero(n);
  x0.setRandom();
  x = x0;
  optimizer(x, tol, max_iter, fun_eval, grad_eval);
  printf("x0 = (");
  for(int i = 0; i < n-1; i++)
  {
    printf("%f, ", x0[i]);
  }
  printf("%f)\n", x0[n-1]);

  printf("x = (");
  for(int i = 0; i < n-1; i++)
  {
    printf("%f, ", x[i]);
  }
  printf("%f)\n", x[n-1]);
  return 0;
}

double fun_eval(VectorXf &x)
{
  int n = x.size();
  double fx = 0.;
  for(int i = 1; i<n; i+=2)
  {
    fx+= 100.*pow(x[i]-x[i-1],2) + pow(x[i-1]-1.,2);
  }
  return fx;
}

void grad_eval(VectorXf &x, VectorXf &g)
{
  int n = x.size();
  for(int i =1; i<n; i+=2)
  {
    g[i-1] = 200.*(x[i-1]-x[i]) +2.*(x[i-1]-1.);
    g[i]   = 200.*(x[i]-x[i-1]);
  }
}
