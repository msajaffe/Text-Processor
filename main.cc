#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "textprocess.h"
#include "echo.h"
#include "decorator.h"
int main () {
  string s;

  while(1) {
    getline(cin,s); //gets the first line of input and puts it into s
    if (cin.fail()) break;
    istringstream iss(s); //make s into a ss
    string fname;	
    iss >> fname; //get first word in input (file name or stdin)
    istream *in = (fname == "stdin") ? &cin : new ifstream(fname.c_str()); //set the istream to cin or file
	
    TextProcessor *tp = new Echo;	
	
	string dec;
    while (iss >> dec) {	//get the next word in the line
      if (dec == "dropfirst") {	
        int n;
        iss >> n;
		tp = new DropFirst(n, tp);	//decorates the tp with dropfirst
	  }
      else if (dec == "doublewords") {
        tp = new DoubleWords(tp);	//decorates the tp with doublewords
      }
      else if (dec == "allcaps") {
        tp = new AllCaps(tp);		//decorates the tp with allcaps
      }
      else if (dec == "count") {
        char c;
        iss >> c;
        tp = new Count(c, tp);		//decorates the tp with count c
      }
   } 

   tp->setSource(in);
   string word;

   while (word = tp->getWord(), !tp->fail()) {
     cout << word << endl;
   }

   if (in != &cin) delete in;

   delete tp;
  }
}
