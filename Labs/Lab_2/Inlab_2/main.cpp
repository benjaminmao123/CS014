#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isPair(const char &open, const char &close)
{
	if (open == '(' && close == ')')
	{
		return true;
	}
	else if (open == '[' && close == ']')
	{
		return true;
	}
	else if (open == '{' && close == '}')
	{
		return true;
	}

	return false;
}

bool isBalanced(string expression)
{
	stack<char> stack;

	for (int i = 0; i < expression.size(); ++i)
	{
		if (expression.at(i) == '(' || expression.at(i) == '[' || expression.at(i) == '{' || '\"')
		{
			stack.push(expression.at(i));
		} 
		else if (expression.at(i) == ')' || expression.at(i) == ']' || expression.at(i) == '}' || '\"')
		{
			if (!isPair(stack.top(), expression.at(i)))
			{
				return false;
			}
			else
			{
				stack.pop();
			}
		}
	}

	if (!stack.empty())
	{
		return false;
	}

	return true;
}

int main()
{
	string expression;

	cout << "TEST CASE RESULTS: " << endl;

	cout << "The expression [(A+B)]({C-D}{[(E-F)(G*H)]}) is ";

	if (isBalanced("[(A+B)]{C-D}({[(E-F)(G*H)]})"))
	{
		cout << "balanced." << endl;
	}
	else
	{
		cout << "unbalanced." << endl;
	}

	cout << "The expression [(A+B)[ is ";

	if (isBalanced("[(A+B)["))
	{
		cout << "balanced." << endl;
	}
	else
	{
		cout << "unbalanced." << endl;
	}

	cout << "The expression (A+B) is ";

	if (isBalanced("(A+B)"))
	{
		cout << "balanced." << endl;
	}
	else
	{
		cout << "unbalanced." << endl;
	}

	cout << "Input more test cases. Type 'q' to exit." << endl;

	getline(cin, expression);

	while (expression != "q")
	{
		cout << "The expression " << expression << " is ";
		
		if (isBalanced(expression))
		{
			cout << "balanced." << endl;
		}
		else
		{
			cout << "unbalanced." << endl;
		}
		
		getline(cin, expression);
	}

	return 0;
}