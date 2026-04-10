#pragma once
#include <iostream>
using namespace std;
#define MAX_DEGREE 80
class Polynomial {
	int			degree;
	float		coef[MAX_DEGREE];
public:
	Polynomial() { degree = 0; }
	void read() {
		cout << "Max polinomial" << endl;
		cin >> degree;
		cout << "number : " << degree + 1 << endl;
		for (int i = 0; i <= degree;i++)
			cin >> coef[i];
	}
	void add(Polynomial a, Polynomial b) {
		if (a.degree > b.degree) {
			*this = a;
			for (int i = 0; i <= b.degree; i++)
				coef[i + (degree - b.degree)] += b.coef[i];
		}
		else {
			*this = b;
			for (int i = 0; i <= a.degree; i++)
				coef[i + (degree - a.degree)] += a.coef[i];
		}
	}
	bool iszero() { return degree == 0; }
	void display(const char* str = "Poly= ") {
		cout << "\t" << str;
		for (int i = 0; i < degree; i++)
			cout << coef[i] << "x^" << degree - i << "+";
		cout << coef[degree] << endl;
	}
};
