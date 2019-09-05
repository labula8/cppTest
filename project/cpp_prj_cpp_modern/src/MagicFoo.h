#pragma once

#include <initializer_list>
#include <vector>

class MagicFoo {
public:
    MagicFoo(std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
    void foo(std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
    std::vector<int> getVec() { return vec; }

private:
    std::vector<int> vec;
};

