#include "Visitor.hpp"

#include "Note.hpp"
#include "Voice_Root.hpp"

void Visitor::visit(YYSTYPE to_visit)
{
     visit_root(to_visit.root);
}

void Visitor::visit_root(list<Measure> root)
{
     for(list<Measure>::iterator i = root.begin(); i!=root.end(); i++)
	  visit_measure(*i);
}

void Visitor::visit_measure(Measure measure)
{
     for(list<Chord>::iterator i = measure.sequence.begin(); i!=measure.sequence.end(); i++)
	  visit_chord(*i);
}

void Visitor::visit_chord(Chord chord)
{
     for(list<Note>::iterator i = chord.notes.begin(); i!=chord.notes.end(); i++)
	  visit_note(*i);
}
