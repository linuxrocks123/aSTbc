#include "Note.hpp"

#include <cctype>
using std::tolower;

Key Note::getKey()
{
     return context.key;
}

void Note::setKey(Key key_)
{
     //The octave is correct by definition.

     //We ALMOST got away with not having to calculate sharps/flats for a key :(
     int net_key_augmentation = 0;
     if(sharp_count)
	  net_key_augmentation = sharp_count - context.key.get_augmentation(tone);
     else if(flat_count)
	  net_key_augmentation = -flat_count - context.key.get_augmentation(tone);
     else if(naturalized)
	  net_key_augmentation = 0 - context.key.get_augmentation(tone);

     tone = static_cast<Tone>(tone + (key_.get_tone() - context.key.get_tone()));
     if(tone < 0)
	  tone = static_cast<Tone>(tone + 7);
     tone = static_cast<Tone>(tone % 7);

     //Reset semitone indicators for new key
     sharp_count = flat_count = naturalized = 0;

     //Calculate new semitone values
     int new_key_natural_augmentation = key_.get_augmentation(tone);
     int net_new_augmentation = net_key_augmentation + new_key_natural_augmentation;
     if(net_key_augmentation!=0)
	  if(net_new_augmentation>0)
	       sharp_count = net_new_augmentation;
	  else if(net_new_augmentation<0)
	       flat_count = net_new_augmentation;
	  else //net_new_augmentation==0
	       naturalized=true;

     //Good thing we decided to make the context per-note!
     context.key=key_;
}

int Note::getOctave()
{
     return octave;
}

void Note::setOctave(int octave_)
{
     octave = octave_;
}

ostream& operator<<(ostream& sout, const Note& note)
{
     //Print sharp/flat/natural
     if(note.sharp_count)
	  sout << '^';
     else if(note.flat_count)
	  sout << '_';
     else if(note.naturalized)
	  sout << '=';

     //Bear with me now.

     char letter;
     int octave = note.octave;

     if(note.tone < TONE_A)
	  letter = 'C';
     else if(note.tone <= TONE_B)
	  letter = 'A';
     else
          letter = 'z';

     if(note.tone <= TONE_B)
          letter += letter=='C' ? note.tone - TONE_C : note.tone - TONE_A;

     if(octave > 0)
     {
	  letter=tolower(letter);
	  octave--;
     }

     sout << letter;

     while(octave > 0)
     {
	  sout << '\'';
	  octave--;
     }
     while(octave < 0)
     {
	  sout << ',';
	  octave++;
     }

     //Now, finish up by printing the beat count and, if it exists, tie
     sout << note.beats;
     if(note.tied)
	  sout << '-';

     return sout;
}
