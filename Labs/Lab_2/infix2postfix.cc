#include <iostream>
#include <gtest/gtest.h>
#include <stack>
#include <string>

using namespace std;

bool isOperand(char C)
{
	if (C >= '0' && C <= '9')
	{
		return true;
	}

	if (C >= 'a' && C <= 'z')
	{
		return true;
	}

	if (C >= 'A' && C <= 'Z')
	{
		return true;
	}

	return false;
}

int opWeight(char op)
{
	int weight = 0;

	if (op == '+' || op == '-')
	{
		weight = 1;
	}
	else if (op == '*' || op == '/')
	{
		weight = 2;
	}

	return weight;
}

string infix2postfix(string infix) {
	// TODO insert your code here
	stack<char> stack;
	string postfix = "";
	
	for (int i = 0; i < infix.size(); ++i)
	{
		if (isOperand(infix.at(i)) && infix.at(i) != ')')
		{
			postfix = postfix + infix.at(i);
		}
		else if (!stack.empty() && !isOperand(infix.at(i)) && infix.at(i) != '(')
		{
			if (stack.top() == '(')
			{
				stack.push(infix.at(i));
			}
			else if (infix.at(i) == ')')
			{
				while (!stack.empty() && stack.top() != '(')
				{
					postfix = postfix + stack.top();
					stack.pop();
				}
				
				stack.pop();
			}
			else if (stack.top() != '(')
			{
				while (!stack.empty() && stack.top() != '(' && opWeight(infix.at(i)) <= opWeight(stack.top()))
				{
					postfix = postfix + stack.top();
					stack.pop();
				}
				stack.push(infix.at(i));
			}
		}
		else
		{
			stack.push(infix.at(i));
		}
	}

	while (!stack.empty())
	{
		postfix = postfix + stack.top();
		stack.pop();
	}

	infix = postfix;

	return infix;
}

int main() {
  EXPECT_STREQ(infix2postfix("2+3").c_str(), "23+");
  EXPECT_STREQ(infix2postfix("a*b").c_str(), "ab*");
  EXPECT_STREQ(infix2postfix("2+3*5").c_str(), "235*+");
  EXPECT_STREQ(infix2postfix("A+B*C+D").c_str(), "ABC*+D+");
  EXPECT_STREQ(infix2postfix("(A+B)*C-(D-E)*(F+G)").c_str(), "AB+C*DE-FG+*-");
  cout << infix2postfix("(A+B)*C-(D-E)*(F+G)").c_str() << endl;
}

