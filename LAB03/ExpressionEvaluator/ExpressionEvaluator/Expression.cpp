#include <string>
#include <sstream>
#include <iostream>
#include <stack>

using namespace std;

//  Function which returns precedence of the operator
int precedence(char ch) {
	if (ch == '*' || ch == '/')
		return 1;

	else if (ch == '+' || ch == '-')
			return 0;

	else return -1;
}

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {
	stringstream ss(s);
	stack<char> op;
	char token;
	string result;

	
	while (ss >> token) { // Get one character
		
		if (token >= '0' && token <= '9') { // If token is a number
			int num;
			ss.putback(token); // We get first digit as a char so we need to put it back and get it as a integer
			ss >> num; // Get it as a int
			result += to_string(num) + ' '; // Add integer to the result with space character
		}
		else if (op.empty()) { // If stack is empty push the operator
			op.push(token);
		}
		else if (token == '(') { // If char is '(' then push it to the stack
			op.push(token);
		}
		else if (token == ')') { // If char is ')' then clear the stack until '(' character
			while (op.top() != '(') {
				result += op.top();
				result += ' ';
				op.pop();
			}
			op.pop();
		}
		else{
			while (!op.empty() && precedence(op.top()) >= precedence(token)) { // Pop all the elements until we encounter a operator with lower priority 
				result += op.top();
				result += ' ';
				op.pop();
			}
			op.push(token); // Push the encountered element
		}
	}

	while (!op.empty()) { // Pop left operators
		result += op.top();
		result += ' ';
		op.pop();
	}
	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	stack<int> operands;
	stringstream ss(s);
	char token;
	string str;
	int result;
	while (ss >> str) { // Get integer or operator
		if (isdigit(str[0])) { // If first element of the string is a number then string is a number
			operands.push(stoi(str)); // Push number to stack
		}
		else {
			// Operator consists one character so we assign operator to a char
			// That way we can set up a switch case
			char op = str[0]; 

			int num1, num2;

			// Get 2 operands from the stack
			num2 = operands.top();
			operands.pop();
			num1 = operands.top();
			operands.pop();

			switch(op) { // Check the operatror, then do the calculation
			case '+':
				operands.push(num1 + num2);
				break;
			case '-':
				operands.push(num1 - num2);
				break;
			case '*':
				operands.push(num1 * num2);
				break;
			case '/':
				operands.push(num1 / num2);
				break;

			}
		}
	}
	return operands.top();
} // end-EvaluatePostfixExpression
