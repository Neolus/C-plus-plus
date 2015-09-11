// define menber functions of class CStence and interface
#include "CSentence.h"

//construct with an ifstream
CSentence::CSentence(std::wifstream & in)
{
		std::wstring text;
		
		while(!in.eof()) //deal all words of txt
		  {
			  wchar_t c=in.get();
			  text+=c;
		  }

		std::vector<std::wstring>phrase=paragraph(text);
		int np=phrase.size();

		for(int i=0;i!=np;++i)
		{
			Clause.push_back(sentence(phrase,i));
		}

}
//construct with a wstring
CSentence::CSentence(std::wstring &s)
{
		std::vector<std::wstring>phrase=paragraph(s);
		int np=phrase.size();

		for(int i=0;i!=np;++i)
		{
			Clause.push_back(sentence(phrase,i));
		}
}

//overload operator[]
std::vector<std::wstring>& CSentence::operator[](int i)
{
	return Clause[i];
}
//overload operator[] const edition
const std::vector<std::wstring>& CSentence::operator[](int i) const
{
	return Clause[i];
}

//function paragraph devides a string into paragraphs 
std::vector<std::wstring> paragraph(std::wstring text)
	{
		
		std::vector<std::wstring> phrase;

			while(text.size()!=0)  
			{ 
				unsigned int pos=text.find('\n'); //以换行为分段标志
				if(pos==std::wstring::npos) //在字符串中没有找到换行
					{
						phrase.push_back(text); //整个字符串为一段
						break;
					 }
				else if(pos==text.size()) //如果找到的换行在整个字符串的末尾
					{
						phrase.push_back(text);
					}
			//	处理空白段落，如果不想保留空白段落就添加这段
				else if(pos==0) //如果换行符在开头，用来处理空白段落
					{
		
						pos=text.find_first_not_of('\n');
						std::wstring s(text,pos);
						text=s;
					}
				
				else  //在字符串中找到换行
						{
						  std::wstring ph(text,0,pos); //保存换行前面所有字符
						  std::wstring  s(text,pos+1); //去除已知段落，前面的部分
						  text=s;
						  phrase.push_back(ph); //段落保存入std::vector
						 }
     		}

		return phrase;
	}

//function sentence devides a paragraph into sentences 
std::vector<std::wstring> sentence(const std::vector<std::wstring> &phrase,int i)
	{
		std::wstring stop,para;
	    stop=L"。！？"; //These signs are used at the end of every sentence
		para=phrase[i];

		std::vector<std::wstring> Ret;
		while(para.size()!=0)
		{
			unsigned pos=para.find_first_of(stop);
			if(pos==std::wstring::npos)
			{
				Ret.push_back(para);
				break;
			}
			else
			{
				std::wstring temp(para,0,pos+1);
				Ret.push_back(temp);
				para=para.substr(pos+1);
			}
		}
		return Ret;
	}

//print every sentence 
void print( CSentence &cl)
{
	std::vector<std::vector<std::wstring>>::iterator beg,end;
	beg=cl.Clause.begin();
	end=cl.Clause.end();

	for(std::vector<std::vector<std::wstring>>::iterator phrase=beg;phrase!=end;++phrase)
	{
		std::vector<std::wstring>::iterator sen_beg,sen_end;
		sen_beg=phrase->begin();
		sen_end=phrase->end();
		
		for(std::vector<std::wstring>::iterator sentence=sen_beg;sentence!=sen_end;++sentence)
		{
			std::wcout<<*sentence<<std::endl;
		}
		std::wcout<<std::endl;
	}
}