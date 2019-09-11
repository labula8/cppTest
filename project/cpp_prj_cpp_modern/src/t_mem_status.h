#include "common.h"

class A {
public:
    A():n(0) {};
    ~A(){};

    A * getThis() { return this; }

    //普通函数修改，类静态变量
    void update() {
        cout << __FUNCTION__ << endl;
        ++n;
        ++n_static;
    };

    //静态函数修改，类静态变量
    static void updateStatic() {
        cout << __FUNCTION__ << endl;
        //++n; //error C2597: 对非静态成员“A::n”的非法引用
        ++n_static;
    };

    void show() {
        cout << "n=" << n << endl;
        cout << "n_static=" << n_static << endl;
    }

public:
    int n;
    static int n_static;
};

int A::n_static = 0;

void t_mem_status()
{
    cout << __FUNCTION__ << endl;

    A obj_a;
    A obj_b;

    cout << "class A this address=0x" << obj_a.getThis()<< endl;

    cout << "obj_a.address=0x" << &obj_a << endl;
    cout << "obj_a.n address=0x" << &obj_a.n << endl;
    cout << "obj_a.n_static address=0x" << &obj_a.n_static << endl;


    cout << "obj_b.address=0x" << &obj_b << endl;
    cout << "obj_b.n address=0x" << &obj_b.n << endl;
    cout << "obj_b.n_static address=0x" << &obj_b.n_static << endl;

    cout << "class A n_static address=0x" << &A::n_static << endl;


    obj_a.show();
    obj_a.update();
    obj_a.show();

    obj_a.updateStatic();
    obj_a.show();

    A::updateStatic();
    obj_a.show();
    obj_b.show();

    return;    
}