#include <Eigen>
#include <iostream>
using namespace Eigen;

void backtrack(VectorXf &xk1, VectorXf &xk, VectorXf &pk,\
	       	double pTg, double (*func)(VectorXf &))
{
    // initialize parameters
    // for line search 
    int j=0;
    bool sufficient_decrease = false;
    double alpha = 1.0;
    double rho   = 0.5;
    double c     = 1.e-4;
    double fkap;
    double fk = func(xk);
    int max_backtrack = 20;  
    while(j < max_backtrack && !sufficient_decrease)
    {
      xk1 = xk + alpha*pk;
      fkap = func(xk1); // f(x_k + alpha p_k)
      if(fkap < fk + c*alpha*pTg)
      {
	// Armijo rule satisfied
        sufficient_decrease=true;
      }   
      else
      {
	// continue backtracking
        j+=1;
	alpha = rho*alpha;
      }
    }
}

void optimizer(VectorXf &x, double tol, int max_iterations,\
		double (*func)(VectorXf &), void (*grad)(VectorXf &, VectorXf &))
{
  bool within_tol = false;
  //int max_iterations = 1000;
  int n = x.size();

  VectorXf xk = VectorXf::Zero(n);
  VectorXf xk1 = VectorXf::Zero(n);
  VectorXf g = VectorXf::Zero(n);
  VectorXf p = VectorXf::Zero(n);
  grad(x, g);

  double g0_norm = g.lpNorm<2>();
  double g_norm, pTg, fk, fkap,alpha;
  
  int i = 0;
  int j;
  while(i < max_iterations && !within_tol)
  {
    // evaluate function and gradient 
    // at current iterate
    xk = xk1;
    fk = func(xk);
    grad(xk, g);
    // determine search direction
    p = -1.*g;
    pTg = p.dot(g);
    
    backtrack(xk1, xk, p, pTg, func);
    
    // new iterate determined
    // has the gradient been
    // sufficiently reduced
    grad(xk1, g);
    g_norm = g.lpNorm<2>();
    if(g_norm / g0_norm < tol)
    {
      within_tol = true;
      printf("minimizer determined \n");
    }
    else
    {
      i+=1;
    }
  }
  x = xk1;
}


