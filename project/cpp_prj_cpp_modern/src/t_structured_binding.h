//
// 2.5.structured.binding.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//
// http://www.cplusplus.com/reference/tuple/tuple/?kw=tuple

#include <iostream>
#include <tuple>
#include <string>

using namespace std;

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

void t_int() {
    int i = 5;
    cout << i << i++ << endl; //vc2013, 65

    i = 5;
    cout << i << endl << "hello " << i++ << endl;

    i = 5;
    cout << i << endl << "hello " << ++i << endl;
}

int t_structured_binding() {
    t_int();

    //auto[x, y, z] = f();
    //std::cout << x << ", " << y << ", " << z << std::endl;

    std::tuple<int, double, std::string> tup1 = f();
    cout << std::get<0>(tup1) << endl;
    cout << get<1>(tup1) << endl;
    cout << get<2>(tup1) << endl;

    //cout << get<3>(tup1) << endl; //ERROR

    int a;
    double b;
    string c;
    std::tie (a, b, c) = tup1;

    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;

    int d_int;
    string e_str;
    std::tie(d_int, e_str) = std::tuple<int, std::string>(get<0>(tup1), get<2>(tup1));
    cout << "d_int=" << d_int << endl;
    cout << "e_str=" << e_str << endl;

    return 0;
}
