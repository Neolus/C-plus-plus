/*This file contains the main function. 15.4.15
** Use wchar_t to deal  Chinese letters. 
** At first, segment the txt to paragraphs. Then segment the paragraphs into sentence. Build an index of letters.
** At last, search words in the index and return the ordinal of paragraph and sentence. 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CSentence.h"
#include "CLetter.h"

void print(CSentence &cl);
using namespace ABC; //A local namespace is defined by me. Class CSentence and class CLetter are included.
using namespace std;
map<int,vector<int>>  search(wstring & ws,CLetter &letter,const CSentence &cs,bool precise=false);


void main()
{
	wcout.imbue(std::locale("chs"));
	wifstream in("Chinese.txt");  //read from a txt
	in.imbue(std::locale("chs"));
	CSentence cs(in);
	CLetter cl(cs);

	wchar_t A(L'中');
	wchar_t B(L'国');
	wstring ws=L"中国o";

	auto res=search(ws,cl,cs);
	print(res);
	

	system("pause");

}

//define function search. search a string in a class CLetter's index. class CSentence contains all sentences
map<int,vector<int>>  search(wstring & ws,CLetter &letter,const CSentence &cs,bool precise) // if(precise==true) march string precisely in an sentence, else chars may appeare discontinuously.
{
	map<int,vector<int>> result; 
	size_t sz=ws.size();
	if(sz==1) result=letter.index[ws[0]]; //only one letter 
	else if(sz==2) result=letter.search(ws[0],ws[1]); //two lettters
	else  //more than 2 letters
	{
		result=letter.search(ws[0],ws[1]);
		for(int i=2;i!=sz;++i)
		{
			result=letter.search(result,ws[i]); //filter possible sentences
		}
	}

	if(precise==false)
	return result;
	else  //precisely march
	{
		map<int,vector<int>> preturn;
		for(std::pair<int,std::vector<int>>s:result)
		{
			for(int j:s.second)
			{
				size_t pos=(cs.Clause[s.first][j]).find(ws); //search the wstring in all possible sentences
				if(pos!=wstring::npos)
					preturn[s.first].push_back(j); 

			}

		}
		return preturn;
	}
}


