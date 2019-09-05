#include "common.h"
#include "MagicFoo.h"

int t_auto() {
    cout << __FUNCTION__ << endl;

    MagicFoo magicFoo = {6, 2, 3, 4, 5};

    for (auto it = magicFoo.getVec().begin(); it != magicFoo.getVec().end(); it++) {
        std::cout << *it << " , ";
    }
    cout << "====" << endl;

    auto a = 5;
    auto b = 6;
    auto c = a + b;
    auto arr = new auto(10);

    cout << "a=" << a << endl;
    cout << "c=" << c << endl;
    cout << "arr=" << arr[0] << endl;

    SAFE_DELETE_VEC(arr);

    return 0;
}
