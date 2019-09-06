#include <iostream>
#include <vector>
#include <algorithm>

int t_if_switch() {
    std::vector<int> vec = { 1, 2, 3, 4 };

    // after c++17, can be simplefied by using `auto`
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }

    const std::vector<int>::iterator itr_2 = std::find(vec.begin(), vec.end(), 3);
    if (itr_2 != vec.end()) {
        *itr_2 = 4;
    }

    // should output: 1, 4, 3, 4. can be simplefied using `auto`
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element) {
        std::cout << *element << std::endl;
        
    }
     
    return 0;
}