#include "genericstorage.h"

GenericStorage::GenericStorage(JObject e)
{
    _data = e;
}

JObject GenericStorage::getData() {
    return _data;
}

void GenericStorage::setData (JObject e) {
    _data = e;
}

int GenericStorage::getLength() {
    return _data.keys().length();
}

QStringList GenericStorage::getKeys() {
    return _data.keys();
}

QVariant GenericStorage::getItem(QString key) {
    return (_data.contains(key)) ? (_data[key]) : (QVariant(NULL));
}

void GenericStorage::setItem(QString e, QVariant n) {
    _data[e] = n;
}

void GenericStorage::removeItem(QString e) {
    _data.remove(e);
}

void GenericStorage::clear() {
    _data.clear();
}

QString GenericStorage::key(int index) {
    return (_data.keys().length() > index) ? (_data.keys()[index]) : ("");
}
