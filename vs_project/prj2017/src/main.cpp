
#include <iostream>
#include <unordered_map>

using namespace std;

#include <iostream>

using namespace std;

class Base {
    int m_tag;
public:
    Base(int tag) : m_tag(tag) {}

    void print() {
        cout << "Base::print() called" << endl;
    }

    virtual void vPrint() {
        cout << "Base::vPrint() called" << endl;
    }

    virtual void printTag() {
        cout << "Base::m_tag of this instance is: " << m_tag << endl;
    }
};

class Derived : public Base {
public:
    Derived(int tag) : Base(tag) {}

    void print() {
        cout << "Derived1::print() called" << endl;
    }

    virtual void vPrint() {
        cout << "Derived::vPrint() called" << endl;
    }

    void print_addr() {
        cout << "Derived1::print_addr() called" << endl;
        //cout << hex << "0x: " << (&Derived::print) << endl;
        printf("%p\n", (&Derived::print));
    }
};

int test_vtl_1()
{
    Derived * foo = new Derived(10);
    Base * bar = foo;

    foo->print();
    foo->vPrint();
    foo->printTag();

    bar->print();
    bar->vPrint();
    bar->printTag();

    cout << foo << endl;
    cout << bar << endl;

    if (foo != NULL)
    {
        delete foo;
        foo = NULL;
        bar = NULL;
        cout << "safe delete" << endl;
    }
    cout << foo << endl;
    cout << bar << endl;

    return 0;
}

typedef void(Derived::*fun)();

void test_fun()
{
    Derived * foo = new Derived(10);
    Base * bar = foo;

    foo->print();

    fun f = &Derived::print;
    (foo->*f)();

    //unsigned int f_addr = (unsigned int)(f);
    //cout << hex << "f_addr: 0x" << f_addr << endl;

    //unsigned int f_addr_2 = reinterpret_cast<unsigned int>(f);//编译错误,错误	1	error C2440: “reinterpret_cast”: 无法从“fun”转换为“unsigned int”	
    //unsigned int f_addr_2 = reinterpret_cast<unsigned int>(&f);
    //cout << hex << "f_addr_2: 0x" << f_addr_2 << endl;

    char buf[32] = { 0 };
    sprintf_s(buf, "%u", f);
    unsigned int f_addr_3 = atoi(buf);
    cout << hex << "f_addr_3: 0x" << f_addr_3 << endl;

    foo->print_addr();
}

void test_unordered_map()
{
    typedef unordered_map<string, string> UMAP;
    UMAP m1;
    m1.insert(make_pair<string, string>("aa", "hello"));
    m1.insert(make_pair<string, string>("bb", "world"));
    m1.insert(make_pair<string, string>("cc", "unordered_map"));

    for (auto &it : m1)
    {
        cout << "first: " << it.first.c_str() << " second: " << it.second.c_str() << endl;
    }

    typedef unordered_map<string, string>::iterator UMap_it;
    /*
    UMap_it it = m1.begin();
    while(it != m1.end())
    {
        cout << "first: " << it->first.c_str() << " second: " << it->second.c_str() << endl;
        ++it;
    }
    */

    for (UMap_it it = m1.begin(); it != m1.end(); ++it)
    {
        cout << "first: " << it->first.c_str() << " second: " << it->second.c_str() << endl;
    }

}

int main()
{
	cout << "hello c++!" << endl;

    //test_vtl_1();
    //test_fun();
    test_unordered_map();

    system("pause");
	return 0;
}
