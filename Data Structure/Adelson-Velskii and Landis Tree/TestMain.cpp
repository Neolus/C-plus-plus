/**
* This file contains Main function. It is used to test AVL Tree.
**/


#include "AVLTree.h"
#include <iostream>
using namespace std;

void main()
{
	AVLTree<int> AVLT;
	int a[8]={4,2,6,1,3,5,7,16};
	for(int i=0;i!=8;++i)
	{
		AVLT.insert(a[i]);
	}
	cout<<"The initianl state of a balanced AVLTree AVLT in preorder traversal:"<<ends;
	AVLT.pre_print(cout);
	cout<<endl<<"TEST-----------------Insert functon------------------------ON"<<endl<<"After inserting 15, preorder traversal:"<<ends;
	AVLT.insert(15);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 14, preorder traversal:"<<ends;
	AVLT.insert(14);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 13, preorder traversal:"<<ends;
	AVLT.insert(13);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 12, preorder traversal:"<<ends;
	AVLT.insert(12);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 11, preorder traversal:"<<ends;
	AVLT.insert(11);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 10 and 8, preorder traversal:"<<ends;
	AVLT.insert(10);
	AVLT.insert(8);
	AVLT.pre_print(cout);
	cout<<endl<<"After inserting 9, preorder traversal:"<<ends;
	AVLT.insert(9);
	AVLT.pre_print(cout);
	cout<<endl<<"TEST-----------------Remove functon------------------------ON"<<endl<<"After removing 11, preorder traversal:"<<ends;
	AVLT.remove(11);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 8, preorder traversal:"<<ends;
	AVLT.remove(8);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 5, preorder traversal:"<<ends;
	AVLT.remove(5);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 3, preorder traversal:"<<ends;
	AVLT.remove(3);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 6, preorder traversal:"<<ends;
	AVLT.remove(6);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 13, preorder traversal:"<<ends;
	AVLT.remove(13);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 12, preorder traversal:"<<ends;
	AVLT.remove(12);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 15, preorder traversal:"<<ends;
	AVLT.remove(15);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 16, preorder traversal:"<<ends;
	AVLT.remove(16);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 1, preorder traversal:"<<ends;
	AVLT.remove(1);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 2, preorder traversal:"<<ends;
	AVLT.remove(2);
	AVLT.pre_print(cout);
	cout<<endl<<"After removing 4, preorder traversal:"<<ends;
	AVLT.remove(4);
	AVLT.pre_print(cout);
	cout<<endl<<"TEST------------Copy constructor, Copy-assignment, and Clear function-----------------ON"<<endl;
	cout<<"copyTree is a copy construction of AVLT. preorder traversal of copyTree:"<<ends;

	AVLTree<int> copyTree(AVLT);
	copyTree.pre_print(cout);
	cout<<endl<<"After inserting 8 and 13 into AVLT. Copy AVLT to copyTree:"<<ends;
	AVLT.insert(8);
	AVLT.insert(13);
	copyTree=AVLT;
	cout<<"Preorder traversal of copyTree:"<<ends; 
	copyTree.pre_print(cout);
	cout<<endl<<"Execute clear function of copyTree, there will be nothing when call pre_print function"<<endl;
	copyTree.clear();
	cout<<"Preorder traversal of copyTree, a void AVLTree:"<<ends;
	copyTree.pre_print(cout);
	cout<<endl;

	system("pause");
}