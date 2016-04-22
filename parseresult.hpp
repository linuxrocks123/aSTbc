#ifndef PARSERESULT_HPP
#define PARSERESULT_HPP

#include <map>
#include <string>

using std::map;
using std::string;

#include "Key.hpp"
#include "Meter.hpp"
#include "rational.h"

class Voice_Root;

enum Clef {TREBLE, BASS};

class Tune
{
public:
     string X, V, K, Q, T, A;
     Clef clef;
     Key key;
     Rational L_value;
     Meter meter;
};

inline bool operator<(const Tune& left, const Tune& right)
{
     if(left.X!=right.X)
	  return left.X < right.X;
     return left.V < right.V;
}

#define YYSTYPE Voice_Root
int yylex();
int yyerror (char* msg);

extern map<Tune,YYSTYPE> parseresult;
extern Tune next_index;

#endif
