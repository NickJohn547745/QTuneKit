#include "localstoragedevflag.h"

LocalStorageDevFlag::LocalStorageDevFlag(QString e)
{
    if (e.isEmpty())
        throw Error("DevFlag requires a non-empty string key");
    key = e;
}

auto LocalStorageDevFlag::getValue() {
    return get();
}

auto LocalStorageDevFlag::getConfigured() {
    return !value.isNull();
}

auto LocalStorageDevFlag::read() {
    var e = getLocalStorage();
    var n = NULL;

    if (e != NULL) {
        n = e.getItem(key);
    }
    return n;
}

void LocalStorageDevFlag::write(e) {
    var n = getLocalStorage();
    if (n != NULL) {
        n.setItem(key, e);
    }
}

void LocalStorageDevFlag::clear() {
    var e = getLocalStorage()
    e.removeItem(key);
}
