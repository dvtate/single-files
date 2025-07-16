/******************************************************************************
Write a function that does the following:

1) Construct a binary search tree, in order, from the integers given in the
   input argument vector
2) Return the distance (number of edges) between nodes with two given values.
   If either node was not found in the binary tree,
   then the function should return -1

For example, given the following vector of input values:

   8 7 13 6 2 5 1 9 11 3 4 10

and the following two node arguments:

   4 2

the function should return 3.

Given the same input vector, but the following input arguments:

   4 0

the function should return -1

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
     - Do not change function signature.
     - You are free to add any supporting helper functions
     - You are forbidden to use STL data structures
     - main function has been provided to make code run inside Rextester Web
       IDE. It is not required to be part of the submission and will not be
       graded.
******************************************************************************/



#include <iostream>
#include <sstream>
#include <string>
#include <vector>



class Tree {
public:
	class Node {
	public:
		int v;
		Node * l, * r;
		
		Node(const int value): v(value), l(nullptr), r(nullptr) {}

	};

	Node* root;

	Tree(const std::vector<int>& values) {
		this->root = nullptr;
		for (const int v : values)
			this->insert(v);
	}

	// TODO: add destructor

	// add item to bstree
	void insert(const int value) {

		Node* n = new Node(value);
		// edge case
		if (this->root == nullptr) {
			this->root = n;
			return;
		}

		Node* ins;
		Node* head = this->root;

		// find insertion point
		while (head != nullptr) {
			ins = head;
			if (head->v > value)
				head = head->l;	
			else if (head->v < value)
				head = head->r;
			else // already in bstree
				return;
		}

		// insert node
		if (ins->v > value)
			ins->l = n;
		else
			ins->r = n;
	}

	// returns sequence of Nodes leading to target
	std::vector<Node*> trace(const int value) {
		std::vector<Node*> ret;
		
		Node* n = this->root;
		while (n) {
			ret.push_back(n);
			// branch left
			if (n->v > value)
				n = n->l;
			// branch right
			else if (n->v < value)
				n = n->r;

			// found it
			else
				break;
		}
		// not in tree, return empty list
		if (!n)
			return std::vector<Node*>();

		// return sequence
		else
			return ret;

	}
};


int BSTdistance(const std::vector<int>& values, int nodeA, int nodeB)
{
	Tree bstree(values);
	std::vector<Tree::Node*>
		pathA = bstree.trace(nodeA), 
		pathB = bstree.trace(nodeB);

	// not found
	if (pathA.size() == 0 || pathB.size() == 0)
		return -1;


	// skip same elements
	unsigned int same_elems = 0;
	for (; same_elems < pathA.size() && same_elems < pathB.size(); same_elems++)
		if (pathA[same_elems] != pathB[same_elems])
			break;
	
	// could be on diverging branches
	// return number of segments going across the common node
	return pathA.size() + pathB.size() - 2 * same_elems;
}

int main ()
{
    std::cout <<BSTdistance({ 8, 7, 13, 6, 2, 5, 1, 9, 11, 3, 4, 10}, 8, 10) <<std::endl;
	std::cout <<BSTdistance({ 8, 7, 13, 6, 2, 5, 1, 9, 11, 3, 4, 10}, 4, 2) <<std::endl;
	std::cout <<BSTdistance({ 8, 7, 13, 6, 2, 5, 1, 9, 11, 3, 4, 10}, 4, 0) <<std::endl;

}
