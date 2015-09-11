/**
* This file contains the definition of a Hash table. In order to solve collision, seperate chaining is used.
* This seperate chaing method is based on some other STL, such as vector and list.
* Date:15.09.08
**/

#ifndef HASNTABLE_H
#define HASHTABLE_H
#include <list>
#include <vector>
#include <algorithm>
#include <string>

template <typename Object>  //Type Object should be string or int, because there are only hash function for those two types.
class HashTable
{
public:
	//Construct with a HashTable size. 
	explicit HashTable(int theTableSize=101):theSize(0)
	{
		Lists.resize(nextPrime(theTableSize)); //NextPrime get a closest prime which is not less theTableSize.
	}
	
	//Destructor
	~HashTable()
	{
		makeEmpty();
	}
	//Copy constructor
	HashTable (const HashTable & rhs)
	{
		operator=(rhs);
	}

	//Copy assignment operator
	const HashTable & operator=(const HashTable & rhs)
	{
		if(this!=&rhs)
			{
				makeEmpty(); //Release memory
				Lists=rhs.Lists; //Copy members
				theSize=rhs.theSize;
    		}
	   return *this;
	}


	//Return ture, if this table contains x,otherwise return false.
	bool contains(const Object &x) const
	{
		const std::list<Object> & thisList=Lists[myhash(x)];
    	std::list<Object>::const_iterator itr;
		itr=find(thisList.cbegin(),thisList.cend(),x);
		if(itr==thisList.cend())
			return false;
		else return true;
	}

    //Insert x to this HashTable. It will do nothing, if x has already been in this table.
	void insert(const Object &x)
	{
			std::list<Object> & thisList=Lists[myhash(x)];
			std::list<Object>::iterator itr;
		    itr=find(thisList.begin(),thisList.end(),x);
			if(itr==thisList.end()) //x is not in this table
		    	{
					thisList.push_front(x);
					++theSize;
					if(theSize>Lists.size()) //Keep average deppth to 1
						rehash();
			    }

	}

	//Remove x form this table. If success, return true. If this table doesn't contain x, return false.
	bool remove(const Object &x)
	{
		std::list<Object> & thisList=Lists[myhash(x)];
	    std::list<Object>::iterator itr;
		itr=find(thisList.begin(),thisList.end(),x);
		if(itr!=thisList.end()) //find x
		 {
    		 thisList.erase(itr);
			 --theSize;
			 return true;
	     }
		else return false;
		
	}
	//Return the total number of elements.
	int elementSize()
	{
		return theSize;
	}
	//Clear this table.
	void clear()
	{
		makeEmpty();
	}
	//Return the table size, the number of table size.
	int tableSize()
	{
		return Lists.size();
	
	}
private:
	//Hasn an Object, renturn an index to list
	 int myhash(const Object &k) const
	{
		return hash(k,Lists.size());
	}

	 //Hash a string
	int hash(const std::string &key, int tableSize) const
	{
		int Val=0;
		for(int i=0;i!=key.size();++i)
			Val=37*Val+key[i];
		Val=Val%tableSize;
		if (Val<0) //When Val overflows, this Val will be negtive.
			Val+=tableSize;
		return Val; 
	}
	//Hash an int
	int hash(int key,int tableSize) const
	{
		int Val=0;
		Val=key%tableSize;
		if(Val<0)
			Val+=tableSize;
		return Val;
	}

	//Rehash this table and enlarge table size. 
	void rehash()
	{
		std::vector<std::list<Object>> oldLists=Lists; 

		Lists.resize(nextPrime(2*Lists.size())); //Enlarge size
		for(int i=0;i!=Lists.size();++i) 
			Lists[i].clear();
		theSize=0;
		for(int i=0;i!=oldLists.size();++i)  //Copy table
		{
			std::list<Object>::iterator itr;
			itr=oldLists[i].begin();
			while (itr!=oldLists[i].end())
			{
				insert(*itr);
				itr++;
			}
		
		}
	}


	//Internal method to release memory
	void makeEmpty()
	{
		for(int i=0;i!=Lists.size();++i)
			Lists[i].clear();
		theSize=0;
	}

	std::vector<std::list<Object>> Lists; // Lists stored all data, if Object elements hashing are same, they are stored in a same list.
	int theSize; // total number of elements.

};

//Prime numbers from 0 to n are stored in bool pointer p called prime number table, after calling this function. If p[i]==true, i is a prime number. 
void Prime(int n,bool *p) 
{

	p[0]=false;
	p[1]=false;
	p[2]=true;
	for(int i=3;i!=n+1;++i) //Initial P
	{
		if(i%2==0) p[i]=false;
		else p[i]=true;
	}

	for(int i=3;i<=sqrt(n);i+=2) //Filter method
	{
		while(!p[i]) //Find a closest prime number
		{
			++i;
		}

		int N=n/i-1;
		int c=i;
		for(int j=1;j<=N;++j) //Filter mutiples of i
		{
			c+=i;
			if(p[c])
			p[c]=false; //Not prime number
		}

	}
}

//Return the closest prime number which is not less than n. If n is a prime number,return n.
int nextPrime(int n)
{
	if(n<=1) return 2;
	else if(n<100)
	{
		bool *p=new bool [2*n+1]; //Prime number table of 0-2*n
		Prime(2*n,p);

		for(int i=n;i!=2*n+1;++i)
			if(p[i]) 
			{
				delete[]p;
				return i;
			}
	}
	else   //Prime number table of 0-3*n/2
	{
		bool *p=new bool [3*n/2+1];
		Prime(3*n/2,p);

		for(int i=n;i!=3*n/2+1;++i)
		{
			if(p[i]) //Closest prime number
			{   
				delete[]p;
				return i;
			}
		}
		delete []p; 
		return nextPrime(3*n/2); //If not find a prime, enlarge scope.
	}
}



#endif