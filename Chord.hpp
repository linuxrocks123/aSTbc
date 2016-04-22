#ifndef CHORD_HPP
#define CHORD_HPP

#include <list>
using std::list;

class Note;

struct Chord
{
     list<Note> notes;
     bool single_element_is_chord;
};

#endif
