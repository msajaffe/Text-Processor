#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include "echo.h"
#include "textprocess.h"
#include <string>
class DropFirst: public TextProcessor {
    std::istream *source;		//source of input
	TextProcessor * component;	//textprocessor to be decorated
    bool failed;				//will show failed if extracting input has failed
	int n;						//number of stuff to drop
 public:	//explained in implementation
    DropFirst(int n, TextProcessor * component);
	void setSource(std::istream *);
    std::string getWord();
	bool fail() const;
};

class DoubleWords: public TextProcessor{	//same stuff
    std::istream *source;
    TextProcessor * component;
	bool failed;
	int doubled;
	std::string previousWord;
 public:
    DoubleWords(TextProcessor *);
    void setSource(std::istream *inp);
    std::string getWord();
    bool fail() const;
};

class AllCaps: public TextProcessor{
    std::istream *source;
    TextProcessor * component;
	bool failed;
 public:
    AllCaps(TextProcessor *);
    void setSource(std::istream *inp);
    std::string getWord();
    bool fail() const;
};

class Count: public TextProcessor{
    std::istream *source;
    TextProcessor * component;
	bool failed;
	char c;
	int counter;
 public:
    Count(char, TextProcessor *);
    void setSource(std::istream *inp);
    std::string getWord();
    bool fail() const;
};
#endif