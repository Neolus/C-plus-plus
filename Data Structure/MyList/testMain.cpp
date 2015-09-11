// This file contains the main function which is used to test the data structure myList.
#include "myList.h"
#include <iostream>
using namespace std;


template <typename object> myList<object>  intersect(const myList<object> &f,const myList<object> &s); //A function gets the same elements in two increasing lists.

void main()
{
	myList<int> f,f2;
	int i=2;
	f.push_back(i);

	for(int i=1;i!=5;++i)
		f.push_back(i);
	myList<int>fn(f);
	f2=f;

	typedef  myList<int>::iterator iterator_l;
	typedef  myList<int>::const_iterator const_iterator_l;
//	using iterator_l=myList<int>::iterator;  C++ 11 new feature, Some compilers don't support, for example VS2012. 
//	using const_iterator_l=myList<int>::const_iterator;
	cout<<"original list f"<<endl;
	for(iterator_l itr=f.begin();itr!=f.end();++itr)
		cout<<*itr<<ends;
	cout<<endl<<"original list in testing range loop."<<endl;
	for(int c:f) //test range loop
		cout<<c<<ends;

	fn.pop_front();
	f2.erase(--f2.end());
	f2.insert(++f2.begin(),9);
	cout<<endl<<"pop the front element of fn, a copy construction List of f."<<endl;
	for(iterator_l itr=fn.begin();itr!=fn.end();++itr)
		cout<<*itr<<ends;
	cout<<endl<<"erase the back element of f2, a copy of List f, and insert 9 at the second order."<<endl;
	for(iterator_l itr=f2.begin();itr!=f2.end();++itr)
		cout<<*itr<<ends;
	cout<<endl;
	f2.clear(); 
	cout<<"test f2.clear function and print all elements of f2. There should be nothing."<<endl;
	for(iterator_l itr=f2.begin();itr!=f2.end();++itr)
		cout<<*itr<<ends;


	myList<int> lis1,lis2;  //constructing two increasing lists.
	for(int i=2;i!=10;++i)
	{
		lis1.push_back(i);
	}
	for(int i=2;i<=10;)
	{
		lis2.push_back(i);
		i=i+2;
	}
	myList<int> lis3=intersect(lis1,lis2); //call function to get the intersection
	cout<<"The intersection of lis1 and lis2"<<endl;
	for(int c:lis3)
	{
		cout<<c<<ends;
	}

	system("pause");
}


template <typename object>  //template function, types must be comparable.
myList<object> intersect(const myList<object> &f,const myList<object> &s) //return the insection of two increasing lists,f and s.
		{

			myList<object> retVal;
			myList<object>::const_iterator itr2=s.begin();
			for(myList<object>::const_iterator itr1=f.begin();itr1!=f.end();)
			{
				if(*itr1==*itr2) //find the same element.
				{
					retVal.push_back(*itr1);
					++itr1; //move two iterators to next nodes.
					++itr2;
	                if(itr2==s.end()) 
						break;
				}
				else if(*itr1<*itr2) //The element of f is small.
				{
					++itr1;

				}
				else    //The element of s is small.
					{
						++itr2;
						if(itr2==s.end())
						break;
				    }
			}
			return retVal;
		}