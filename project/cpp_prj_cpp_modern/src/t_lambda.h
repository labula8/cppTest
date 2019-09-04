
#include <iostream>
#include <functional>

int add(int x, int y);

int add(int x, int y) {
    return x + y;
}

void t_lambda_0()
{
    // use lambda expression
    /*
    [](out = std::ref(std::cout << "Result from C code: " << add(1, 2))){
        out.get() << ".\n";
    }();
    */
}

