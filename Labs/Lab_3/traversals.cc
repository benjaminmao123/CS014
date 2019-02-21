#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <stack>
#include "helper.hh"

using namespace std;

template <typename T>
vector<T> preorderTraversalNoRecursion(Node<T>* root) {
  vector<T> preorder;
  // if (root == NULL)
  //   return preorder;
  // // 1. root
  // preorder.push_back(root->value);
  // // 2. Preorder left
  // vector<T> preorderLeft = preorderTraversalNoRecursion(root->left);
  // preorder.insert(preorder.end(), preorderLeft.begin(), preorderLeft.end());
  // // 3. Preorder right
  // vector<T> preorderRight = preorderTraversalNoRecursion(root->right);
  // preorder.insert(preorder.end(), preorderRight.begin(), preorderRight.end());
  stack<Node<T>*> s;
  
  s.push(root);
  
  while (!s.empty())
  {
	  Node<T> *node = s.top();

	  preorder.push_back(node->value);
	  s.pop();

	  if (node->right != nullptr)
	  {
      s.push(node->right);
	  }
	  
	  if (node->left != nullptr)
	  {
	    s.push(node->left);
	  }
  }
  
  return preorder;
}

template <typename T>
vector<T> inorderTraversalNoRecursion(Node<T>* root) {
  vector<T> inorder;
  
  if (root == NULL)
    return inorder;
  
  // 1. Inorder left
  vector<T> inorderLeft = inorderTraversalNoRecursion(root->left);
  inorder.insert(inorder.end(), inorderLeft.begin(), inorderLeft.end());
  // 2. root
  inorder.push_back(root->value);
  // 3. Inorder right
  vector<T> inorderRight = inorderTraversalNoRecursion(root->right);
  inorder.insert(inorder.end(), inorderRight.begin(), inorderRight.end());
  
  stack<Node<T>*> s;
  bool isDone = false;
  Node<T> *node = root;
  
  while (!isDone)
  {
    if (node != nullptr)
    {
      s.push(node);
      node = node->left;
    }
    else
    {
      if (!s.empty())
      {
        inorder.push_back(s.top()->value);
        node = s.top();
        s.pop();
        node = node->right;
      }
      else
      {
        isDone = true;
      }
    }
  }

  return inorder;
}

void testPreorder() {
  Node<int>* root = buildTree(vector<int>({1}), vector<int>({1}));
  vector<int> preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1}), preorder);
  delete(root);
  
  root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({10, 8, 3, 5, 2, 7}), preorder);
  delete(root);

  root = buildTree(vector<int>({1, 2, 3, 4, 5}), vector<int>({1, 4, 3, 2, 5}));
  preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1, 2, 3, 4, 5}), preorder);
  delete(root);
}


void testInorder() {
  Node<int>* root = buildTree(vector<int>({1}), vector<int>({1}));
  vector<int> inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1}), inorder);
  delete(root);
  
  root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({3, 8, 5, 10, 7, 2}), inorder);
  delete(root);
  
  root = buildTree(vector<int>({1, 2, 3, 4, 5}), vector<int>({1, 4, 3, 2, 5}));
  inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1, 4, 3, 2, 5}), inorder);
  delete(root);
}


int main() {
  testBuildTree();
  testPreorder();
  testInorder();
  
  Node<int>* root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  vector<int> preorder = preorderTraversalNoRecursion(root);
  vector<int> inorder = inorderTraversalNoRecursion(root);
  cout << "Preorder: " << preorder << endl
       << "Inorder: " << inorder << endl;
  cout << "Finished succesfully!" << endl;
}

