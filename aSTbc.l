%{    /* aSTbc.l -- lex specification for ABC Notation    08 Nov 08 */

/* Copyright (c) 2008 Patrick Simmons */
/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License (file gpl.text) for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <string>

#include "Key.hpp"
#include "StringFunctions.h"
#include "parseresult.hpp"
#include "aSTbc.h"
#include "Voice_Root.hpp"

using std::toupper;
using std::string;
using std::atoi;
using std::istringstream;

void parseheader();
void parsenote();
void parserest();
void skipline();

//Lex weirdness
%}

/* regular definitions */

ws       [ \t\n]+
digit    [1-9]

/*change {1,2} to * to support unlimited sharping/flatting*/
note     ("^"{1,2}|"_"{1,2}|"=")?[A-Ga-g]("'"*|","*){digit}*("/"{digit}+)?("-")?
rest     [Zz]{digit}*("/"{digit}+)?

%%

{ws}      { /* no action and no return */ }
{note}    { parsenote(); return NOTE; }
{rest}    { parserest(); return NOTE; }
"["       { return CHORDBEGIN; }
"]"       { return CHORDEND; }
"|"       { return MEASURESEP; }
"|]"      { return ENDVOICE; } /*parser uses this to set parseresult[next_index]*/
"%aSTbc END SENTINEL" { return ENDTUNE; }
"%"       { skipline(); }
[A-Z]:    { parseheader(); }

%%

/* Note that lex always returns two values:
   1. "What is it?": a small integer such as NUMBER that indicates the
      kind of item that was found; this is the return() value.
   2. The value itself.  This is yylval, which points to a TOKEN.
*/

/* Skip to start of next line */
void skipline()
{
  char c;
  while ((c = yyinput()) != '\n' && c!='\0')
    ;
}

void parsenote()
{
  //Initialize yylval to "blank" for parsing
  yylval.note = Note();

  //Deal with tied notes
  int yyleng = ::yyleng;
  if(yytext[yyleng-1]=='-')
  {
    yylval.note.tied = true;
    yyleng--;
  }

  string ntext = yytext;
  ntext.resize(yyleng);
  int nbound = ntext.find_first_of("123456789")!=string::npos ? ntext.find_first_of("123456789") : yyleng;

  yylval.note.sharp_count = yylval.note.flat_count =
  yylval.note.octave = yylval.note.naturalized = 0;
  for(int i=0; i<nbound; i++)
    switch(ntext[i])
    {
      case '^': yylval.note.sharp_count++; break;
      case '_': yylval.note.flat_count++; break;
      case '=': yylval.note.naturalized = true; break;
      case '\'': yylval.note.octave++; break;
      case ',': yylval.note.octave--; break;
      case '/': yylval.note.beats = Rational(1,atoi(ntext.substr(i+1,ntext.find_last_of("123456789") - i).c_str()));
        i=ntext.find_last_of("123456789");
	nbound = yyleng;
	break;
      default: char ch = yytext[i];
        if(ch > 'Z')
        {
          yylval.note.octave++;
          ch=toupper(ch);
        }

        /*Executive Decisions:
          We're going to ignore the question of what Octave 0 is.
          According to the ABC Standard, it's middle C,
          but no one seems to follow that for the Bass Clef.
          It's possible to derive the clef from the parseresult
          context, so individual transformations can make their
          own judgments on where to put Octave 0.

          Similarly, we're not going to represent sharps or flats
          given by the key, because it might complicate some
          transformations and can be manually added by a helper
          transformation pass later on very easily.
        */

        //Enumerated scale: CDEFGAB
        yylval.note.tone = static_cast<Tone>(ch - 'C');
        if(yylval.note.tone < 0)
          yylval.note.tone = static_cast<Tone>(yylval.note.tone + 7);
    }

  //Use Pygmalitype Rational class for beat information
  if(nbound < yyleng)
  {
    int fracbound = ntext.find_first_of("/")!=string::npos ? ntext.find_first_of("/") : yyleng;
    yylval.note.beats = Rational(atoi(ntext.substr(nbound,fracbound-nbound).c_str()),
                                 fracbound==yyleng ? 1 : atoi(ntext.substr(fracbound+1,yyleng-(fracbound+1)).c_str()));
  }

  //Store note's context with it
  yylval.note.context = next_index;
}

void parserest()
{
  yylval.note = Note();
  yylval.note.tone = TONE_REST;
  string ntext = yytext;

  //Use Pygmalitype Rational class for beat information
  if(1 < yyleng)
  {
    int fracbound = ntext.find_first_of("/")!=string::npos ? ntext.find_first_of("/") : yyleng;
    yylval.note.beats = Rational(atoi(ntext.substr(1,fracbound-1).c_str()),
                                 fracbound==yyleng ? 1 : atoi(ntext.substr(fracbound+1,yyleng-(fracbound+1)).c_str()));
  }

  //Store note's context with it
  yylval.note.context = next_index;
}

void parseheader()
{
  char ch;
  string rest_of_line, modestr;

  /*Skip leading whitespace*/
  while((ch = yyinput())==' ');

  /*Make string & stringstream from header arguments*/
  rest_of_line=ch;
  while((ch = yyinput())!='%' && ch!='\n')
    rest_of_line+=ch;
  unput(ch);
  istringstream sin(rest_of_line);

  /*Switch: Deal with relevant headers*/
  switch(yytext[0])
  {
    case 'X': next_index.X = rest_of_line; break;
    case 'V': next_index.V = rest_of_line; break;
    case 'Q': next_index.Q = rest_of_line; break;
    case 'T': next_index.T = rest_of_line; break;
    case 'A': next_index.A = rest_of_line; break;
    case 'L': sin >> next_index.L_value; break;
    case 'M': sin >> next_index.meter; break;
    case 'K': /*I love you, Mom.*/
      next_index.K = rest_of_line;

      /*FSM: Tone -> Semitone -> Mode*/
      int fsm_state = 0;

      Tone tone;
      Key::Semitone semitone = Key::NATURAL;
      Key::Mode mode = Key::IONIAN;
      for(int i=0; i<rest_of_line.size(); i++)
      {
        if(rest_of_line[i]==' ') continue;
        switch(fsm_state)
        {
          case 0: /*Tone state*/
            tone = static_cast<Tone>(rest_of_line[i] - 'C');
            if(tone < 0) tone = static_cast<Tone>(tone + 7);
            fsm_state++;
            break;
          case 1: /*Semitone state*/
            if(rest_of_line[i]=='#' || rest_of_line[i]=='b')
            {
              semitone = rest_of_line[i]=='#' ? Key::SHARP : Key::FLAT;
              break;
            }
            else
              fsm_state++;
            /*fall through*/
          case 2: /*Mode state*/
            if(i+2 >= rest_of_line.size())
            {
              yyerror("Syntax error in reading key.\n");
              break;
            }

            modestr = StringFunctions::upperCase(rest_of_line.substr(i,3));
            while(mode_tbl[mode]!=modestr)
              mode = static_cast<Key::Mode>(mode + 1);
            if(mode > Key::LOCRIAN) mode = static_cast<Key::Mode>(mode - 7); /*deal with MAJ/MIN == ION/AEO*/
            fsm_state++;
            i=rest_of_line.size()-1;
            break;
          default:
            yyerror("Syntax error in reading key.\n");
            break;
        }
      }

      next_index.key = Key(tone,semitone,mode);
      break;
  }
}

int yywrap() {  return(1);  }       /* lex may need this. */
