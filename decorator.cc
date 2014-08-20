#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include "decorator.h"
#include "echo.h"
using namespace std;

DropFirst::DropFirst(int n, TextProcessor * component): component(component), n(n), source(0){} //initialize tp,and n
std::string DropFirst::getWord(){
	string s;		
	s = component->getWord();		//get the previous component's word from the stream
	failed = component->fail();		
	if(failed) return s;
	if (s.length() <= n) return getWord();	//if the length is smaller than n, then get the next word
	else s = s.substr(n);	//if its greater than n, then get the parts after n
	return s;
}
void DropFirst::setSource(istream * in) {	
	source = in;				//set the component's and this' source to whatever is given
	component->setSource(in);	
}
bool DropFirst::fail() const { return failed; }


DoubleWords::DoubleWords(TextProcessor * comp): component(comp), source(0), doubled(1){}	//same idea...
void DoubleWords::setSource(istream * in) {	
	source = in;
	component->setSource(in);
}
string DoubleWords::getWord() {
	string s;
	if((doubled % 2)==0){		//every other time this function is called, it goes into this conditional
		s = previousWord;		//sets s to the previousword
	} else {
		s = component->getWord();	//set s to a new word
		failed = component->fail();
		previousWord = s;			//initialize the soon to be previous word
	}
	doubled++;
	return s;
}
bool DoubleWords::fail() const { return failed; }

AllCaps::AllCaps(TextProcessor * comp): component(comp), source(0){}	//same idea..
void AllCaps::setSource(istream * in) {	
	source = in;
	component->setSource(in);
}
char toCap(char c){
	return (c>=97 && c<=122) ? (c - 32): c;	//check if its lowercase, if it is then convert to upper
}
string AllCaps::getWord() {
	string s;
	s = component->getWord();
	failed = component->fail();
	char * cstr = new char [s.length()+1];	//make an array of chars
	strcpy(cstr, s.c_str());				//get each char in provided word
	for (int i = 0; i <= s.length(); i++){
		cstr[i] = toCap(cstr[i]);			//and capitalize them
	}
	s = cstr;	//set s to the updated array of characters
	delete [] cstr;	
	return s;
}
bool AllCaps::fail() const { return failed; }


Count::Count(char c, TextProcessor * comp): component(comp), c(c), source(0), counter(0){}	//same idea..
void Count::setSource(istream * in) {	
	source = in;
	component->setSource(in);
}
int getDigits(int digits, int acc){
	return (digits<=0) ? acc: getDigits(digits/10, ++acc);
}
string Count::getWord() {
	string s, sc;
	sc = c;
	s = component->getWord();
	failed = component->fail();
	int last = s.find(sc);	//get the first(aptly named) position of the required character in the first word
	if(last != -1){			//if it exists..
		counter++;			//increase the number of characters found
		stringstream ss;
		ss << counter;	
		s.replace(last, 1, ss.str()); //replace it with the number of characters found
	}
	while(s.find(sc) != -1 && (last+1) < s.length()) { //if there is no more to find, or reach the end of file, then stop loop
		counter++;
		stringstream ss;
		ss << counter; 
		last = s.find(sc,last+1);		//this is the position of the last one found + 1
		s.replace(last, 1, ss.str());	//use the last's position to look for anything beyond that
	}
	return s;
}

bool Count::fail() const { return failed; }
