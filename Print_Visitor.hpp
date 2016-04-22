#ifndef PRINT_VISITOR_HPP
#define PRINT_VISITOR_HPP

#include "Visitor.hpp"

class Print_Visitor : public Visitor
{
public:
     Print_Visitor(const Tune& context, bool print_header_) : Visitor(context), print_header(print_header_) {}
     void visit_root(list<Measure> root);
     void visit_measure(Measure measure);
     void visit_chord(Chord chord);
     void visit_note(Note note);

private:
     bool print_header;
};

#endif
