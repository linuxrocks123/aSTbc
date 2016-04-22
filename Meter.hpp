#ifndef METER_HPP
#define METER_HPP

#include <iostream>

using std::istream;
using std::ostream;

struct Meter
{
     int beats_per_measure;
     int freq_of_beat;
};

inline ostream& operator<<(ostream& left, const Meter& right)
{
     left << right.beats_per_measure << '/' << right.freq_of_beat;
     return left;
}

inline istream& operator>>(istream& left, Meter& right)
{
     char slash;
     left >> right.beats_per_measure >> slash >> right.freq_of_beat;
}

#endif
