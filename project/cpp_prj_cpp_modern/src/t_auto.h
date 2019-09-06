#include "common.h"
#include "MagicFoo.h"

void t_decltype() {
    auto a = 10;
    //auto decl_a = decltype(); //	3	IntelliSense:  不允许使用类型名
    /*
    if (decltype(a) == int) {
        cout << "a type equal int" << endl;
    }
    */
    if (std::is_same<decltype(a), int>::value) {
        cout << "a type equal int" << endl;
    }
}

int t_auto() {
    cout << __FUNCTION__ << endl;

    MagicFoo magicFoo = {6, 2, 3, 4, 5};

    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); it++) {
        //std::cout << *it << " , ";
        auto v_elem = (*it);
        std::cout << v_elem << ", ";
    }

    /*
    for (auto it = magicFoo.getVec().begin(); it != magicFoo.getVec().end(); it++) {
        //std::cout << *it << " , ";
        auto v_elem = (*it);
        std::cout << v_elem << ", ";
    }
    */
    cout << "====" << endl;

    
    cout << "typeid(magicFoo).name=" << typeid(magicFoo).name() << endl;

    auto a = 5;
    auto b = 6;
    auto c = a + b;
    auto arr = new auto(10);

    cout << "typeid(a).raw_name=" << typeid(a).raw_name() << endl;
    cout << "typeid(a).name=" << typeid(a).name() << endl;

    //typeof(a);
    //std::string name_a = std::string(typeid(a).name);
    //cout << "name_a=" << name_a << endl;

    cout << "a=" << a << endl;
    cout << "c=" << c << endl;
    cout << "arr=" << arr[0] << endl;

    cout << "typeid(arr).name=" << typeid(arr).name() << endl;

    SAFE_DELETE_VEC(arr);


    t_decltype();

    return 0;
}
