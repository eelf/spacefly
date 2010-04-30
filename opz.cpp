#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;


float op(float op1, float op2, char op) {
	printf("op(%f, %f, %c)\n", op1, op2, op);
	switch (op) {
	case '+': return op1 + op2;
	}
}


int main(int argc, char* args) {

	stack<float> s;
    vector<string> words;
    string str;
	stringstream buf;
	float f;
 
    while( cin >> str )
		words.push_back(str);
	
    for( vector<string>::const_iterator iter = words.begin();
         iter != words.end(); ++iter ) {
		
		*iter >> f;
		buf << *iter;
		buf >> f;
		buf.clear();
		s.push( f );
		cout << "f=" << f << " s.top=" << s.top() << " ";
    }
	cout << endl << "iterations done" << endl;
	while (!s.empty()) {
		cout << s.size() << " " << s.top() << endl;
		s.pop();
	}
	
	return 0;
}
