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


int t_auto_0() {
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

    //cout << "typeid(a).raw_name=" << typeid(a).raw_name() << endl; //ERROR
    cout << "typeid(a).name=" << typeid(a).name() << endl;

    //typeof(a);
    //std::string name_a = std::string(typeid(a).name);
    //cout << "name_a=" << name_a << endl;

    cout << "a=" << a << endl;
    cout << "c=" << c << endl;
    cout << "arr=" << arr[0] << endl;

    cout << "typeid(arr).name=" << typeid(arr).name() << endl;

    SAFE_DELETE_VEC(arr);

    return 0;
}

template <typename T1, typename T2, typename T3>
T1 add1(T2 x, T3 y) {
    return x + y;
}

template <typename T1, typename T2>
auto add2(T1 x, T2 y) -> decltype(x + y) {
    return x + y;
}

#ifdef STD_CPP_17
template <typename T1, typename T2>
auto add3(T1 x, T2 y) {
    return x + y;
}
#endif

template <typename T>
const char* getTypeName(T in) {
    cout << __FUNCTION__ << "# " << typeid(in).name() << endl;
    return typeid(in).name();
}

void t_tail_return_type() {
    int a = 3;
    int b = 4;
    int z1 = add1<int, int, int>(a, b);
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "z1=" << z1 << endl;
    auto z2 = add2<int, int>(a, b);
    cout << "z2=" << z2 << endl;
    getTypeName(z2);

    auto z3 = add2<int, double>(a, b*1.3);
    cout << "z3=" << z3 << endl;
    getTypeName(z3);

#ifdef STD_CPP_17
    auto z4 = add3<int, double>(a, b*1.2);
    cout << "z4=" << z4 << endl;
    getTypeName(z4);
#endif

    return;
}

#ifdef STD_CPP_17

template <int i>
struct Int {};

constexpr auto iter(Int<0>)->Int<0>;

template <int i>
constexpr auto iter(Int<i>) {
    return iter(Int<i - 1>{});
}

#endif

void t_decl_type_auto() {

#ifdef STD_CPP_17
    decltype(int) a_int;
#endif

}

int t_auto() {
    //t_auto_0();
    //t_decltype();
    //t_tail_return_type();
    t_decl_type_auto();

    return 0;
}
