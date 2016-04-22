#include "StringFunctions.h"
#include <cctype>
#include <cstring>

namespace StringFunctions
{
     using std::toupper;
     using std::tolower;
     using std::strcpy;
     using std::streampos;

     void tokenize(vector<string>& split_result, const string& to_split, const char* ch_mask)
     {
	  int index = 0;
	  int new_index;
	  while((new_index = to_split.find_first_of(ch_mask,index)) != string::npos)
	  {
	       if(new_index == index)
	       {
		    index++;
		    continue;
	       }

	       split_result.push_back(to_split.substr(index,new_index - index));
	       index = new_index + 1;
	  }

	  if(index < to_split.size())
	       split_result.push_back(to_split.substr(index,to_split.size()));
     }

     void strsplit(vector<string>& split_result, const string& to_split, const string& splitter)
	 {
		  int index = 0;
		  int new_index;
		  while((new_index = to_split.find(splitter,index)) != string::npos)
		  {
			   if(new_index == index)
			   {
					index+=splitter.size();
					continue;
			   }

			   split_result.push_back(to_split.substr(index,new_index - index));
			   index = new_index + splitter.size();
		  }

		  if(index < to_split.size())
			   split_result.push_back(to_split.substr(index,to_split.size()));
	 }

	 int num_occurrences(const string& str, const string& substr)
	 {
		  int to_return = 0;		  
		  int position = 0;
		  
		  while((position = str.find(substr,position))!=string::npos)
		  {
			   to_return++;
			   position+=substr.length();
		  }

		  return to_return;
     }

     string replace(string target, const string& old_text, const string& new_text)
     {
    	 int position = 0;
    	 while((position = target.find(old_text,position))!=string::npos)
    	 {
    		 target.replace(position,old_text.length(),new_text);
    		 position+=new_text.length();
    	 }

    	 return target;
     }

     string upperCase(const string& casey)
     {
	  string upperCasey=casey;
	  for(int i=0; i<casey.length(); i++)
	       upperCasey[i]=toupper(casey[i]);
	  return upperCasey;
     }

     string lowerCase(const string& casey)
     {
	  string lowerCasey=casey;
	  for(int i=0; i<casey.length(); i++)
	       lowerCasey[i]=tolower(casey[i]);
	  return lowerCasey;
     }

     string peekline(istream& sin)
     {
          streampos sp = sin.tellg();
          string to_return;
          getline(sin, to_return);
          sin.seekg(sp);
          return to_return;
     }

     char* permanent_c_str(string transformer)
     {
		  char* to_return = new char[transformer.size()+1];
	  strcpy(to_return,transformer.c_str());
	  return to_return;
     }
}
