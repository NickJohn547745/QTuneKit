#ifndef GENERICSTORAGE_H
#define GENERICSTORAGE_H

#include <QMap>
#include <QVariant>

#include "jobject.h"

class GenericStorage
{
public:
    GenericStorage(JObject e);

    JObject getData();
    void setData (JObject e);
    int getLength();
    QStringList getKeys();
    QVariant getItem(QString e);
    void setItem(QString e, QVariant n);
    void removeItem(QString e);
    void clear();
    QString key(int index);

private:
    JObject _data;
};

#endif // GENERICSTORAGE_H
