#include <Eigen>

using namespace Eigen;
void backrack(VectorXf &, VectorXf &, \
		VectorXf &, double, \
		double (*func)(VectorXf &));
void optimizer(VectorXf &, double, int,\
		double (*func)(VectorXf &), void (*grad)(VectorXf &, VectorXf &));

