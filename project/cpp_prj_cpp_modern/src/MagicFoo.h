#pragma once

#include <initializer_list>
#include <vector>

class MagicFoo {
public:
    MagicFoo(std::initializer_list<int> list) {
        vec.clear();
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
            std::cout << "MagicFoo push_back() " << *it << std::endl;
        }
    }
    void foo(std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
            std::cout << "foo push_back() " << *it << std::endl;
        }
    }
    std::vector<int> getVec() { return vec; }

private:
    std::vector<int> vec;
};

