/***
* The file refered form the textbook is a basic STL vector.
* Date:15.5.16
***/

#ifndef MYVECTOR_H
#define MYVECTOR_H
template <typename object>
class myVector
{
public:
	explicit myVector(int inisize=0):thesize(inisize),thecapacity(inisize+SPARE_CAPACITY) //constructor 
    {
		arry=new object[thecapacity];  //assign memory 
	}

	myVector (const myVector &rhs):arry(nullptr)  //copy constructor 
	{
		   operator=(rhs); //calling the operator == is a useful way.
	 
	}

	~myVector(){delete []arry;} //destructor 
	
	const myVector &operator=( const myVector &rhs) //assignment operator
	{
		if(this!=&rhs)
		{
			delete []arry; //release old memory.
			thesize=rhs.thesize; //calling rhs.size() is wrong. size() return a const int, but thesize is an int.
			thecapacity=rhs.thecapacity;
			arry=new object[thecapacity];
			
			for(int i=0;i!=thesize;++i) //deep copy 
			{
				arry[i]=rhs.arry[i];
			}
		}
		return *this;
	}

	object & operator[](int i)
	{return arry[i];}

	const object & operator[](int i) const
	{return arry[i];}

	void reserve(int newcapacity)//reserve memory
	{
		if(newcapacity>capacity())
		{
			object *oldarray=arry; //point to old memory 
		//	oldarray=arry;
			arry=new object[newcapacity];
			for(int i=0;i!=thesize;++i)//deep copy 
			{
				arry[i]=oldarray[i];
			}
		delete []oldarray;
		}
	}


	void resize(int newsize) //change the size of vector
	{
		if(newsize>thecapacity)
		{
			reverse[2*newsize+1];
		}
	}

	void push_back(const object &obj)
	{
		if(thesize==thecapacity)
		{
			reserve(2*thesize+1);
		}
		arry[thesize++]=obj;
	}

	void pop_back()
	{
		--thesize;
	}

	//use the traditional pointer as iterator
	typedef object* iterator;
	typedef const object* const_iterator;

	//return iterator functions
	iterator begin()
	{
		return &arry[0];
	}
	const_iterator begin() const
	{
		return &arry[0];
	}

	iterator end()
	{
		return &arry[size()];
	
	}
	const_iterator end() const
	{
		return &arry[size()];
	
	}

	int size()
	{return thesize;}
	bool empty()
	{return size()==0;}
	int capacity()
	{return thecapacity;}


	enum 
	{
		SPARE_CAPACITY=16 //';' is unnecessary;
	};
private:
	int thesize; //vector's size
	int thecapacity; // vector's capacity. 
	object * arry; //use array to store data. 
};


#endif