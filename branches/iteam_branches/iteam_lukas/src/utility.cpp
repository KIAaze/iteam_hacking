#include <cmath>

#include "utility.hpp"

int roundInt(double x) {
	x += 0.5;
	return (int) x;
}

int nextPowerOfTwo(int x) {
	double logBase2 = log(x) / log(2);
	return roundInt(pow(2, ceil(logBase2)));
}
