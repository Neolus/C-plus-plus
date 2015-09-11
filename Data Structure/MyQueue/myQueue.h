/***
* This file contains the definition of a basic data structe, queue. This class is based on circular array.
* Date:8.15
***/
#ifndef MYQUEUE_H
#define  MYQUEUE_H

template <typename object>
class myQueue
{
public:
	/******************  //This is a failed example of iterator. It is difficult to compare two pointers of a circular array.
	class const_iterator //This iterator class could realize a few operations of queue.
	{
	public:
	//	const_iterator():current(nullptr){}

		const object & operator *() const
		{
			return retrieve();
		}

		const_iterator operator++()
		{
			object* old=current;
			if(++old>end)
				current=begin;
			else ++current;
			return *this;
		}

	protected:
		object* current; //the current point's address
		object* begin; //the first address of the array
		object* end; //the last address of the array

		object & retrieve() const
		{
			return *current;
		}
		const_iterator(object * p,int n,int psize ):begin(p),current(p+n),end(p+(psize-1)){}
		friend class myQueue<object>;
	};

	const_iterator begin() const  // the iterator of head element
	{
		return const_iterator(a,head,theSize);
	}
	const_iterator end() const  //the iterator of tail element
	{
		return const_iterator(a,tail,theSize);
	}
	**********************************/

	//constructor   
	explicit  myQueue(int initSize=0):theCapacity(initSize+SPARE_CAPACITY)
	{
		a=new object[theCapacity];
		head=0;  //Set void queue's head and tail to the same position 0
		tail=0;
		theSize=0;
	}

	~myQueue() //destructor
	{
		delete [] a;
	}

	//copy constructor
	myQueue (const myQueue &rhs):a(nullptr)
	{
		operator=(rhs);  //call operator =
	}


	const myQueue& operator=(const myQueue &rhs) //overload operator =
	{
		if(this==&rhs) return *this;
		else
		{
			delete []a; //delete old memory
			theSize=rhs.theSize;
			theCapacity=rhs.theCapacity;

			a=new object[theCapacity]; 
			head=rhs.head;
			tail=rhs.tail;

			for(int i=0;i!=size();++i) //deep copy from head to tail
			{
				int n=head+i;
				if(n>(theCapacity-1))
					n=n-theCapacity;
				a[n]=rhs.a[n];
			}
			return *this;
		}
	}

	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}

	int front() const //return the index of front element
	{
		return head;
	}

	int back() const //return the index of back element
	{
		return tail;
	}

	bool empty() const
	{
		if(theSize==0) return true;
		else return false;
	}

	void clear() //Function of clearing the queue
	{
		while(theSize!=0)
			pop();
	}

	void reserve(int newCapacity) //Function of reserving memory
	{
		if(newCapacity<=theCapacity) return;
		object* old=a;
		a=new object [newCapacity];
		for(int i=0;i!=theSize;++i) //copy elements to new memory.
		{                      
			int n=head+i;
			if(n>(theCapacity-1))
				n=n-theCapacity;
			a[i]=old[n];     //store form position 0
		}
		delete []old;
		head=0;  //adjust head to 0
		tail=theSize-1;
	}
	
	void push(const object & x) //Function of pushing elemnt at the end
	{
		if(theSize==theCapacity) //check capacity
			reserve(2*theCapacity+1);
	
		tail=next(tail); //move tail
		a[tail]=x; //insert x
		
		++theSize;
	}
	void pop() //Function of popping the front element
	{
		if(empty()) return ;
		head=next(head); //move head
		--theSize;
		if(empty()) tail=head;  //When all elements are popped, reset queue to the initial situation
	}

	int  next(int n) const //Function of moving index to the next position.It is the key of circular array.
	{
		if(empty())
			return n;
		int k=n+1;
		if(k>theCapacity-1) //When the position is at the end of array, the next position should be the first.
			k=k-theCapacity;
		return k;
	}

	const object & operator[](int k) //Overload operator[]. Access a element of this queue quickly, but it is illegal to change it.
	{                                                   //Changing the return type could realize the function of changing elements of queue.
		return a[k];
	}

	const object & operator[](int k) const //Overload operator[], const edition
	{
		return a[k];
	}

	enum {SPARE_CAPACITY=16};
private:
	object* a; //an array stores all elemnts of queue
	int head;   //points to the head of queue
	int tail;   //points to the tail of queue
	int theSize;      //current size of queue
	int theCapacity;  //the capacity of quene
};

#endif