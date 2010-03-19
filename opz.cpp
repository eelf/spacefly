#include <iostream>

class Stack {
	char stack[100];
	int p;
	Stack() {
		p = 0;
	}
	void push(char e) {
		if (p == 100) throw "Stack full";
		stack[p++] = e;
	}
	char pop() {
		if (p == 0) throw "Stack empty";
		return stack[--p];
	}
	char top() {
		return stack[p];
	}
};


int main(int argc, char* args) {
	char input[100];
	cin >> input;
	return 0;
}
