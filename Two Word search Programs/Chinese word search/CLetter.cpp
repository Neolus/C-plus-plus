//define menber fuctions of CLetter and interface.

#include "CLetter.h"

namespace ABC{

void compare (const std::vector<int> & vec1,const std::vector<int> & vec2,std::vector<int> & Ret);

CLetter::CLetter(CSentence &cs)
{
	{
		std::vector<std::vector<std::wstring>> &clause=cs.Clause;
		int np=clause.size();
		for(int i=0;i!=np;++i) //traverse every paragraph
		{
			wchar_t letter;
			std::vector<std::wstring> & phase=clause[i];

			int sent=phase.size();
			for(int j=0;j!=sent;++j) //traverse every sentence
				{
					std::map<wchar_t,int> times;  //map times stores the times of a letter in one sentence. wchar is a letter. int is the times.
					std::wstring s=phase[j];
					std::wistringstream ss(s); 
					while(ss>>letter)
					{
						if(times.find(letter)==times.end()) //initialize the map times.
						 times[letter]=1;
						else times[letter]++;
						if(times[letter]>1) continue;  //Index of every letter in this sentence is keep once time.
						index[letter][i].push_back(j);
					}
				}
		}
	}
}

//define member functon search, which is used to search two wchars form index
std::map<int,std::vector<int>> CLetter::search(wchar_t a,wchar_t b)
{
	
	std::map<int,std::vector<int>>::iterator a_beg;
	std::map<int,std::vector<int>>::const_iterator a_end,b_beg,b_end;
	a_beg=index[a].begin();
	a_end=index[a].cend();
	b_end=index[b].cend();
	
	std::map<int,std::vector<int>> Ret,&MB=index[b];

	//find same keys in both maps. key is the ordinal of paragraph.
	for(std::map<int,std::vector<int>>::iterator it=a_beg;it!=a_end;++it)
	{
		int para=(*it).first;
		std::map<int,std::vector<int>>::const_iterator res=MB.find(para);
		if(res!=b_end)  //find same values in the same paragraphs. values stand for ordinals of sentence.
		{
			compare(MB[para],(*it).second,Ret[para]); //call compare function
		}
		else continue;
	}

	return Ret;
}

// overload search function, which is used to seach the same sentence of a wchar and a map which stores the index of more than one wchar
std::map<int,std::vector<int>> CLetter::search(std::map<int,std::vector<int>> &ab,wchar_t c)
{
	typedef std::map<int,std::vector<int>>::const_iterator cmap_iterator;
	typedef std::map<int,std::vector<int>>::iterator map_iterator;
	map_iterator c_beg;
	cmap_iterator c_end,ab_end;
	c_beg=index[c].begin();
	c_end=index[c].cend();
	ab_end=ab.cend();

	std::map<int,std::vector<int>> Ret;
	for(map_iterator it=c_beg;it!=c_end;++it)
	{
		int para=(*it).first;   //find same keys in both maps.
		cmap_iterator res=ab.find(para);
		if(res!=ab_end)  //find same values in the same paragraphs.
		{
			compare(ab[para],(*it).second,Ret[para]);
		}
		else continue;
	}
	return Ret;
}

void print(const std::map<int,std::vector<int>>& mv)
{
	for(std::pair<int,std::vector<int>>s:mv)
		{
			std::cout<<"Parahraph"<<std::ends<<s.first<<std::endl;
			std::cout<<"Sentence"<<std::ends;
			for(int j:s.second)
				std::cout<<j<<std::ends;
			std::cout<<std::endl;
		}
}

void print(const std::map<wchar_t,std::map<int,std::vector<int>>> &index)
{
	for(std::pair<wchar_t,std::map<int,std::vector<int>>> wc:index)
	{
		std::wcout<<wc.first<<std::endl;
		print(wc.second);
	}
}

//The function of comparing two vectors, returns the same ordinals which are included in both vectors
void compare (const std::vector<int> & vec1,const std::vector<int> & vec2,std::vector<int> & Ret)
{
	std::vector<int>::const_iterator start,after;
	start=vec2.begin();
	after=vec2.end(); 

	for(int a:vec1) //traverse the whole vector
	{
	std::vector<int>::const_iterator result=find(start,after,a); 
	if(result!=after) //find letter a in vec2
		Ret.push_back(*result);
	}
}

}