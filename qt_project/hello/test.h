#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <QLabel>
#include <QPushButton>

using namespace std;

void t_console()
{
    cout << "hello qt!" << endl;
    auto n = 888;
    cout << "n=" << n << endl;
    vector<int> vec = {1, 2, 8, 4, 5};
    for (auto elem : vec) {
        cout << "elem=" << elem << endl;
    }
}

void t_label()
{
    QLabel * label = new QLabel("Hello, QT!");
    label->show();
}

void t_button(QApplication &app)
{
    QPushButton * btn = new QPushButton("Quit");
    QObject::connect(btn, SIGNAL(clicked()), &app, SLOT(quit()));
    btn->show();
}

void t_test(QApplication &app)
{
    t_console();
    t_label();
    t_button(app);
}


#endif // TEST_H
