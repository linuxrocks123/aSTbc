#include "Print_Visitor.hpp"
#include "Note.hpp"

#include <iostream>
using std::cout;
using std::endl;

void Print_Visitor::visit_root(list<Measure> root)
{
     if(print_header)
     {
	  cout << "X: " << context.X << endl;
          cout << "T: " << context.T << endl;
          cout << "A: " << context.A << endl;
	  cout << "M: " << context.meter << endl;
	  cout << "L: " << context.L_value.Numerator() << '/' << context.L_value.Denominator() << endl;
          cout << "K: " << context.K << endl;
          cout << "Q: " << context.Q << endl;
     }

     cout << "V: " << context.V << endl;

     Visitor::visit_root(root);
     cout << "]\n";
}

void Print_Visitor::visit_measure(Measure measure)
{
     Visitor::visit_measure(measure);
     cout << "|";
}

void Print_Visitor::visit_chord(Chord chord)
{
     if(chord.notes.size()>1 || chord.single_element_is_chord)
     {
	  cout << "[";
	  Visitor::visit_chord(chord);
	  cout << "]";
     }
     else
	  Visitor::visit_chord(chord);
}

void Print_Visitor::visit_note(Note note)
{
     cout << note;
}
