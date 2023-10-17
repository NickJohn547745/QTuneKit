#include "basemp4box.h"

BaseMp4Box::BaseMp4Box(QString e, QByteArray n, int d, int h) {
    id = e;
    data = n;
    start = d;
    end = h;
}

int BaseMp4Box::size() {
    return end - start;
}

QByteArray BaseMp4Box::rawBytes() {
    return data.sliced(start, end);
}
