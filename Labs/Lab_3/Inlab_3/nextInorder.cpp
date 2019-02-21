#include "BST.h"

#include <iostream>

using namespace std;

int main()
{
	BST<int> tree;
	int userInput = 0;
	int limit = 0;
	
	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	tree.insert(5);
	tree.insert(4);
	tree.insert(6);

	limit = 6;

	cout << "Enter a node (1-" << limit << ") to find the next inorder node press 'q' to quit." << endl;

	while (true)
	{
		if (!(cin >> userInput))
		{
			break;
		}

		cout << "The next inorder node of " << tree.getKey(userInput) << " is " << tree.nextInorder(userInput) << endl;
	}

	return 0;
}