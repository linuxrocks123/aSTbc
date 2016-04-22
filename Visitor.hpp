#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "parseresult.hpp"

#include "Measure.hpp"

#include <list>
using std::list;

class Visitor
{
public:
     Visitor(const Tune& context_) : context(context_) {}
     void visit(YYSTYPE to_visit);

protected:
     /*Visitor functions (overridable)*/
     virtual void visit_root(list<Measure> root);
     virtual void visit_measure(Measure measure);
     virtual void visit_chord(Chord chord);
     virtual void visit_note(Note note) = 0;

     Tune context;
};

#endif
