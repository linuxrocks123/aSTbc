#ifndef VOICE_ROOT
#define VOICE_ROOT

#include <list>

#include "Measure.hpp"
#include "Note.hpp"

using std::list;

struct Voice_Root
{
     list<Measure> root;
     Measure measure;
     Chord chord;
     list<Note>& note_set;
     Note note;

     Voice_Root() : note_set(chord.notes) {}

     Voice_Root(Measure initial_measure) : note_set(chord.notes)
	  {
	       root.clear();
	       root.push_back(initial_measure);
	  }

     Voice_Root& operator=(Voice_Root& to_copy)
	  {
	       root=to_copy.root;
	       measure=to_copy.measure;
	       chord=to_copy.chord;
	       note=to_copy.note;
	       return *this;
	  }
};

#endif
