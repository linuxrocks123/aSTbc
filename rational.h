//CUSTOM VERSION for use with aSTbc
// rational.h: declaration of Rational ADT
#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>

using std::istream;
using std::ostream;

// Rational ADT: class description
class Rational {
	public: // member functions
		// constructor
		Rational(int numer = 0, int denom = 1);
		// some arithmetic and stream facilitators
		Rational Add(const Rational &r) const;
		Rational Multiply(const Rational &r) const;
		Rational Subtract(const Rational &r) const;
		Rational Divide(const Rational &r) const;
		void Insert(ostream &sout) const;
		void Extract(istream &sin);
		//facilitators
		int Compare(const Rational& r) const;
		// inspectors
		int Numerator() const;
		int Denominator() const;
	protected:
		// mutators
		void SetNumerator(int numer);
		void SetDenominator(int denom);
		//facilitators
		void Reduce();
	private:
		// data members
		int NumeratorValue;
		int DenominatorValue;
};

// Rational ADT: auxiliary operator description
Rational operator+(const Rational &r, const Rational &s);
Rational operator*(const Rational &r, const Rational &s);
Rational operator-(const Rational &r, const Rational &s);
Rational operator/(const Rational &r, const Rational &s);

ostream& operator<<(ostream &sout, const Rational &s);
istream& operator>>(istream &sin, Rational &r);
bool operator==(const Rational& r,const Rational& s);
bool operator>(const Rational& r,const Rational& s);
bool operator<(const Rational& r,const Rational& s);

#endif


