/* aSTbc.y - Yacc grammar file for the ABC music notation language.
 *
 * See the corresponding aSTbc.l file for the specification of the lexemes.
 */

%{
/* put C definitions here that are needed for the actions
 * associated with the grammar rules.
 */

#include "parseresult.hpp"
#include "Voice_Root.hpp"

%}

/* define the tokens returned by the lexer specified in icalc.l */

%token NOTE
%token CHORDBEGIN CHORDEND MEASURESEP
%token ENDVOICE
%token ENDTUNE

/* the grammar "start" symbol */

%start Tune

%%  /* begin grammar rules section */

/* grammar rules have the form

   rule:  alt-1 { alt-1 actions }
        | alt-2 { alt-2 actions }
	| ...  ...
        | alt-n { alt-n actions }
        ;

 $$n vars are POSITIONAL variables that can be used
 in actions to obtain the value associated with the
 result of evaluating a rule. So if a rule is of the form
 
 expr:   expr PLUS term   { $$ = $1 + $3; }

 The rule expr can be thought of as a procedure that
 'invokes the rhs of the rule, which when evaluated
 the action $$ = $1 + $3  is like executing
 return val(expr) + val(term)

 */

/*read entire tune sequence*/
Tune:   TuneSequence ENDTUNE
        ;

/*read all tunes in the sequence*/
TuneSequence:   TuneSequence Voice
              | Voice
              ;

/*read entire voice sequence in tune*/
Voice:  VoiceSequence ENDVOICE
        ;

/*read all voices in voice sequence*/
VoiceSequence:   VoiceSequence MEASURESEP Measure { parseresult[next_index].root.push_back($3.measure); }
| Measure { Voice_Root temp($1.measure); parseresult[next_index] = temp; }
               ;

Measure:  Measure Chord { $$.measure = $1.measure;
                          $$.measure.sequence.push_back($2.chord); }
        | Chord { $$.measure.sequence.push_back($1.chord); }
        ;

Chord:    CHORDBEGIN NoteSet CHORDEND { $$.chord.notes = $2.note_set;
                                        $$.chord.single_element_is_chord = true; }
        | NOTE { $$.chord.notes.push_back($1.note);
	       	 $$.chord.single_element_is_chord = false; }
        ;

NoteSet:  NoteSet NOTE { /*append note to noteset*/ 
                         $$.note_set=$1.note_set;
	  	       	 $$.note_set.push_back($2.note); }
        | NOTE { $$.note_set.push_back($1.note); }
        ;

%% /* end grammar rules */

#include <cstdio>

using std::fprintf;
using std::clearerr;

/* yacc helper functions:
 *
 * yyerror - called by yyparse when a parser error is encountered
 *
 * yywrap - called by yyparse when end-of-file is reached. 
 * It must return a non-zero value to cause yyparse to exit.
 */

int yyerror (char* msg) { fprintf(stderr, "%s\n", msg); }
int yywrap () 		{ fprintf(stderr, "quitting...\n"); return (1); }
extern FILE* yyin;



map<Tune,YYSTYPE> parseresult;
Tune next_index;

#include "commander.hpp"

int main (int argc, char** argv)
{ 
     /* get name of file to parse, open it */
     if(argc!=2)
     {
	  fprintf(stderr, "Invalid command line.\n");
	  return 1;
     }
     yyin = fopen(argv[1],"r");

     /* read and parse ABC music notation file from standard input */
     yyparse();
     
     run_ui();
     
     return 0;
}
