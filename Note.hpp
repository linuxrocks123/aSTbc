#ifndef NOTE_HPP
#define NOTE_HPP

//From Pygmalitype
#include "rational.h"

#include "parseresult.hpp"
#include "Tone.hpp"

//For operator<< only
#include <iostream>
using std::ostream;

class Key;

class Note
{
public:
     Tone tone;
     Rational beats;

     int octave;
     int sharp_count, flat_count;
     bool naturalized;

     bool tied;

     Tune context;

public:
     Note() : tone(TONE_C), beats(1,1), octave(0), sharp_count(0), flat_count(0), naturalized(false), tied(false) {}

     Key getKey();
     void setKey(Key key);
     int getOctave();
     void setOctave(int octave);
};

ostream& operator<<(ostream& sout, const Note& note);

#endif
