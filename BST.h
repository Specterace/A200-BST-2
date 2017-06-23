/*
 Choy, Oscar
 CS A200
 March 10, 2016
 
 This file will be used as the header file for "BST.cpp", declaring all the functions defined in
 that file.
*/

#ifndef BST_H
#define BST_H

#include <string>		
#include <iostream>
#include <stack>
using namespace std;

class Node
{
	friend class BST;
public:
	Node(){}
	~Node(){}
private:
    int data;
    Node *rlink, *llink;
};

class BST
{
public:

	// Default constructor
	BST();
	// Destructor  
	~BST();
	// destroyTree
	void destroyTree();

	// recursiveInorder
	void recursiveInorder() const;

	// totalNodes
	int totalNodes() const;

	// insert
	void insert(int data);
	// nonRecursiveInorder
	void nonRecursiveInorder() const;
	// nonRecursivePreorder
	void nonRecursivePreorder() const;
	// nonRecursivePostorder
	void nonRecursivePostorder() const;
	// deleteItem
	void deleteItem(int delItem);
	// insert (recursive)
	void insertRecursive(int data, Node *p);
private:
	Node *root; //pointer to the root
	int count;  //number of nodes

	// destroy
	void destroy(Node *&p);

	// recursiveInorder
	void recursiveInorder(Node *p) const;
};

#endif