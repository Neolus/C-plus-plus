//This file contains Bank project's main function

#include <iostream>
#include "Bank.h"

int Bank::Worker::increaseWorker=0;
int Bank::Customer::increaseCus=0;
using namespace std;

void main()
{
	
	Bank CCB(6);
	for(int i=0;i!=96;++i)
	CCB.update();

	system("pause");

}