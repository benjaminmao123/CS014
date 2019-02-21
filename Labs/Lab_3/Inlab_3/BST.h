#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T key;
	Node<T> *right;
	Node<T> *left;
	Node<T> *parent;
	Node(T key) : key(key), right(nullptr), left(nullptr), parent(nullptr)
	{

	}
};

template <typename T> 
class BST
{
public:
	BST();
	~BST();
	Node<T> * addNode(T key);
	T nextInorder(T key);
	void insert(T key);
	void printInOrder();
	bool empty() const;
	Node<T> * search(T key);
	Node<T> * findMin(Node<T> *node);
	T getKey(T key);
	
private:
	Node<T> *root;
	Node<T> * searchHelper(T key, Node<T> *node);
	Node<T> * nextInorderHelper(Node<T> *node);
	void insertHelper(T key, Node<T> *node);
	void printInOrderHelper(Node<T> *node);
};

template<typename T>
BST<T>::BST() : root(nullptr)
{

}

template<typename T>
BST<T>::~BST()
{
	
}

template<typename T>
Node<T> * BST<T>::addNode(T key)
{
	Node<T> *nn = new Node<T>(key);

	return nn;
}

template<typename T>
void BST<T>::insert(T key)
{
	insertHelper(key, root);
}

template<typename T>
void BST<T>::insertHelper(T key, Node<T> *node)
{
	if (empty())
	{
		root = addNode(key);
		root->parent = root;
	}
	else
	{
		if (key < node->key)
		{
			if (node->left != nullptr)
			{
				insertHelper(key, node->left);
			}
			else
			{
				node->left = addNode(key);
				node->left->parent = node;
			}
		}
		else if (key > node->key)
		{
			if (node->right != nullptr)
			{
				insertHelper(key, node->right);
			}
			else
			{
				node->right = addNode(key);
				node->right->parent = node;
			}
		}
		else
		{
			cout << "Key already exists." << endl;
		}
	}
}

template <typename T>
bool BST<T>::empty() const
{
	if (root == nullptr)
	{
		return true;
	}

	return false;
}

template <typename T>
Node<T> * BST<T>::search(T key)
{
	return searchHelper(key, root);
}

template<typename T>
Node<T> * BST<T>::searchHelper(T key, Node<T> *node)
{
	if (empty() || node == nullptr)
	{
		cout << "Key not found." << endl;
		exit(1);
	}
	else if (node != nullptr && node->key == key)
	{
		return node;
	}
	else if (node->key > key)
	{
		return searchHelper(key, node->left);
	}
	else if (node->key < key)
	{
		return searchHelper(key, node->right);
	}
}

template<typename T>
Node<T> * BST<T>::findMin(Node<T> *node)
{
	if (empty())
	{
		cout << "Tree is empty." << endl;
		exit(1);
	}
	else
	{
		if (node->left != nullptr)
		{
			return findMin(node->left);
		}
		else
		{
			return node;
		}
	}
}

template<typename T>
void BST<T>::printInOrder()
{
	printInOrderHelper(root);
}

template<typename T>
void BST<T>::printInOrderHelper(Node<T> *node)
{
	if (empty())
	{
		cout << "Tree is empty." << endl;
	}
	else
	{
		if (node == nullptr)
		{
			return;
		}
		else
		{
			cout << node->key << " ";

			printInOrderHelper(node->left);
			printInOrderHelper(node->right);
		}
	}
}

template <typename T>
T BST<T>::nextInorder(T key)
{
	Node<T> *temp = search(key);
	Node<T> *nextIn = nextInorderHelper(temp);

	return nextIn->key;
}

template <typename T>
Node<T> * BST<T>::nextInorderHelper(Node<T> *node)
{
	Node<T> *successor = nullptr;

	if (node->right != nullptr)
	{
		successor = findMin(node->right);
	}
	else
	{
		successor = node->parent;

		while (successor != nullptr && node == successor->parent)
		{
			node = successor;
			successor = successor->parent;
		}
	}

	return successor;
}

template <typename T>
T BST<T>::getKey(T key)
{
	Node<T> *temp = search(key);

	return temp->key;
}
