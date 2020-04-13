#ifndef JERRY_H
#define JERRY_H

#include "common.h"

class Jerry : public QObject
{
    Q_OBJECT
public:
    Jerry(QObject *parent = nullptr) : QObject(parent)
    {
        qDebug() << __FUNCTION__ << " construct..";
    }
public slots:
    void slot_RunAway()
    {
        qDebug() << __FUNCTION__ << "The Cat comming, go way!";
    }
};

#endif // JERRY_H
