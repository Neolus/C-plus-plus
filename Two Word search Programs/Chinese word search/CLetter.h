// Class CLetter is a letter library of Chinese characters.


#ifndef CLETTER_H
#define CLETTER_H

#include "CSentence.h"
#include <map>
#include <vector>
#include <string>
#include <sstream>

namespace ABC {

class CLetter
{
public:
    std::map<wchar_t,std::map<int,std::vector<int>>> index; //wchar is a Chinese letter. 
					//inner map.key is the ordinal of paragraph, and inner map.value are ordinals of sentences in this parahraph
    //construct with a class CSentence
    CLetter(CSentence &cs);
	//declare member functions
	std::map<int,std::vector<int>> search(wchar_t a,wchar_t b);
	std::map<int,std::vector<int>> search(std::map<int,std::vector<int>> &ab,wchar_t c);

};


void print(const std::map<int,std::vector<int>>& mv);
void print(const std::map<wchar_t,std::map<int,std::vector<int>>> &index);
}
#endif