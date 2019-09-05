#include "common.h"

void foo(char *) {
    std::cout << "foo(char*) is called" << std::endl;
}

void foo(int i) {
    std::cout << "foo(int) is called" << std::endl;
}

void t_nullptr_0()
{
    if (std::is_same<decltype(NULL), decltype(0)>::value) {
        std::cout << "NULL == 0" << std::endl;
    }
        
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value) {
        std::cout << "NULL == (void *)0" << std::endl;
    }
        
    if (std::is_same<decltype(NULL), std::nullptr_t>::value) {
        std::cout << "NULL == nullptr" << std::endl;
    }
        
    foo(0);          // will call foo(int)
    // foo(NULL);    // doen't compile
    foo(nullptr);    // will call foo(char*)
}

