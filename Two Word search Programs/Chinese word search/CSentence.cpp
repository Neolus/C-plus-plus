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
				unsigned int pos=text.find('\n'); //�Ի���Ϊ�ֶα�־
				if(pos==std::wstring::npos) //���ַ�����û���ҵ�����
					{
						phrase.push_back(text); //�����ַ���Ϊһ��
						break;
					 }
				else if(pos==text.size()) //����ҵ��Ļ����������ַ�����ĩβ
					{
						phrase.push_back(text);
					}
			//	����հ׶��䣬������뱣���հ׶����������
				else if(pos==0) //������з��ڿ�ͷ����������հ׶���
					{
		
						pos=text.find_first_not_of('\n');
						std::wstring s(text,pos);
						text=s;
					}
				
				else  //���ַ������ҵ�����
						{
						  std::wstring ph(text,0,pos); //���滻��ǰ�������ַ�
						  std::wstring  s(text,pos+1); //ȥ����֪���䣬ǰ��Ĳ���
						  text=s;
						  phrase.push_back(ph); //���䱣����std::vector
						 }
     		}

		return phrase;
	}

//function sentence devides a paragraph into sentences 
std::vector<std::wstring> sentence(const std::vector<std::wstring> &phrase,int i)
	{
		std::wstring stop,para;
	    stop=L"������"; //These signs are used at the end of every sentence
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