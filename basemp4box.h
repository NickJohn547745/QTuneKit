#ifndef BASEMP4BOX_H
#define BASEMP4BOX_H

#include <QByteArray>
#include <QString>

class BaseMp4Box
{
public:
    BaseMp4Box(QString e, QByteArray n, int d, int h);

    QByteArray rawBytes();
    int size();

private:
    QString id;
    QByteArray data;
    int start;
    int end;
};

#endif // BASEMP4BOX_H
