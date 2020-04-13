#ifndef TOM_H
#define TOM_H

#include "common.h"

class Tom : public QObject
{
    Q_OBJECT

public:
    Tom(QObject * parent= nullptr) : QObject(parent)
    {
        qDebug() << __FUNCTION__ << " construct..";
    }
    void miaoW()
    {
        qDebug() << __FUNCTION__ << " miaow...";
        emit sigl_Miao();
    }
signals:
    void sigl_Miao();
};

#endif // TOM_H
