#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

#define SIZE(p) ((p)==NULL?0:((p)->size))

template <typename T>
struct Node {
	T value;
	Node<T> *left, *right;
	int size;
	Node() : left(NULL), right(NULL), size(1) {}
	Node(const T& x) : value(x), left(NULL), right(NULL), size(1) {}
};

template <typename T>
class BST {
  Node<T>* root;
  
  /// Search for the node with the given key and return a pointer to a pointer
  /// to the node. The additional parameter incrementSizes can be set to increment
  /// the sizes in all traversed nodes along the path from the root. This should
  /// be used when inserting a new node to adjust the sizes.
  Node<T>** searchNode(const T& x, bool incrementSizes) {
  	Node<T>** p = &root;
  	while (*p != NULL) {
  		if (incrementSizes)
  			(*p)->size++;
  		if ((*p)->value < x)
  			p = &((*p)->right);
  		else if (x < (*p)->value)
  			p = &((*p)->left);
  		else
  		    return p;  // Element found in the tree, return it
  	}
  	return p; // Element not found in the tree, return a pointer to where it is supposed to be
  }
public:
  BST() : root(NULL) {}
  ~BST() {
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
  	Node<T>** p = searchNode(x, true);
  	if (*p != NULL)
  		return false; // Element found in the tree but we do not currently support duplicate values
  	// The pointer falled off the tree, the new value should be inserted at
  	// the current pointer position
  	(*p) = new Node<T>();
  	(*p)->value = x;
  }
  
  bool search(const T& x) {
  	Node<T>** p = searchNode(x, false);
  	return *p != NULL;
  }
  
  /// Return the total number of keys that are less than or equal the given key
  /// Keep in mind that the given key might not exist in the tree.
  int rank(T key) {
  	int rank = 0;
  	Node<T>* p = root;
  	while (p != NULL) {
  		if (p->value < key) {
  			// p along with all its left subtree are less than or equal key
  			rank++; // For the current node p
  			rank += SIZE(p->left); // For the left subtree
  			p = p->right;
  		} else if (key < p->value) {
  			// p is larger than the key. This does not give me any information
  			// about how many keys are less than or equal to the given key
  			// Do not update the rank
  			p = p->left;
  		} else {
  			// p->key is equal to the key. This situation is similar to the first
  			// case. We know that this node along with all its left subtree should
  			// add up to to the rank. The only difference is that this time
  			// we terminate the algorithm.
  			rank++; // For the current node p
  			rank += SIZE(p->left); // For the left subtree
  		    return rank;
  		}
  	}
  	return rank;
  }
  
  bool empty() {
  	return root == NULL;
  }
};

int main(){
	// Test the rank function in the BST
	BST<char> bst;
	// Use the same example we had in the slides
	bst.insert('K');
	bst.insert('C');
	bst.insert('M');
	bst.insert('B');
	bst.insert('E');
	bst.insert('T');
	EXPECT_EQ(0, bst.rank('A'));
	EXPECT_EQ(1, bst.rank('B'));
	EXPECT_EQ(3, bst.rank('E'));
	EXPECT_EQ(3, bst.rank('G'));
	EXPECT_EQ(6, bst.rank('Z'));
	cout << bst.rank('N') << endl;
	return 0;

}
