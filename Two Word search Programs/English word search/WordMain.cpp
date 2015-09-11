/***
* This program is about the use of letters to search for words
* At first,sort all words and build an index of 26 letters. The index contains the times of letter in a word and the ordinal of the word.
* Then search words with the index.
* Date:15.3.7
***/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <fstream>

#include "Vocabulary.h"
#include "Indexs.h"

//function declaration
void print(const Voc& V);
void print(const Indexs& s);

using namespace std;


vector<int> search(string & s,Indexs & let_index); //search function
map<char,int> letter_count(string & s); //letter count function

void main()
{
	ifstream in("1.txt");
	Voc v(in);  //construct a Voc
	cout<<"The total number of words is "<<v.size()<<endl;
	cout<<"Words are: ";
	print(v);
	cout<<endl;
	Indexs letter(v); //construct an Indexs
//	print(letter);

	/*  //use the mumber function to search
	vector<int> result=letter.search('a',1,'n',2); 
	cout<<"The ordinal of search result ";
	for(int i:result)
	{
		cout<<i<<ends;
	}
	cout<<endl;
	*/

	string s="nan";

	vector<int> result2;
	result2=search(s,letter); //search ordinals of letters,appeared in string s, in letter Indexs
	if(result2.size()==0) cout<<"There is no matched word"<<endl;
	else
	{
		cout<<"The result of search: ";
		for(int i:result2)  //print matched words
			cout<<v[i]<<ends;
	}
	system("pause");
}

//search letters of string s in the Index
vector<int> search(string & s,Indexs & let_index)
{
	map<char,int> let_count;
	let_count=letter_count(s);//count letters' times of the string 

	pair<char,int> first_letter=*let_count.begin();
	pair<char,int> second_letter=*(++let_count.begin());
	map<char,int>::iterator third=++let_count.begin();
	third++;

	vector<int> both; //search the first two letters
	both=let_index.search(first_letter.first,first_letter.second,second_letter.first,second_letter.second);
	
	map<char,int>::iterator end=let_count.end();
	for(map<char,int>::iterator  beg=third;beg!=end;++beg) //search the rest letters
	{
		both=let_index.search(both,(*beg).first,(*beg).second);
	}

	return both;
}

//function,letter_count,counts letters' times of the string 
map<char,int> letter_count(string & s)
{

    sort(s.begin(),s.end()); 
	string s_unique=s;
	string::iterator end_unique=unique(s_unique.begin(),s_unique.end()); //unique string s
	s_unique.erase(end_unique,s_unique.end()); //erase extra chars of string
	map<char,int> let_count;

	for(char c:s_unique)
	{
		let_count[c]=count(s.cbegin(),s.cend(),c); //count the times
	}
	return let_count;
}