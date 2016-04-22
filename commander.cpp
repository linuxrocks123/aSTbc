#include <iostream>
#include <cstdlib>
#include <vector>

using std::atoi;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::vector;

#include "commander.hpp"
#include "parseresult.hpp"
#include "StringFunctions.h"
#include "Voice_Root.hpp"

void run_ui()
{
     while(true)
     {
	  string x;
	  cout << "/ ";
	  getline(cin,x);
	  if(x=="print")
	  {
	       int n = 0;
	       for(map<Tune,YYSTYPE>::iterator i = parseresult.begin(); i!=parseresult.end(); i++,n++)
		    cout << n << ": " << "X: " << i->first.X << " V: " << i->first.V << endl;
	  }
	  else
	  {
	       vector<string> tokens;
	       StringFunctions::tokenize(tokens,x);
	       map<Tune,YYSTYPE>::iterator active_voice = parseresult.begin();
	       for(int i=atoi(tokens[0].c_str()); i>0; i--) active_voice++;

	       if(false)
	       {
	       }
	       else if(tokens[0]=="quit")
	       {
		    for(map<Tune,YYSTYPE>::iterator i = parseresult.begin(); i!=parseresult.end(); i++)
		    {
			 Print_Visitor current_voice_printer(i->first,i==parseresult.begin());
			 current_voice_printer.visit(i->second);
		    }

		    break;
	       }
	       else
		    cerr << "aSTbc: invalid command given to transformation launcher!\n";
	  }
     }
}
