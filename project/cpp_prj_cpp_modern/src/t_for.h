
#include "common.h"
#include "MagicFoo.h"

void t_for() {
    MagicFoo m1 { 3, 8, 4, 6 };
    for (auto it = m1.vec.begin(); it != m1.vec.end(); it++) {
        cout << *it << ", " << endl;
    }

    cout << "==========" << endl;

<<<<<<< HEAD
#ifdef STD_CPP_17
    for (auto elem : m1.vec) {
        cout << "elem=" << elem << endl;
    }
#endif
}
=======
    for (auto elem : m1.vec) {
        cout << "elem=" << elem << endl;
    }
}
>>>>>>> 72af7c73494cdcc938887cb75f27491b0682ca89
