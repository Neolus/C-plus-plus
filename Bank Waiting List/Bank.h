/** 
* This file is the declaration of class Bank. It is designed for bank waiting problem.
* Model hypothesis:1. A unit time is five minutes.
*                  2. The number of customers arriving at per unit time, is similar to normal distribution curve.
*                  3. The business period of a customer is a uniform distribution. 
*
* Date:15.09.17 
**/

#ifndef BANK_H
#define BANK_H

#include <random>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cmath>


class Bank
{
public:
	explicit Bank (int n); //total number of workers is n.
	void update(); //Update Bank to next unit time.
	void to(int t); //Update Bank for time=0  to time=t.
	int vacantNumber();  //return the number of available workmen at clock time.
	int waitNumber();    //return the number of waiting customers at clock time.
	int customerNumber();//return the total number of customers form open to now.

private:

	struct Customer 
	{
		int timeIn;   // Customer's arrival time
		int timeOut;  // Customer's arrival time
		int workTime; // It will take workTime to do service.
		int index;    // The index of customer
		static int increaseCus; //IncreaseCus is used to increase index
		Customer(){};

		Customer(int time):timeIn(time),index(increaseCus++)
		{
			static std::default_random_engine e; //Random engine e
		    static	std::uniform_int_distribution<unsigned> u(1,3); //Uniform distribution minimum is
			workTime=u(e);
			timeOut=timeIn+workTime;
		}


	};
	struct Worker
	{
		int cus;     //The index of customer to whom this worker is serving. 
		int index;   //The index of worker
		bool status; //If it works, is true,or else is false.
		static int increaseWorker; //IncreaseWorker is used to increase the index of worker.

		Worker & point(const Customer & cust) //point to a customer who will be served by this worker.
		{
			cus=cust.index;
			return * this;
		}
		//Constructor 
		Worker(bool s=false):index(increaseWorker++),status(s)
		{}
	};

	//Return value of normal distribution curve at position t.
	double normal(double t);
	//Return the number of customer during per unit time.
	int  cusNumber();
	
	


	 int time; //Clock
	 int vacant; //The number of available workers.
	 std::vector<Worker> workMen; //The bank's workmen
	 std::vector<Customer> cusList; //All customers. They are arriving in the day.
	 std::deque<Customer> waitList; //Waiting customers at clock time 
	 std::vector<double> Normal_dis; //Values of standard normal distribution

};


#endif
