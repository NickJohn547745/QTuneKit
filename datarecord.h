#ifndef DATARECORD_H
#define DATARECORD_H

#include <QList>

#include "mkutils.h"
#include "jobject.h"

class DataRecord
{
public:
    DataRecord(QString type, QString n, JObject d = {});

    bool _hasProperties(QStringList e, QStringList n);
    bool hasAttributes(QStringList attrs);
    bool hasRelationships(QStringList rels);
    bool hasViews(QStringList views);

    bool hasProperties(JObject e);
    void setParent(QString newPar);
private:
    QString type;
    QString id;

    JObject _meta;
    JObject _mjs;
};

#endif // DATARECORD_H
