//This file contains the main function. It is used to test the data structure Queue.


#include <iostream>
#include "myQueue.h"
using namespace std;

void main()
{
	myQueue<int> Q1,Q2;
	int t=9;
	//Push three int to Q1
	Q1.push(t);
	Q1.push(t+3);
	Q1.push(t+4);

	cout<<"The size of Q1 is "<<Q1.size()<<endl;

	int k=Q1.front(); //get the index of front element
	cout<<"All elements of Q1 are "<<ends;
	for(int i=0;i!=Q1.size();++i)
	{
		cout<<Q1[k]<<ends;
		k=Q1.next(k); //move index
	}
	cout<<endl;
	Q1.clear(); //clear Q1
	
	Q1.push(999);
	Q1.push(998);
	k=Q1.front();
	cout<<"The size of Q1  "<<Q1.size()<<endl<<"The front index of Q1 "<<k<<endl<<"All elements of Q1 "<<ends;
	
	for(int i=0;i!=Q1.size();++i)
	{
		cout<<Q1[k]<<ends;
		k=Q1.next(k);
	}
	cout<<endl;

	myQueue<int> Q3;
	for(int i=0;i!=16;++i)
		Q3.push(i);
	cout<<"Test the moving of front index after each pop "<<ends;
	for(int i=0;i!=15;++i)
	{
		Q3.pop();
	   int s=Q3.front();
		cout<<s<<ends;
	
	}
	cout<<endl;
	Q3.pop();//pop to the end of the array
	Q3.push(56); //56 should be stored at the begin of array
	int j=Q3.front();  
	cout<<"Test the circular array in Q3, 56 are stored at the begin of array: "<<endl<<"The front index of Q3 is "<<j<<endl<<"All elements of Q3 are ";
	for(int i=0;i!=Q3.size();++i)
	{
		cout<<Q3[j]<<endl;
	}
	cout<<"The back index of Q3 is "<<Q3.back()<<endl;

	system("pause");
}

