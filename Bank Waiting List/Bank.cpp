/**
* This file contains the definition of class Bank.
**/


#include "Bank.h"
#include <iostream>
using namespace std;

Bank::Bank (int n):vacant(n),workMen(n),time(0),cusList(),waitList()
	{
		ifstream infile("Normal_dis.txt"); //Read values of standard normal distribution form Normal_dis.txt.
	    string s;
		while(infile>>s)
		{
		    double data=stod(s);
			Normal_dis.push_back(data);  //push into vector Normal_dis
		}
	}

//Update Bank to next unit time.
void Bank::update()
	{
		time=time+1; //Increase clock
        /****** Check serving customers to see if someone will left. **********/
		for(int i=0;i!=workMen.size();++i) 
		{
			if(workMen[i].status) //Find a working worker
			{
				int j=workMen[i].cus;  //Get index of his customer.
				if(cusList[j].timeOut==time) //The customer's service ends.
				{
					workMen[i].status=false; //Reset worker's status
					++vacant; //Increase vaccant number.
				}
			}
		
		}

        /**** Dealing with coming customers and waiting List. **********/
    	int CusNumberPer=cusNumber(); //Compute the number of customers who will come in this per unit time.
		for(int i=0;i!=CusNumberPer;++i) //Construct Customers and put them into waiting List.
		{
			Customer thisCus(time);
			cusList.push_back(thisCus);
			waitList.push_back(thisCus);
		}

		for(int i=0;i!=workMen.size();++i)
		{
			if(!workMen[i].status) //Find an avialable worker
			{
				if(!waitList.empty()) //Waiting List is not empty
				{
		
					waitList[0].timeOut=time+waitList[0].workTime;   //Add waiting to left time.
					cusList[waitList[0].index].timeOut=waitList[0].timeOut; //Update left time of Customer.

					workMen[i].point(waitList[0]); //A worker serves to the first customer of waiting list
					waitList.pop_front();   //dequeue
					workMen[i].status=true;// This worker is not avialable.
					--vacant;          //Vaccant number of workers decrease 1
				}
			}
		
		}
	}


//Update Bank to clock t
void Bank::to(int t)
{
	for(int i=0;i!=t;++i)
		update();
}

//return the number of available workmen.
int Bank::vacantNumber()
{
	return vacant;
}

//return the number of waiting customers
int Bank::waitNumber()
{
	return waitList.size();
}

//return the total number of customers
int Bank::customerNumber()
{
	return cusList.size();

}

//Return value of normal distribution curve at position t.
double Bank::normal(double t)  //Normal distribution depicts the number of customer per unit time. 
{      
	double exception,variance;
        expectation=48; //Expectation of normal distribution is 48,
        variance=48;    //Variance    of normal distribution is 48. Two values could be changed when necessary.
	double s=fabs(t-expectation)/variance; //Change form to standard normal distribution
	int x=100*s;            //Change to the index of vector Normal_dis
	return 1-Normal_dis[x];

}
//Return the number of customer during a unit time.
int Bank::cusNumber()
{
	return 10*normal(time); //Enlarge 10 times.
}




