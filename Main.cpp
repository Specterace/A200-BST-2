/*
 Choy, Oscar
 CS A200
 March 10, 2016
 
 This file will be used to test the functions of the BST implementation file "BST.cpp".
*/
#include "BST.h"

#include <iostream>
#include <fstream>
using namespace std;

void testData(BST& bst, int toDelete);

int main()
{
	// TEST 1
	int a1[] = { 13, 3, 9, 12, 4, 19, 2, 11, 16, 17, 18, 10 };
	int numOfElem1 = 12;
	BST int1BST;
	for (int i = 0; i < numOfElem1; ++i)
	{
		for (int j = 0; j < numOfElem1; ++j)
			int1BST.insert(a1[j]);
		testData(int1BST, a1[i]);
		int1BST.destroyTree();
	}

	//// TEST 2
	int a2[] = { 50, 25, 70, 16, 30, 60, 85, 12, 20, 27, 40, 54, 63, 61 };
	int numOfElem2 = 14;
	BST int2BST;
	for (int i = 0; i < numOfElem2; ++i)
	{
		for (int j = 0; j < numOfElem2; ++j)
			int2BST.insert(a2[j]);
		testData(int2BST, a2[i]);
		int2BST.destroyTree();
	}
		
	cout << endl << endl;
	system("Pause");
	return 0;
}

void testData(BST& bst, int toDelete)
{
	cout << "Tree is: ";
	bst.recursiveInorder();
	cout << "Total nodes: " << bst.totalNodes() << endl;

	cout << "Deleting " << toDelete << "...\n";

	bst.deleteItem(toDelete);

	cout << "Tree is: "; 
	bst.recursiveInorder();
	cout << "Total nodes: " << bst.totalNodes() << endl;

	cout << "\n---------------------------------------------------------\n\n";
}
