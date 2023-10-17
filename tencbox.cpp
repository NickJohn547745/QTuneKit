#include "tencbox.h"

TencBox::TencBox(QByteArray e, int n, int d)
    : BaseMp4Box("tenc", e, n, d) {
    data = e;
    start = n;
    end = d;
}

bool TencBox::isProtected() {
    return data[start + 14];
}

QString TencBox::defaultKeyId() {
    return data.sliced(start + 16, start + 32);
}

void TencBox::setDefaultKeyId(QString e) {
    for (int h = 0; h < e.length(); h++) {
        data[h + start + 16] = e[h].toLatin1();
    }
}
