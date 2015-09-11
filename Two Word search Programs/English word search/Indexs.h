//class Indexs is an index of all letters of words. We can know each letter's frequency of words.


#ifndef INDEXS_H
#define INDEXS_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>


void compare (const std::vector<int> & vec1,const std::vector<int> & vec2,std::vector<int> & Ret);


class Indexs
{
private:
	std::map<char,std::map<int,std::vector<int>>> letter;  //char is a letter, map.key is the frequency of the letter in one word. map.value is the ordinals of word.

public:

	//construct the index with an class Voc
	Indexs(Voc &V)
	{
		std::set<std::string>::iterator beg=V.total.begin();
		std::set<std::string>::iterator end=V.total.end();

		int i=0;
		
		for(std::set<std::string>::iterator it=beg;it!=end;it++)
		{
			std::map<char,int> times;  //map times stores the times of a letter in one word. char is a letter. int is the times.
		
			std::istringstream is(*it);
			char c;
			while (is>>c) //deal with each letter
			{
				if(times.find(c)==times.end()) //initialize the map times.
				times[c]=1;

			    int& j=times[c];
			
				if(letter[c][j].size()==0)  //the frequency j of letter c is zero
					letter[c][j].push_back(i);
				else  
				{   
				std::vector<int>::iterator after=letter[c][j].end();
				std::vector<int>::iterator  back=--after; //iterator of last element
				int last=letter[c][j].back(); //last element
					if(last==i) //the letter appears again in the word.
						{       //shift the ordinal to the corresponding frequency
							letter[c][j].erase(back);
							  ++j;
							letter[c][j].push_back(i);
						}
					else	//the letter appears for the first time.
					{
						letter[c][j].push_back(i);
					}
					
				}
			}
			i++;
		}	
	}

	//member function search, is used to search same ordinals.
    std::vector<int> search(char a,int m,char b,int n);
	std::vector<int> search(const std::vector<int>& ab,char c,int n);
	friend void print(const Indexs& s);
};

//print the Indexs
void print(const Indexs& s)
{
	for(auto let:s.letter)  //let is a pair
	{
		std::cout<<let.first<<std::ends; //char
		for(auto number:let.second)  //the inner map's pair
		{
			std::cout<<number.first<<std::ends;  //frequency

			for(int n:number.second)
				{
					std::cout<<n<<std::ends;  // ordinal
			    }
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}

}

//search function searchs same ordinals of words, in which the frequency of letter a is not less than m and the frequency of letter b isn't less than n. 
std::vector<int> Indexs::search(char a,int m,char b,int n)
{
	std::vector<int> Result;
	int max_m=letter[a].size()+1;
	int max_n=letter[b].size()+1;
	for(int i=m;i!=max_m;++i) // i and j, refer to as  frequencies
	{
		for(int j=n;j!=max_n;++j) 
		{
			compare(letter[a][i],letter[b][j],Result); //call the function compare to get same ordinals of two frequency indexs
		}
	
	}
	return Result;

}

//overload search function. seach same ordinals between the known ordinals and frequncy index of letter c 
std::vector<int> Indexs::search(const std::vector<int>& ab,char c,int n) //the frequncy of letter c isn't less than n 
{
	std::vector<int> Result;
	for(int i=n;i!=letter[c].size();++i)
	{
			compare(letter[c][i],ab,Result);
	}
	return Result;
}





//The function of comparing two vectors, returns the same ordinals which are included in both vectors
void compare (const std::vector<int> & vec1,const std::vector<int> & vec2,std::vector<int> & Ret)
{
	
	std::vector<int>::const_iterator start=vec2.begin();
	std::vector<int>::const_iterator after=vec2.end(); 

	for(int a:vec1) //traverse the whole vector
	{
	std::vector<int>::const_iterator result=find(start,after,a); 
	if(result!=after) //find letter a in vec2
		Ret.push_back(*result);
	}
}
#endif