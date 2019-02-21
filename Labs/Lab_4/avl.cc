#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

#define HEIGHT(n) (((n) == NULL)? -1 : ((n)->height))

template <typename T>
struct Node {
	T value;
	int height;
	Node<T> *left, *right;
	Node() : left(NULL), right(NULL), height(0) {}
	Node(const T& x) : value(x), left(NULL), right(NULL), height(0) {}
	void updateHeight() {
		height = max(HEIGHT(left), HEIGHT(right)) + 1;
	}
	
	bool balanced() {
		return abs(HEIGHT(left) - HEIGHT(right)) <= 1;
	}
	
	Node* singleLeftRotation() {
		Node* k1 = this;
		Node* k2 = k1->right;
		Node* y = k2->left;
		k1->right = y;
		k2->left = k1;
		k1->updateHeight();
		k2->updateHeight();
		return k2;
		//return this;
	}
	
	Node* singleRightRotation() {
		Node* k2 = this;
		Node* k1 = k2->left;
		Node* y = k1->right;
		k1->right = k2;
		k2->left = y;
		k2->updateHeight();
		k1->updateHeight();
		return k1;
		//return this;
	}
	
	Node* doubleLeftRightRotation() {
		Node* k3 = this;
		Node* k1 = k3->left;
		Node* k2 = k1->right;
		Node* b = k2->left;
		Node* c = k2->right;
		
		k2->left = k1;
		k2->right = k3;
		k1->right = b;
		k3->left = c;
		k1->updateHeight();
		k3->updateHeight();
		k2->updateHeight();
		return k2;
		//return this;
	}
	
	Node* doubleRightLeftRotation() {
		Node* k1 = this;
		Node* k3 = k1->right;
		Node* k2 = k3->left;
		Node* b = k2->left;
		Node* c = k2->right;
		k1->right = b;
		k2->left = k1;
		k2->right = k3;
		k3->left = c;
		k1->updateHeight();
		k3->updateHeight();
		k2->updateHeight();
		return k2;
		//return this;
	}
};

#include "print_ascii.cc"
template <typename T>
class AVL;

template <typename T>
std::ostream& operator<< (std::ostream& out, const AVL<T>& v);

template <typename T>
class AVL {
  Node<T>* root;
  
  vector<Node<T>*> searchNode(const T& x) {
  	vector<Node<T>*> path;
  	Node<T>* p = root;
  	while (p != NULL) {
  		path.push_back(p);
  		if (p->value < x)
  			p = p->right;
  		else if (x < p->value)
  			p = p->left;
  		else
  		    return path;  // Element found in the tree, return the full path from the root to the node
  	}
  	return path; // Element not found in the tree, return the path to where the node is supposed to be
  }
public:
  AVL() : root(NULL) {}
  ~AVL() {
  	// Delete all nodes in the tree
  	stack<Node<T>*> toDelete;
  	toDelete.push(root);
  	while (!toDelete.empty()) {
  		Node<T>* node = toDelete.top();
  		toDelete.pop();
  		if (node != NULL) {
  		  delete node;
  		  toDelete.push(node->left);
  		  toDelete.push(node->right);
  		}
  	}
  }
  
  bool insert(const T& x) {
  	vector<Node<T>*> p = searchNode(x);
  	if (p.empty()) {
  		// Inserting at the root
  		root = new Node<T>(x);
  		// No need to check the balance after inserting one node
  		return true;
  	} else {
  		// Inserting at a non-root node
  		Node<T>* newNode = new Node<T>(x);
  		Node<T>* parent = p.back();
  		if (parent->value < x)
  			parent->right = newNode;
  		else
  			parent->left = newNode;
  		p.push_back(newNode);
  		// Now we need to update the tree height and check the balance
  		for (int i = p.size() - 1; i >= 0; i--) {
				p[i]->updateHeight();
				if (!p[i]->balanced()) {
  				// Balance the tree after insertion
  				// Check the four cases
  				Node<T>* updatedNode;
  				if (p[i+1] == p[i]->left && p[i+2] == p[i+1]->left) {
  					// Case 1: Insertion happened at left-left
  					updatedNode = p[i]->singleRightRotation();
  				} else if (p[i+1] == p[i]->left && p[i+2] == p[i+1]->right) {
  					// Case 2: Insertition happened at left-right
  					// make a double rotation
  					updatedNode = p[i]->doubleLeftRightRotation();
  				} else if (p[i+1] == p[i]->right && p[i+2] == p[i+1]->left) {
  					// Case 3: Insertition happened at left-right
  					// make a double rotation
  					updatedNode = p[i]->doubleRightLeftRotation();
  				} else {
  					// Case 4: Insertition happened at right-right
  					// make a single left rotation
  					updatedNode = p[i]->singleLeftRotation();
  				}
					if (i == 0) {
						root = updatedNode;
					} else if (p[i-1]->left == p[i]) {
						p[i-1]->left = updatedNode;
					} else {
						p[i-1]->right = updatedNode;
					}
					while (--i >= 0)
					  p[i]->updateHeight();
  			}
  		}	
  	}
  }
  
  bool search(const T& x) {
  	vector<Node<T>*> p = searchNode(x);
  	return !p.empty() && p.back()->value == x;
  }
  
  bool erase(const T& x) {
  	return false;
  	/*Node<T>** p = searchNode(x);
  	if (*p == NULL)
  		return false; // Element not found in the tree
	// Check the three cases
	if ((*p)->left == NULL && (*p)->right == NULL) {
		// TODO Case 1: Deleting a leaf node
		delete *p;
		*p = NULL;
		return true;
	} else if ((*p)->left == NULL || (*p)->right == NULL) {
		// TODO Case 2: Deleting a node with one child
		Node<T>* toDelete = *p;
		// Update the link to point to the only child of p
		if ((*p)->left != NULL)
			*p = (*p)->left;
		else
			*p = (*p)->right;
		delete toDelete; // Delete the old node
		return true;
	} else {
		// TODO Case 3: Deleting a node with two children
		// Find the minimum value in the right subtree
		Node<T>* oldNode = *p;
		Node<T>** minRight = &((*p)->right);
		while ((*minRight)->left != NULL)
			minRight = &((*minRight)->left);
		oldNode->value = (*minRight)->value;
		// Now, delete the node minRight which can only be in case 1 or 2
		// We know for sure that minRight does not have a left child
		Node<T>* toDelete = *minRight;
		*minRight = (*minRight)->right; // This will work for both cases 1 & 2
		delete toDelete;
		return true;
	}*/
  }
  
  bool empty() {
  	return root == NULL;
  }
  
  bool balanced() {
  	stack<Node<T>*> toTest;
  	toTest.push(root);
  	while (!toTest.empty()) {
  		Node<T>* n = toTest.top();
  		toTest.pop();
  		if (n != NULL) {
	  		if (!n->balanced())
	  			return false;
	  		toTest.push(n->left);
	  		toTest.push(n->right);
  		}
  	}
  	return true;
  }
  
  friend std::ostream& operator<< <> (std::ostream& out, const AVL<T>& v);
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const AVL<T>& v) {
	print_ascii_tree(out, v.root);
  return out;
}

int main() {
	// Simple test for the four cases after insertion
	AVL<int> avl;
	avl.insert(10);
	avl.insert(9);
	avl.insert(7); // A single right rotation should happen here
	EXPECT_TRUE(avl.balanced());
	avl.insert(14);
	avl.insert(18);
	EXPECT_TRUE(avl.balanced());
	avl.insert(11); // A double rotation should happen here
	EXPECT_TRUE(avl.balanced());
	avl.insert(8);
	EXPECT_TRUE(avl.balanced());

	// A good way to test an AVL tree is to create a worst-case scenario by
	// inserting items in the sorted order and make sure that the tree is
	// balanced after each insertion
	AVL<int> seq_avl;
	for (int i = 1; i <= 20; i++) {
		seq_avl.insert(i);
		EXPECT_TRUE(seq_avl.balanced());
	}
	cout << seq_avl << endl;
	return 0;
}
