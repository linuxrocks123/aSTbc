//CUSTOM VERSION for use with aSTbc

#include <iostream>
#include <string>
#include "gcd.h"
#include "rational.h"

using std::cerr;
using std::istream;

// (numer, denom) constructor
Rational::Rational(int numer, int denom) {
	SetNumerator(numer);
	SetDenominator(denom);
	Reduce();
}

// get the numerator
int Rational::Numerator() const {
	return NumeratorValue;
}

// get the denominator
int Rational::Denominator() const {
	return DenominatorValue;
}

// set the numerator
void Rational::SetNumerator(int numer) {
	NumeratorValue = numer;
}

// set the denominator
void Rational::SetDenominator(int denom) {
	if (denom != 0)
		DenominatorValue = denom;
	else {
		cerr << "Illegal denominator: " << denom
		<< " using 1" << endl;
		DenominatorValue = 1;
	}
}

// adding Rationals
Rational Rational::Add(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*d + b*c, b*d);
}

// multiplying Rationals
Rational Rational::Multiply(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*c, b*d);
}


// inserting a Rational
void Rational::Insert(ostream &sout) const {
        if(Numerator()!=1)
	    sout << Numerator();
	if(Denominator()!=1)
	    sout << '/' << Denominator();
	return;
}

// extracting a Rational
void Rational::Extract(istream &sin) {
	int numer;
	int denom;
	char slash;
	sin >> numer >> slash >> denom;
	SetNumerator(numer);
	SetDenominator(denom);
	Reduce();
	return;
}

// adding Rationals
Rational operator+(const Rational &r,
const Rational &s) {
	return r.Add(s);
}

// multiplying Rationals
Rational operator*(const Rational &r,
const Rational &s) {
	return r.Multiply(s);
}

// inserting a Rational
ostream& operator<<(ostream &sout, const Rational &r) {
	r.Insert(sout);
	return sout;
}

// extracting a Rational
istream& operator>>(istream &sin, Rational &r) {
	r.Extract(sin);
	return sin;
}

void Rational::Reduce()
{
	bool Signs=false; //tell whether to switch signs at end
	int GCD;
	if (!Numerator() || !Denominator())
		return;
	if (Numerator() < 0)
	{
		SetNumerator(-Numerator());
		Signs=true;
	}
	if (Denominator() < 0)
	{
		Signs=-Signs; //if numerator also switched, set false; otherwise will be true
		SetDenominator(-Denominator());
	}
	GCD=gcd(Numerator(),Denominator());
	SetNumerator(Numerator()/GCD);
	SetDenominator(Denominator()/GCD);
	if (Signs)
		SetNumerator(-Numerator()); //set numerator back if fraction originally negative
	//all done
}

int Rational::Compare(const Rational& r) const
{
	const int& a=Numerator();
	const int& b=Denominator();
	const int& c=r.Numerator();
	const int& d=r.Denominator();
	if (a*d == b*c)
		return 0;
	else if (a*d < b*c)
		return -1;
	else return 1;
}

bool operator<(const Rational& r, const Rational& s)
{
	if(r.Compare(s)==-1)
		return true;
	return false;
}

bool operator>(const Rational& r, const Rational& s)
{
	if(r.Compare(s)==1)
		return true;
	return false;
}

bool operator==(const Rational& r, const Rational& s)
{
	if(!r.Compare(s))
		return true;
	return false;
}
