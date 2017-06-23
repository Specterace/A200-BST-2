/*
 Choy, Oscar
 CS A200
 March 10, 2016
 
 This is another implementation of a binary search tree (a BST). It has the following functions: 
 a default constructor, a destructor, "destroy", "destroyTree", "recursiveInOrder", "totalNodes",
 "insert" (both recursive and non-recursive), "nonRecursiveInorder", "nonRecursivePreorder",
 "nonRecursivePostorder", and "search(recursive)". This BST is implemented on a doubly-linked list.
*/
#include "BST.h"

// // This is the default constructor. It constructs a BST without being given any node as a root.
BST::BST() {
	root = NULL;
	count = 0;
}

// This is the BST's destructor. It calls the "destroyTree" function.
BST::~BST() {
	
	destroyTree();
}

// This is the "destroyTree" function. It destroys the BST tree.
void BST::destroyTree() {
	
	destroy(root);
	count = 0;
}

// This is the "destroy" function. It destroys the node it is given, and it also destroys the nodes
// linked to it (the one pointing to it and the one it is pointing to.
void BST::destroy(Node *&p) {
	if (p != NULL) {
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}

// This is the "recursiveInorder" function. Calling it allows the user to traverse the entire BST 
// recursively in a "inorder" fashion by calling a helper function to do the actual traversal.
void BST::recursiveInorder() const{

	if (root == NULL) {
		cerr << "There is no tree.";
	} else {
		recursiveInorder(root);
	}
}

// This is the "recursiveInorder" helper function. It takes a node as an argument, and first visits 
// its left subtree, then the node itself, and then the node's right subtree. It does all of these visits
// recursively.
void BST::recursiveInorder(Node *p) const {
	if (p != NULL) {
		recursiveInorder(p->llink);
		cout << p->data << " ";
		recursiveInorder(p->rlink);
	}
}

// This is the "totalNodes" function. It returns the number of nodes in the BST.
int BST::totalNodes() const {
	return count;
}


//This is the non-recursive version of the "insert" function.
void BST::insert(int data) {
	Node *newNode = new Node();
	newNode->data = data;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (count == 0) {
		root = newNode;
		++count;
	} else {
		Node *currNode = root;
		bool enteredNode = false;
		while (!enteredNode) {
			if (currNode->data > data) {
				if (currNode->llink == NULL) {
					currNode->llink = newNode;
					++count;
					enteredNode = true;
				} else {
					currNode = currNode->llink;
				}
			} else if (currNode->data < data) {
				if (currNode->rlink == NULL) {
					currNode->rlink = newNode;
					++count;
					enteredNode = true;
				} else {
					currNode = currNode->rlink;
				}
			} else {
				cerr << "The item to insert is already in the list. Duplicates are not allowed." << endl;
				delete newNode;
				enteredNode = true;
			}
		}
	}	
}



// This is the "nonRecursiveInorder" function. It traverses the BST in an non-recursive manner, in
// an in-order fashion (visits the left subtree, then the current node/root, then the right subtree).
void BST::nonRecursiveInorder() const {
	Node *currNode = root;
	if (currNode == NULL) {
		cerr << "There is no tree.";
	}
	else {
		stack<Node *> pointStack;
		pointStack.push(currNode);
		currNode = currNode->llink;

		while ((currNode != NULL) || (!pointStack.empty())) {
			if (currNode != NULL) {
				pointStack.push(currNode);
				currNode = currNode->llink;
			}
			else {
				currNode = pointStack.top();
				cout << currNode->data << " ";
				currNode = currNode->rlink;
				pointStack.pop();
			}
		}
	}
}


// This is the "nonRecursivePreorder" function. It traverses the BST in an non-recursive manner, in
// a pre-order fashion (visits the current node/root, then the left subtree, then the right subtree).
void BST::nonRecursivePreorder() const{
	Node *currNode = root;
	if (currNode == NULL) {
		cerr << "There is no tree.";
	} else {
		stack<Node *> pointStack;
		pointStack.push(currNode);
		cout << currNode->data << " ";
		currNode = currNode->llink;
		while ((!pointStack.empty()) || (currNode != NULL)) {
			if (currNode != NULL) {
				pointStack.push(currNode);
				cout << currNode->data << " ";
				currNode = currNode->llink;
			}
			else {
				currNode = pointStack.top()->rlink;
				pointStack.pop();
			}

		}
	}
}





// This is the "nonRecursivePostorder" function. It traverses the BST in an non-recursive manner, in
// a post-order fashion (visits the left subtree, then the right subtree, then the current node/root).
void BST::nonRecursivePostorder() const {
	Node *currNode = root;

	if (currNode == NULL) {
		cerr << "There is no tree.";
	}
	else {
		stack<Node *> pointStack;
		stack<int> intStack;
		int value = 0;
		pointStack.push(currNode);
		intStack.push(1);
		currNode = currNode->llink;
		while (!pointStack.empty() && (!intStack.empty())) {
			if (currNode != NULL && (value == 0)) {
				pointStack.push(currNode);
				currNode = currNode->llink;
				intStack.push(1);

			} else {
				currNode = pointStack.top();
				value = intStack.top();
				pointStack.pop();
				intStack.pop();
				if (value == 1) {
					pointStack.push(currNode);
					intStack.push(2);
					currNode = currNode->rlink;
					value = 0;
				}
				else {
					cout << currNode->data << " ";
				}
			}
		}

	}

}

// This is the "deleteItem" function. It deletes the node that contains the integer it is given
// as an argument, if that node exists in the tree. If it is not in the tree, or if the tree does
// not exist, it will print out an error message. After deleting the node, it will re-configure the
// BST so that it is accurate once more (this is mostly relevant in cases where the deleted node is
// not a leaf node).
void BST::deleteItem(int delItem) {

	if (root == NULL) {
		cerr << "There is no tree. Cannot delete." << endl;
	} else {
		Node *currNode = root;
		Node *trailNode = NULL;	//Creating a trailing pointer
		int currValue, direction = 0;
		bool searchOver = false;

		while (!searchOver) {
			if (currNode == NULL) {
				cerr << "Node is not present in tree. Cannot delete." << endl;
				searchOver = true;
			}
			else {
				currValue = currNode->data;
				if (currValue == delItem) {
					if ((currNode->llink == NULL) && (currNode->rlink == NULL)) {	//If deleted Node is a leaf
						if (direction == 1) {
							trailNode->llink = NULL;
						} else if (direction == 2) {
							trailNode->rlink = NULL;
						} else {
							root = NULL;
						}
						delete currNode;
					}
					else if (currNode->llink == NULL) {			//If deleted Node has no left subtree
						if (direction == 1) {
							trailNode->llink = currNode->rlink;
						} else if (direction == 2) {
							trailNode->rlink = currNode->rlink;
						} else {
							root = currNode->rlink;
						}
						delete currNode;

					}
					else if (currNode->rlink == NULL) {			//If deleted Node has no right subtree
						if (direction == 1) {
							trailNode->llink = currNode->llink;
						} else if (direction == 2) {
							trailNode->rlink = currNode->llink;
						} else {
							root = currNode->llink;
						}
						delete currNode;
					}
					else {				//If deleted Node has both left and right subtrees
						Node *largestPreDes = currNode->llink;	//Using largest predescessor
						Node *preDesTrailing = NULL;
						while (largestPreDes->rlink != NULL) {
							preDesTrailing = largestPreDes;
							largestPreDes = largestPreDes->rlink;
						}

						largestPreDes->rlink = currNode->rlink;
						if (preDesTrailing != NULL) {
							preDesTrailing->rlink = largestPreDes->llink;
							largestPreDes->llink = currNode->llink;
						}
						if (direction == 1) {
							trailNode->llink = largestPreDes;
						} else if (direction == 2) {
							trailNode->rlink = largestPreDes;
						} else {
							root = largestPreDes;
						}
						delete currNode;
						largestPreDes = NULL;
						preDesTrailing = NULL;
					}
					--count;
					searchOver = true;
				}
				else if (currValue > delItem) {
					trailNode = currNode;
					currNode = currNode->llink;
					direction = 1;
				}
				else {
					trailNode = currNode;
					currNode = currNode->rlink;
					direction = 2;
				}
			
			}
		}
		currNode = NULL;
		trailNode = NULL;
		
	}

}

////This is the recursive version of the "insert" function.
void BST::insertRecursive(int data, Node *p) {
	Node *newNode = new Node();
	newNode->data = data;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (count == 0) {
		root = newNode;
		++count;
	} else if (p->data == data) {
		cerr << "The item to insert is already in the list. Duplicates are not allowed." << endl;
		delete newNode;
	}
	else if (p->data > data) {
		if (p->llink == NULL) {
			p->llink = newNode;
			++count;
		}
		else {
			insertRecursive(data, p->llink);
		}
	} else {
		if (p->rlink == NULL) {
			p->rlink = newNode;
			++count;
		} else {
			insertRecursive(data, p->rlink);
		}
	}
}