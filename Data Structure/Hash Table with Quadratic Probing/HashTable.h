/**
* This file contains the definition of a hash table. Quadratic probing is adopted to avoid collision
* Date:15.09.10
**/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>

template<typename Object>
class HashTable
{
public:
	//Construction with a hash table size.
	explicit HashTable(int theTableSize=101):currentSize(0)
	{
		table.resize(nextPrime(theTableSize));
	}
	//Destructor
	~HashTable()
	{
		table.clear();
	}

	HashTable (const HashTable & rhs)
	{
		operator=(rhs);
	}

	//Copy assignment operator
	const HashTable & operator=(const HashTable & rhs)
	{
		if(this!=&rhs)
		{
//			makeEmpty(); //Release memory
			
			table=rhs.table; //Copy table and size
			currentSize=rhs.currentSize;
		}
		return *this;
	
	}

	//Return total number of elements
	int elementSize()  const
	{
		return currentSize;
	}

	//Return table size
	int tableSize() const
	{
		return table.size();
	}




	//Return true if contains x.
	bool contains(const Object &x) const
	{
		int i=myhash(x);
		return isActive(table[i]);
	}

	//Insert x to this table. If x is in the table, nothing will be done and renturn false, else insert x and return true.
	bool insert(const Object &x)
	{
		int i=myhash(x);
		if (table[i].info==ACTIVE) //x is in this table
			return false;
		else  //Insert x
		{
			table[i]=HashEntry(x,ACTIVE);
			++currentSize; //Increase size
			if(currentSize>(table.size()/2))
					rehash();
			return true;
		}
		
	}

	//Remove x form this table. If x is not in the table, return false, else change the HashEntry's info and return true.
    bool remove(const Object &x)
	 {
		 int i=myhash(x);
		 if (table[i].info==ACTIVE) //x is in this table
			{
				table[i].info=DELETED; //Lazy deletion
				--currentSize; //Decrease size
				return true;
		    }
		 else return false;
	 
	 }
	//Clear elements, but keep table size.
	void clear()
	{
		makeEmpty();
	}



private:
	struct HashEntry //Store an element and its status information
	{
		Object element;
		int info; //Flag of HashEntry information

		HashEntry(const Object & e=Object(),int i=EMPTY):element(e),info(i)
		{}
	};

	//Tree const value for HashEntry info. 
	static const int ACTIVE =0; //This Entry is active
	static const int EMPTY  =1; //This Entry is empty
	static const int DELETED=2; //This Entry is deleted.


	//Return true, if HashEntry is active. 
	bool isActive(const HashEntry &x) const
	{
		if(x.info==ACTIVE)
			return true;
		else return false;
	}


	//Hasn an Object, renturn an index
	int myhash(const Object &x) const
	{
		int Val=hash(x,table.size());
		if(!isActive(table[Val])) return Val; //Position is Empty or Deleted
		else if(isActive(table[Val])&&table[Val].element==x) return Val; //Position is Active and element equals x
		else //Collision, adopt square probing
		{
			for(int i=1;;++i)
			{
				Val+=2*i-1;
				if(Val>=table.size())
					Val-=table.size();
				if(!isActive(table[Val])) break;
			}
		}
	   return Val;
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
		vector<HashEntry> oldTable=table;

		table.resize(nextPrime(2*table.size())); //Double the size
		makeEmpty(); 
		for(int i=0;i!=oldTable.size();++i) //Deep copy and hash new table.
		{
			if(oldTable[i].info==ACTIVE) //Find Active HashEntry
				{
			
					Object obj=oldTable[i].element;
					int i=myhash(obj);
					table[i]=HashEntry(obj,ACTIVE);
					++currentSize;
				}
		}
	}
	

	//Internal method to mark HashEntry empty
	void makeEmpty()
	{
		for(int i=0;i!=table.size();++i)
			table[i].info=EMPTY;
		currentSize=0;
	}

	std::vector<HashEntry> table; 
	int currentSize;


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
