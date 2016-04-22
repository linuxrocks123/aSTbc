// Compute the greatest common divisor of two integers
// Use Euclid's algorithm
#ifndef GCD_H
#define GCD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "gcd.h"

using std::cerr;
using std::exit;
using std::endl;

// swap two values
template<class t>
void Swap(t &n1, t &n2) {
   t tmp;
   tmp = n1;
   n1 = n2;
   n2 = tmp;
}

template<class t>
t gcd(t m, t n) {

   // ensure that m is greater than or equal to n
	if (m < n) {
		Swap(m, n);
	}

	if (n == 0) {
		cerr << "bad gcd request" << endl;
		exit(1);
	}

	// loop until r is 0

	int r = m % n;

	while (r) {
		m = n;
		n = r;
		r = m % n;
	}

	return n;
}

#endif
