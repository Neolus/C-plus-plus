//This file contains Main Function. It is used to test HashTable.


#include "HashTable.h"
#include <iostream>
using namespace std;
bool isPrime(int n);
void Prime(int n,bool *p);
int nextPrime(int n);
void main()
{
	
	HashTable<int> HT(10),HT3(25);
	HT.insert(102);
	HT.insert(203);
	HT.insert(987);
	HT.insert(86);
	cout<<"HT, a hash table, contains 102, 203, 987 and 86"<<endl;
	cout<<"TEST------- Copy Constructor and Operator = ------------------ON"<<endl;
	HashTable<int> HT2(HT);
	HT3=HT;
	cout<<"HT2 is a copy construction of HT. "<<ends<<"HT3 is a copy of HT. "<<endl;
	cout<<"Element munber and table size of HT  are "<<HT.elementSize()<<" and "<<HT.tableSize()<<endl;
	cout<<"Element munber and table size of HT2 are "<<HT2.elementSize()<<" and "<<HT2.tableSize()<<endl;
	cout<<"Element munber and table size of HT3 are "<<HT3.elementSize()<<" and "<<HT3.tableSize()<<endl;
	cout<<"TEST------------- Member Functions ----------------------------ON"<<endl;	
	cout<<"Does HT contains 87?"<< boolalpha<<ends<<HT.contains(86)<<endl;
	HT.insert(87);
	HT.remove(86);
	cout<<"After inseting 87 and removing 86, element number of HT is "<<HT.elementSize()<<endl;
	HT.insert(87);//Inserting 87 once again will fail for HT has contained 87.
	cout<<"After inseting 87 once again, element number of HT is "<<HT.elementSize()<<endl;

	HT.clear();
	cout<<"After clearing HT, element number of HT is "<<HT.elementSize()<<ends<<HT.tableSize()<<endl;
	HT.insert(4);
	for(int i=0;i!=20;++i) //Rehash will be executed two times
		{
			HT.insert(i);
    	}
	cout<<"Does HT contains 15?"<< boolalpha<<ends<<HT.contains(15)<<endl;
	cout<<"After rehashing two times, element munber and table size of HT  are "<<HT.elementSize()<<" and "<<HT.tableSize()<<endl;
	system("pause");


	system("pause");



}


