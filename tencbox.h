#ifndef TENCBOX_H
#define TENCBOX_H

#include "basemp4box.h"

class TencBox : public BaseMp4Box
{
public:
    TencBox(QByteArray e, int n, int d);

    bool isProtected();
    QString defaultKeyId();
    void setDefaultKeyId(QString e);

private:
    QByteArray data;
    int start;
    int end;
};

#endif // TENCBOX_H
