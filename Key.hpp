#ifndef KEY_HPP
#define KEY_HPP

#include "Tone.hpp"

//Should be static data member but for some reason won't work as one
const static char* mode_tbl[] = { "ION", "DOR", "PHR", "LYD", "MIX", "AEO", "LOC",
				  "MAJ", "", "", "", "", "MIN" };

class Key
{
public:
     enum Semitone { NATURAL=0, SHARP, FLAT };
     enum Mode { IONIAN=0, DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN, AEOLIAN, LOCRIAN };
     Key(Tone tone, Semitone stepping, Mode mode);
     Key() {}

     int get_augmentation(Tone tone);
     Tone get_tone() { return tone; }

private:
     Tone tone;
     bool sharpped;
     bool notemask[7]; //You can index into this with a Tone.
};

#endif
