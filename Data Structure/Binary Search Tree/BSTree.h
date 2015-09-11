/***
* This file contains the definition of class Binary search tree, called BSTree in this program. It is a useful data structure.
* Recursion loop is widely used in this file.
* Date: 15.8.20
***/

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <typename Object>
class BSTree
{
public:
	BSTree(){root=nullptr;}
	//Destructor
	~BSTree()
	{
		clear(root);
	}
	//Copy constructor
	BSTree(const BSTree & rhs)
	{ 
	   //operator=(rhs); It is wrong to call operator = in this copy constructor
	   //clear(root);     //root is void, but doesn't point to an object, root!=nullptr 
		root=clone(rhs.root);
	}
	//Deep copy
	const BSTree & operator=(const BSTree & rhs) //copy assignment
	{
		if(this==&rhs) return *this;
		if(this!=&rhs)
		{
			clear(root); //Release old memory.
			root=clone(rhs.root); //Copy to this tree
		}
	    return *this;
	}

	bool empty()
	{
		if(root==nullptr)
			return true;
		else return false;
	}


	bool contains(const Object & x) const //Function contains is used to see whether Object x is in this tree. If the tree includes x, return true.
	{
		return contains(x,root); //call the private contains function
	}

	const Object & findMin() const //Function findMin, find the minimum element of this tree and return it.
	{
		return findMin(root)->element; //call internal findMin Function to get the Node of the minimum element
	}
	const Object& findMax() const //Function findMax, find the maximum element of this tree and return it.
	{
		return findMax(root)->element; //call internal findMax Function to get the Node of the maximum element
	}

	void insert(const Object & x)// Insert x into the tree. If it contains x, this function will do nothing.
	{
		insert(x,root); //call internal insert function. Insert from the root
	}

	void remove(const Object & x)// Remove x from this tree. If it does not contains x, this function will do nothing.
	{
	   remove(x,root);//call internal remove function
	}

	//Print the tree in the preorder traversal
	void pre_print(std::ostream &out) //  //print data to ostream out.
	{
		pre_print(root,out); //print from the root node
	}



private:
	struct BinaryNode
	{
		Object element;
		BinaryNode * left;
		BinaryNode * right;
		BinaryNode(const Object &x,BinaryNode* lt,BinaryNode* rt):element(x),left(lt),right(rt){}
	};


	//Internal contains function, if find x in this tree, return true
	bool contains(const Object & x,BinaryNode* t) const
	{
		if(t==nullptr) return false; //void Node
		if(x<t->element)
			return contains(x,t->left);
		else if(t->element<x)
			return contains(x,t->right);
		else return true; //find x
	}

	//Internal findMin Function, return the BinaryNode with the minimum element
	BinaryNode * findMin(BinaryNode * t) const
	{
		if(t==nullptr) //Only a void root
			return nullptr;
		if(t->left==nullptr) //t has no a left son. In other words t's element is the minimum
			return t; //Return this node
		else
			return findMin(t->left);  //Move to next node
	}
	//Internal findMax Function, return the BinaryNode with the maximum element
	BinaryNode * findMax(BinaryNode * t) const
	{
		if(t==nullptr) //Only a void root
			return nullptr;
		if(t->right==nullptr) //t has no a right son. In other words t's element is the maximum
			return t;
		else
			return findMax(t->right); //move to next node
	}

	//Internal function to insert x to the tree.
	void insert(const Object &x,BinaryNode* &t) //The reference of pointer t could realize the change of the Node's pointer.
	{
		if(t==nullptr) 
		{
			t=new BinaryNode(x,nullptr,nullptr);
	//		t->element=x; 
		}
		else if(x<t->element) 
			insert(x,t->left);
		else if(t->element<x)
			insert(x,t->right);
	//	else return; 
	}

	//Internal function to remove x from the tree
	void remove(const Object &x,BinaryNode * &t)
	{
		if(t==nullptr)
			return;
		BinaryNode *old=t;
		if(x<t->element)
			remove(x,t->left);
		else if(t->element<x)
			remove(x,t->right);
		else //Remove the element of this Node
		{
			if(t->left!=nullptr&&t->right!=nullptr)  //Two children
			{	
				t->element=findMin(t->right)->element;
				remove(t->element,t->right);
			}
			else if(t->left==nullptr&&t->right==nullptr) //no child
			{
				delete t;
				t=nullptr;
			}
			else  //Only one child
			{
				BinaryNode * old=t;
				if(t->left==nullptr)
					t=t->right;
				else t=t->left;
				delete old;
			}
		}
		
	}

	//Internal function to clear all the tree.
	void clear(BinaryNode* &t)
	{
		if(t!=nullptr)
		{
			if(t->left==nullptr&&t->right==nullptr) //leaf
				{
					delete t; //release memory
					t=nullptr;
			    }
			else if(t->left!=nullptr)
				clear(t->left);
			else if(t->right!=nullptr)
				clear(t->right);
				
		/*	clear(t->left);
			clear(t->right);
			delete t;
			*/
		}
	 t=nullptr;
	}

	//clone a node and its all descendants, and return the new node
	BinaryNode * clone(BinaryNode * t) const //clone node * t and its object.
	{
		if(t==nullptr)
			return nullptr;

			BinaryNode * lf=clone(t->left);  //copy left node
			BinaryNode * rt=clone(t->right); 
	    	BinaryNode * c= new BinaryNode(t->element,lf,rt); //apply new memory
			return c;
		//	return new BinaryNode(t->element,clone(t->left),clone(t->right));//Left and right node are also need to cloned. It is necessary to apply new memory.
	}

	//Internal function to print the tree form node to node
	void pre_print(BinaryNode * t,std::ostream & out) const //print data to ostream out
	{
		if(t==nullptr) return;
		out<<t->element<<std::ends;
		pre_print(t->left,out);
		pre_print(t->right,out);
	}
	BinaryNode * root;
};



#endif