#include <stdio.h>
#include <ctype.h>
#include "Poly.h"
#include <stdlib.h>
#include <math.h>
//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {

	PolyNode* poly = nullptr;
	double coefficient = 0;
	int exponent = 0, sign = 1, i = 0;

	while (expr[i] != '\0')
	{
		char c = expr[i];
		if (isdigit(c))
		{
			double value = 0;
			while (expr[i] != '\0' && isdigit(expr[i]) || expr[i] == '.')
			{
				if (expr[i] == '.')
				{
					int j = i + 1, cnt = 1;
					float frac = 0.1;
					while (isdigit(expr[j]))
					{
						value = value + (expr[j] - '0') * frac;
						frac *= 0.1;
						j++;
						cnt++;
					}
					i += cnt;
					continue;
				}
				value = value * 10 + (expr[i] - '0');
				i++;
			}
			coefficient = value * sign;
			i--;
		}
		else if (c == 'x')
		{
			if (coefficient == 0 && expr[i + 1] != '.')
				coefficient = sign;
			if (expr[i + 1] != '\0' && expr[i + 1] == '^')
			{
				i += 2; // Skip x
				int value = 0;
				while (expr[i] != '\0' && isdigit(expr[i]))
				{
					value = value * 10 + (expr[i] - '0');
					i++;
				}
				exponent = value;
				i--;
			}
			else
			{
				exponent = 1;
			}
			poly = AddNode(poly, coefficient, exponent);

			coefficient = 0;
			exponent = 0;
		}
		else if (c == '-')
		{
			sign = -1;
		}
		else if (c == '+')
		{
			sign = +1;
		}
		i++;
	}
	poly = AddNode(poly, coefficient, exponent);

	return poly;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	// Fill this in
	while (poly) {
		PolyNode* temp = poly;
		poly = poly->next;
		delete temp;
	}
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
	// Create new node
	PolyNode* node = new PolyNode();
	node->coef = coef;
	node->exp = exp;
	node->next = NULL;

	// Create 2 pointers to insert the node
	PolyNode* p = head;
	PolyNode* q = NULL;

	// Walk over the nodes until we hit end of the list or
	// node's exponent is bigger 
	while (p != NULL && node->exp <= p->exp) {
		// If there is already a node with the same exponent
		// add coefficients and return. 
		if (node->exp == p->exp) {
			p->coef += node->coef;

			if (q == NULL && p->coef == 0) { // If first node's coefficient is 0 delete the first node
				delete q;
				return p->next;
			}
			
			else if (p->coef == 0) { // Else if the sum equals to 0, then delete the node
				q->next = p->next;
				delete p;
			}
			return head;
		}
		// Iterate over linked list
		q = p;
		p = p->next;
	}

	// If we are inserting first element of the node
	if (q == NULL) {
		node->next = head;
		return node;
	}

	// If we are inserting somewhere but the first element
	else {
		node->next = p;
		q->next = node;
		return head;
	}

	//Return head of the node
	return node;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {

	// Create new list to store result.
	PolyNode* result = new PolyNode();

	// Create a node for iterating over poly1
	PolyNode* head = poly1;


	while (head != NULL) {
		result = AddNode(result, head->coef, head->exp); // Add every node of poly1 to result
		head = head->next;
	}

	// Assign poly2's head to some node
	head = poly2;

	while (head != NULL) {
		// Result list already consists all of the poly1 node's
		// We just simply add every poly2 nodes to result
		result = AddNode(result, head->coef, head->exp);
		head = head->next;
	}

	return result;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) { 
	// Works similar to Add(). Only difference is we add every coefficient of 
	// poly2 with minus
	PolyNode* result = new PolyNode();
	PolyNode* head = poly1;
	while (head != NULL) {
		result = AddNode(result, head->coef, head->exp);
		head = head->next;
	}
	head = poly2;
	while (head != NULL) {
		result = AddNode(result, -(head->coef), head->exp);
		head = head->next;
	}

	return result;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* res = new PolyNode();
	PolyNode* head = poly2;

	// Iterates over poly1 and poly2
	while (poly1 != NULL) {
		while (poly2 != NULL) {
			// Multiply the coefficients and sum the exponents
			// and assign this to new list using AddNode() function
			// which we coded earlier
			res = AddNode(res, poly1->coef * poly2->coef, poly1->exp + poly2->exp);
			poly2 = poly2->next;
		}
		poly2 = head;
		poly1 = poly1->next;
	}
	return res;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {

	double res = 0;
	while (poly != NULL) { // Iterates over poly1 and sums every element
		res += poly->coef * pow(x, poly->exp);
		poly = poly->next;
	}
	return res;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
	PolyNode* deriv = new PolyNode();
	while (poly != NULL && poly->exp != 0) {
		// Multiply coefficient with exponent and decrease exponent by 1
		deriv = AddNode(deriv, poly->coef * poly->exp, poly->exp - 1);
		poly = poly->next;
	}
	return deriv;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
	// Fill this in	

	// Nested loop for graph 
	for (int y = 12; y >= -12; y--) {
		for (int x = x1; x <= x2; x++) {

			if (round(Evaluate(poly, x)) == y) // If value of polynomial at x is equals to y print '*'
				printf("*");

			else if (x == 0) // Print y axis 
				printf("|");

			else if (y == 0) // Print x axis
				printf("-");
			else
				printf(" ");
		}
		printf("\n");
	}
} //end-Plot
