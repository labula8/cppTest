#include <iostream>

#include <boost/lexical_cast.hpp>

using namespace std;

void t_test() 
{
	using boost::lexical_cast;
	int a = lexical_cast<int>("123");
	double b = lexical_cast<double>("123.023456789");

	string s0 = lexical_cast<string>(a);
	string s1 = lexical_cast<string>(b);

	cout << "number:" << a << " " << b << endl;
	cout << "string:" << s0 << " " << s1 << endl;

	int c = 0;
	try {
		c = lexical_cast<int>("abcd");
	}
	catch(boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
}

int main()
{	
	cout << "hello!" << endl;
	t_test();
	return 0;
}
