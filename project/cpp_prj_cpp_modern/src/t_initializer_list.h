//
// 2.4.initializer.list.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <initializer_list>
#include <vector>

class Foo {
public:
    int value_a;
    int value_b;
    Foo(int a, int b) : value_a(a), value_b(b) {}
};

class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
    void foo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};

void t_init_old(int arr[], int arr_size, std::vector<int> &vec) {
    Foo foo(1, 2);

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
    std::cout << "vec: " << std::endl;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }

    
}

int t_initializer_list() {

    int arr[3] = { 1, 2, 3 };
    std::vector<int> vec = { 1, 2, 3, 4, 5 };

    // before C++11    
    t_init_old(arr, 3, vec);

    // after C++11
    MagicFoo magicFoo = { 1, 2, 3, 4, 5 };
    magicFoo.foo({ 6, 7, 8, 9 });
    Foo foo2{ 3, 4 };

    
    std::cout << "magicFoo: " << std::endl;
    for (std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "foo2: " << foo2.value_a << ", " << foo2.value_b << std::endl;

    return 0;
}