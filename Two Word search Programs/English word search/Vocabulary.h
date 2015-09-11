//class Voc is a dictionary,based on a txt;

#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>


class Voc
{
private:
	int number;  //the total number of Vocubulary
	std::set<std::string> total; //all words
	std::vector<std::string> dictionary; // store all words in an vector

public:

//construct with an fstream
	Voc(std::ifstream & text)
	{
	  std::string word;
	  while(!text.eof()) //deal all words of txt
	  {
		  text>>word;
		  word[0]=tolower(word[0]);  //translate the upercase letter to lowercase letter
		  total.insert(word);
	  }
	  number=total.size();


	  for(std::set<std::string>::iterator it=total.begin();it!=total.end();++it)
	  {
		  dictionary.push_back(*it);
	  }
	}

	//member function, return the size.
	int size()
	{
		return number;
	}

	//overload operator []. return an word of the ordinal i
	std::string operator[](int i)
	{
		return dictionary[i];

	}

	//overload operator []. const edition
	const std::string operator[](int i) const
	{
		
		return  dictionary[i];

	}

    friend void print(const Voc& V);
	friend class Indexs;
};


//print 
void print(const Voc& V)
{
	std::set<std::string>::iterator beg=V.total.begin();
	std::set<std::string>::iterator end=V.total.end();
	for(std::set<std::string>::iterator it=beg;it!=end;it++)
	{
		std::cout<<*it<<std::ends;
	}
}

#endif