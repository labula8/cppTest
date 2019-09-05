
#include "common.h"
#include "MagicFoo.h"

void t_for() {
    MagicFoo m1 { 3, 8, 4, 6 };
    for (auto it = m1.vec.begin(); it != m1.vec.end(); it++) {
        cout << *it << ", " << endl;
    }

    cout << "==========" << endl;

#ifdef STD_CPP_17
    for (auto elem : m1.vec) {
        cout << "elem=" << elem << endl;
    }
#endif
}
