/**
* This file contains the difinition of AVL Tree, a balance condition tree.
* Binary search tree is the basis of this AVL tree. Pointer and recuring fucntion are widly used in this file.
* Date:15.8.27
**/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
template <typename Object> 
class AVLTree
{
public:
	//Default constuctor
	AVLTree(){root=nullptr;}
	//Destructor
	~AVLTree()
	{
		clear(root);
	}
	//Copy constructor
	AVLTree(const AVLTree & rhs)
	{
		root=clone(rhs.root);
	}
	//Copy-assignment operator 
	const AVLTree & operator=(const AVLTree &rhs)
	{
		if(this==&rhs) return *this;
		else
		{
			clear(); //Release memory
			root=clone(rhs.root); //deep copy from rhs.root
			return *this;
		}

	
	}

	//Insert x to the tree. If x is in this tree, do nothing.
	void insert(const Object & x) 
	{
		insert(x,root);
	}
	//erase x from this tree. If this tree doesn't contains x, do nothing
	void remove(const Object & x)
	{
		remove(x,root);
	}

	//Clear whole tree
	void clear()
	{
		clear(root); //Call internal edition to clear from root.
	}
	const Object & findMin() const //Function findMin, find the minimum element of this tree and return it.
	{
		return findMin(root)->element; //call internal findMin Function to get the Node of the minimum element
	}
	const Object& findMax() const //Function findMax, find the maximum element of this tree and return it.
	{
		return findMax(root)->element; //call internal findMax Function to get the Node of the maximum element
	}
	
	//Print the tree in the preorder traversal
	void pre_print(std::ostream &out=std::cout) //  //print data to ostream out.
	{
		pre_print(root,out); //print from the root node
	}


private:
	struct AvlNode
	{
		 Object element; //date
		 AvlNode * left; //Left node
		 AvlNode * right;//Right node
		 int height;  //Height of this node
		 //Constructor
		 AvlNode(const Object & theElement,AvlNode *lf,AvlNode *rt,int h=0)
			 :element(theElement),left(lf),right(rt),height(h){}
	};
	//Return the height of node t. If t is void return -1.
	int height(AvlNode *t)
	{
		if(t==nullptr) return -1;
		else return t->height;
	}
	//Internal function to insert x. AvlNode t is the start node
	void insert(const Object &x,AvlNode * &t)
	{
		if(t==nullptr)
		 t=new AvlNode(x,nullptr,nullptr);
		else if(x<t->element) //Insert to left tree
		{
			insert(x,t->left);
			if(height(t->left)-height(t->right)==2) //Balance condition is destroyed.
			{
				if(x<t->left->element)   //x is inserted to t->left->left
					 SingleRotate_LeftChild(t); //Single Rotate
				else DoubleRotate_LeftChild(t); // x is inserted to t->left->right, double rotate
			}

		}
		else if(t->element<x) //Insert to right tree
		{
			insert(x,t->right);
			if(height(t->right)-height(t->left)==2) //Balance condition is destroyed.
			{
				if(t->right->element<x) //x is inserted to t->right->right
					 SingleRotate_RightChild(t);
				else DoubleRotate_RightChild(t); //x is inserted to t->right->left
			}
		}

		t->height=Max(height(t->left),height(t->right))+1; //Increase the height of Node
	}

	//Single rotate a left child. The balance condition of node t is broken.
	void SingleRotate_LeftChild(AvlNode * &t)
	{
		AvlNode *k2,*k1,*k3;
		k2=t;
		k1=t->left;
		k3=t->left->right;
		k2->left=k3; //Move nodes
//		k2->=nullptr;
		k1->right=k2;
	
		k2->height=Max(height(k2->left),height(k2->right))+1; //Update height
		k1->height=Max(height(k1->left),height(k1->right))+1;

		t=k1;

	}
	//Single rotate a right child. The balance condition of node t is broken.
	void SingleRotate_RightChild(AvlNode * &t)
	{
		AvlNode *k2,*k1,*k3;
		k2=t;
		k1=t->right;
		k3=t->right->left;
		k2->right=k3; //Move nodes


		k1->left=k2;
		k2->height=Max(height(k2->left),height(k2->right))+1; //Update height
		k1->height=Max(height(k1->left),height(k1->right))+1;

		t=k1; 
	}
	//Double rotate a left child. The balance condition of node t is broken.
	void DoubleRotate_LeftChild(AvlNode * &t)
	{
      /**  Double rotate method
		SingleRotate_RightChild(t->left);
		SingleRotate_LeftChild(t);
	  **/

		// Node to node movement 
		AvlNode *k2,*k1,*k3,*s1,*s2;
		k1=t;
		k2=t->left; //Copy address
		k3=k2->right;
		s1=k3->left;
		s2=k3->right;

		k2->right=s1; //Move nodes
		k1->left=s2;
		k3->left=k2;
		k3->right=k1;

		k1->height=Max(height(k1->left),height(k1->right))+1; //Update heights from leaf to root
		k2->height=Max(height(k2->left),height(k2->right))+1;
		k3->height=Max(height(k3->left),height(k3->right))+1;
	
	    t=k3; //New root
	}
	//Double rotate a right child. The balance condition of node t is broken.
	void DoubleRotate_RightChild(AvlNode * &t)
	{
	  /**  Double rotate method
		SingleRotate_LeftChild(t->right);
		SingleRotate_RightChild(t);
	  **/

	  // Node to node movement 
		AvlNode *k2,*k1,*k3,*s1,*s2;
		k1=t;
		k2=t->right; //Copy address
		k3=k2->left;
		s1=k3->left;
		s2=k3->right;


		k2->left=s2; //Move nodes
		k1->right=s1;
		k3->left=k1;
		k3->right=k2;

		k1->height=Max(height(k1->left),height(k1->right))+1; //Update heights from leaf to root
		k2->height=Max(height(k2->left),height(k2->right))+1;
		k3->height=Max(height(k3->left),height(k3->right))+1;
	
	    t=k3; //New root
	}

	//Return the largest number of two int. Return anyone if two equal
	int Max(int n1,int n2)
	{
		if(n2<n1) return n1;
		if(n1<n2) return n2;
		else return n1;
	}
	//Internal findMin Function, return the AvlNode with the minimum element
	AvlNode * findMin(AvlNode * t) const
	{
		if(t==nullptr) //Only a void root
			return nullptr;
		if(t->left==nullptr) //t has no a left son. In other words t's element is the minimum
			return t; //Return this node
		else
			return findMin(t->left);  //Move to next node
	}
	//Internal findMax Function, return the AvlNode with the maximum element
	AvlNode * findMax(AvlNode * t) const
	{
		if(t==nullptr) //Only a void root
			return nullptr;
		if(t->right==nullptr) //t has no a right son. In other words t's element is the maximum
			return t;
		else
			return findMax(t->right); //move to next node
	}

	//Internal function to remove x from the tree
	void remove(const Object &x,AvlNode * &t)
	{
		if(t==nullptr)
			return;
		if(x<t->element)
		{
			remove(x,t->left);
			if(height(t->right)-height(t->left)==2) //Check balance condition
			{
				if(t->right->left==nullptr) //Remove Case 1
				 SingleRotate_RightChild(t);
				else DoubleRotate_RightChild(t);  //Remove Case 2
			}
		}
		else if(t->element<x)
		{
				remove(x,t->right);
				if(height(t->left)-height(t->right)==2) //Check balance condition
				{
					if(t->left->right==nullptr) //Remove Case 3
				    SingleRotate_LeftChild(t);
					else DoubleRotate_LeftChild(t); //Remove Case 4
				}
		}
		else //Remove the element of this Node
		{
			if(t->left!=nullptr&&t->right!=nullptr)  //Two children
			{	
				t->element=findMin(t->right)->element;
				remove(t->element,t->right); 
				if(height(t->left)-height(t->right)==2) //After remove funcntion, checking balance condition is necessary.
				{
					if(t->left->right==nullptr) 
				    SingleRotate_LeftChild(t);
					else DoubleRotate_LeftChild(t); 
				}
				
	//			AvlNode * nowMin=findMin(t->right);
	//			nowMin->height=(height(nowMin->left),height(nowMin->right))+1;
			}
			else if(t->left==nullptr&&t->right==nullptr) //no child
			{
				delete t;
				t=nullptr;
			}
			else  //Only one child
			{
				AvlNode * old=t;
				if(t->left==nullptr)
					t=t->right;
				else t=t->left;
				delete old;
			}
		}
       if(t==nullptr) return;
	   else  t->height=Max(height(t->left),height(t->right))+1; //Update the height of Node
	}
	//Internal function to clear all the tree.
	void clear(AvlNode* &t)
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

	//Clone a node and its all descendants, and return the new node
	AvlNode * clone(AvlNode * t) const //clone node * t and its object.
	{
		if(t==nullptr)
			return nullptr;

			AvlNode * lf=clone(t->left);  //copy left node
			AvlNode * rt=clone(t->right); 
	    	AvlNode * c= new AvlNode(t->element,lf,rt,t->height); //apply new memory
			return c;
	}

	//Internal function to print the tree form node to node
	void pre_print(AvlNode * t,std::ostream & out) const //print data to ostream out
	{
		if(t==nullptr) return;
		out<<t->element<<std::ends;
		pre_print(t->left,out);
		pre_print(t->right,out);
	}
	AvlNode * root;


};




#endif