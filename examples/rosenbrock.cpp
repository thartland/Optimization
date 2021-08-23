#include <iostream>
#include <Eigen>
#include <math.h>
#include "rosenbrock.hpp"

using namespace std;
using namespace Eigen;

double fun_eval(VectorXf &);
void grad_eval(VectorXf &, VectorXf &);

int main()
{
  int n = 10; // problem dimension
  VectorXf x0 = VectorXf::Zero(n);
  VectorXf x  = VectorXf::Zero(n);
  VectorXf g  = VectorXf::Zero(n);
  x0.setRandom();
  double tol = 1.e-4;
  x = x0;
  optimizer(x, tol, fun_eval, grad_eval);
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
