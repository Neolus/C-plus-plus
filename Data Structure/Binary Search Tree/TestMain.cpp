//This file contains main function. It is used to test a data structure, binary search tree.


#include "BSTree.h"
#include <iostream>
using namespace std;
void main()
{

	BSTree<int> bt;
	
	int a[8]={25,18,30,11,16,65,33,6};
	for(int i=0;i!=8;++i)
	{
		bt.insert(a[i]);
	}
	cout<<"bt is an int binary search tree, whose initial numbers are 25 18 30 11 16 65 33 and 6"<<endl;
	cout<<"TEST---------------------------------------------------------ON"<<endl;

	cout<<"The smallest number of bt is  "<<bt.findMin()<<endl<<"The largest number of bt is  "<<bt.findMax()<<endl;
	cout<<"Preorder traversal bt: "<<ends;
	bt.pre_print(cout);
	cout<<endl;

	bt.insert(21);
	bt.insert(27);
	bt.remove(65);
	cout<<"After inserting 21 and 27 and removing 65, preorder traversal bt:"<<ends;
	bt.pre_print(cout);
	cout<<endl;

	bt.remove(11);
	BSTree<int> bt1(bt);
	
	cout<<"After remove 11, mimimum and maximum of bt are ";
	cout<<bt.findMin()<<ends<<bt.findMax()<<endl;
	
	cout<<"bt1 is a copy of bt. Preorder traversal bt1: "<<ends;
	bt1.pre_print(cout);

	system("pause");
}


