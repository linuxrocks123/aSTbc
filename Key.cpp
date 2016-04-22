#include "Key.hpp"

Key::Key(Tone tone_, Semitone stepping, Mode mode)
{
     tone=tone_;
                                   /*whole whole half   whole whole whole half*/
     bool tonal_pattern[] = {true, true, false, true, true, true, false};

     //Left rotate for scale
     for(int i=0; i<tone; i++)
     {
	  bool wrapped = tonal_pattern[0];
	  for(int j=0; j<6; j++)
	       tonal_pattern[j] = tonal_pattern[j+1];
	  tonal_pattern[6] = wrapped;
     }

     //Generate notemask
     const static bool ionian_pattern[] = {true, true, false, true, true, true, false};
     int semitone_state = stepping < 2 ? stepping : -1;
     for(int i=0; i<7; i++)
     {
	  if(semitone_state!=0)
	       sharpped = semitone_state > 0;
	  notemask[(tone+i)%7] = (semitone_state!=0);
	  //calculate for next iteration
	  semitone_state += (tonal_pattern[(tone+i)%7] - ionian_pattern[(tone+i)%7]);
     }
}

int Key::get_augmentation(Tone tone)
{
     return sharpped ? notemask[tone] : -notemask[tone];
}
