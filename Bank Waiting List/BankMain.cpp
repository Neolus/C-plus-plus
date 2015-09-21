//This file contains Bank project's main function

#include <iostream>
#include "Bank.h"

int Bank::Worker::increaseWorker=0; //Set static values.
int Bank::Customer::increaseCus=0;
using namespace std;

void main()
{
	
	Bank CCB(6);
	for(int i=0;i!=96;++i) //Whole the day equals 96 unit times.
        CCB.update();          //All information are placed in CCB.

	system("pause");

}
