/***
* This file contains the definition of a data structure-List.
* Date:15.8.4
***/

#ifndef MYLIST_H
#define MYLIST_H

template <typename object> class myList
{
	struct Node  //struct Node stroes the all information of a node of list.
	{
		object data; //the node's data
		Node* prev; //points to the previous node
		Node* next; //points to the next node

		Node(const object &d=object(),Node*p=nullptr,Node*n=nullptr):data(d),prev(p),next(n){} //constructor
	};
public:

	class const_iterator //iterator class, base class const_iterator
	{
	public:
		const_iterator():current(NULL) 
		{}

		virtual ~const_iterator(){}; //destructor of const_iterator. Base class's destructor should be virtual. 
		const object &  operator*() const //overload *
		{
			return retrieve();
		}

		const_iterator & operator++() //overload ++const_iterator
		{
			current=current->next;
			return *this;
		}
		const_iterator operator++(int) //overload const_iterator++. Caution: return type shouldn't be &. const_iterator old is a local value
		{                              //considering the meaning of iterator which points to a memory of this List, there is a little difference between a copy type iterator and a reference type iterator.
			const_iterator old=*this;
			++(*this); //call the pre-increment
			return old;
		}
		const_iterator operator--() //overload --const_iterator
		{
			current=current->prev;
			return current;
		}

		const_iterator operator--(int) //overload const_iterator--
		{
			const_iterator old=*this;
			--(*this); //call the pre-decrement
			return old;
		}

		bool operator==(const const_iterator & compare) //overload ==
		{
			if(current==compare.current)
				return true;
			else
				return false;
		}
		bool operator!=(const const_iterator & compare) //overload !=
		{
			if(*this==compare)
				return false;
			else return true;
		}


	protected:
		Node *current;

		object & retrieve() const  //return the data of the node
		{
			return current->data;
		}
		const_iterator (Node*p):current(p){} //construct a const_iterator with a node.

	friend class myList<object>;
	
	};

	class iterator:const_iterator //iterator class, inherited class
	{
	public:
		iterator(){}

		object & operator*() //mutator
		{
			return retrieve();
		}
		const object& operator*()const //accessor
		{
			return retrieve();
		}

		iterator & operator++() // overload ++iterator
		{
			current=current->next;
			return *this;
		}
		iterator  operator++(int) // overload iterator++
		{                       
			iterator old=*this; 
			++(*this);
			return old;
		}
		iterator & operator--() //overload --iterator
		{
			current=current->prev;
			return *this;
		}

		iterator operator--(int) //overload iterator--
		{
			const_iterator old=*this;
			--(*this); //call the pre-decrement
			return old;
		}
	    //Rewriting == and != is necessary. Because the paramater type of operator == of class const_iterator is const_iterator. It is illegal to compare iterator and const_iterator.
		bool operator==(const iterator & compare) //overload ==
		{
			if(current==compare.current)
				return true;
			else
				return false;
		}
		bool operator!=(const iterator & compare) //overload !=
		{
			if(*this==compare)
				return false;
			else return true;
		}

	protected:
		iterator(Node*p):const_iterator(p)
		{}
	
	friend class myList<object>;

	};



public:
	myList()  //default constructor
	{
	    thesize=0;  //initialization
		head=new Node; //default construction head and tail. That is to say, head.prev=head.next=tail.prev=tail.next=NULL.
		tail=new Node;
		head->next=tail;
		tail->prev=head;
	};

	myList(const myList& L) //copy constructor
	{
		thesize=0;  //initialization
		head=new Node; 
		tail=new Node;
		head->next=tail;
		tail->prev=head;

		*this=L; //call operaotr=
//		return *this;  //return value are unnecessary and illegal for this is a constructor whose return value is void. This is a basical knowledge.
	}

	const myList& operator=(const myList &rhs) //operator assignment
	{
		if(this==&rhs) //check whether rhs is itself or not
			return *this;
		clear();
		for(const_iterator itr=rhs.begin();itr!=rhs.end();++itr)
		{
			push_back(*itr);
		}
		return *this;

	}

	~myList()  //destructor
	{
		delete head;
		delete tail;
	}
	/*******************************/ //some functions of operating iterator
	iterator insert(iterator itr,const object & x)
	{
		Node *p=itr.current; //current point
		thesize++;
		Node *s=new Node(x,p->prev,p); //creat new node with the data x
		p->prev->next=s; // previous point.next points to s, the inserted node
		p->prev=s; //current point.prev points to s.
		return iterator (s); //return a iterator
	}

	iterator erase(iterator itr) //erase a node and return the next node's iterator
	{
		Node* p=itr.current;
		iterator retVal(p->next);
		p->prev->next=p->next;
		p->next->prev=p->prev;
		delete p;
		--thesize;
		return  retVal;
	}

	iterator erase(iterator start,iterator end)  //earse some successive nodes-[strat,end)- and return the iteraor end;
	{
		for(iterator itr=start;itr!=end;) //itr++ is wrong
			itr=erase(itr);  //erase would move itr automatically
		return end;
	}


	/*********************************/ // some basical functions of List
	iterator begin()
	{
		return iterator(head->next);
	}
	const_iterator begin() const
	{
		return iterator(head->next);
	}

	iterator end()
	{
		return iterator(tail);
	}
	const_iterator end() const
	{
		return iterator(tail);
	}
	int size()
	{
		return thesize;
	}

	bool empty()
	{
		if (size()==0)
			return true;
		else return false;
	}
	/******************************/ // some operate functions of list by iterator;Two editions, mutator and accessor, are defined.
	object & front()
	{
		return *begin();
	}
	const object &front() const
	{
		return *begin();
	}

	object back()
	{
		return *(--end());
	}
	const object back() const
	{
		return *(--end());
	}

	void push_front(const object& x)
	{
		insert(begin(),x);
	}
	void push_back(const object& x)
	{
		insert(end(),x);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}


	void clear()
	{
		while(!empty())
		pop_front();  //call pop function, there are many means to clear this List
	/*	if(!empty())  //erase form begin to end with iterator
			for(iterator itr=begin();itr!=end();)
				erase(itr);
    */
	
	}


private:
	Node *head; // header node of list is void. head.next is the first element of list
	Node *tail; //tail  node of list is viod. tail.prev is the last element of list.
	int thesize;
};


#endif