#ifndef DEVELOPERTOKEN_H
#define DEVELOPERTOKEN_H

#include <QDateTime>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "error.h"
#include "jobject.h"

class DeveloperToken
{
public:
    DeveloperToken(QString e);

    JObject decode(QString e);
    bool isExpired();

private:
    QDateTime expiration;
    QString token;
    QString teamId;
    QString keyId;
};

#endif // DEVELOPERTOKEN_H
