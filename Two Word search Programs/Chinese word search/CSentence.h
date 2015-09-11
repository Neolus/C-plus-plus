//Class CSentence preserves all sentences of a text.

#ifndef CSENTENCE_H
#define CSENTENCE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::wstring> paragraph(std::wstring text);
std::vector<std::wstring> sentence(const std::vector<std::wstring> &phrase,int i);


class CSentence
{
public:
	std::vector<std::vector<std::wstring>> Clause; //the outer vector stores paragraphs. inner vector stores all sentences of this paragraph

	//construct with an ifstream
	CSentence(std::wifstream & in);
	//construct with a wstring
	CSentence(std::wstring &s);

    //overload operator[],return a paragraph.
	std::vector<std::wstring>& operator[](int i);
	const std::vector<std::wstring>& operator[](int i) const;
};

//function paragraph devides a string into paragraphs 
std::vector<std::wstring> paragraph(std::wstring text);

//function sentence devides a paragraph into sentences 
std::vector<std::wstring> sentence(const std::vector<std::wstring> &phrase,int i);

//print every sentence 
void print( CSentence &cl);

#endif