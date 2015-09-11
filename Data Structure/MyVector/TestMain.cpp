// This file contains the main function which is used to test the data structure myVector.

#include "myVector.h"
#include <iostream>


using namespace std;
void main()
{
	myVector<int> mv;

	cout<<"Default capacity is "<<mv.capacity()<<endl<<"size of mv is "<<mv.size()<<endl;
	for(int i=0;i!=18;++i)
		mv.push_back(i);

	cout<<"All elements of mv are ";
	for(int i=0;i!=18;++i)
	{
		cout<<mv[i]<<ends;
	
	}
	cout<<endl;
	mv.pop_back();
	cout<<"pop the last elemnt of mv, and print this element:"<<ends;
	cout<<mv[17]<<endl; //It is illegal to print the popped elemen. However, this print is successful. The memory isn't deleted.
	myVector<int> copymv=mv;
	cout<<"All elements of vector copymv, a copy of mv."<<ends;
	for(int i=0;i!=copymv.size();++i)
	{
		cout<<copymv[i]<<ends;
	
	}
	system("pause");

}
