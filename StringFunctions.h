#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>

namespace StringFunctions
{
     using std::istream;
     using std::string;
     using std::vector;

     /*Difference between tokenize and strsplit:
       - tokenize() creates a split whenever any one of the characters in ch_mask is found
       - strsplit() creates a split whenever the entire string splitter is found
      */
     void tokenize(vector<string>& split_result, const string& to_split, const char* ch_mask = " \t\n");
     void strsplit(vector<string>& split_result, const string& to_split, const string& splitter);

	 int num_occurrences(const string& str, const string& substr);
     string replace(string target, const string& old_text, const string& new_text);

     string upperCase(const string&);
     string lowerCase(const string&);

     //WARNING: peekline() IS NOT PORTABLE TO WINDOWS
     string peekline(istream& sin);

     char* permanent_c_str(string);
}

#endif
