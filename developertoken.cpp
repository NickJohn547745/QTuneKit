#include "developertoken.h"

DeveloperToken::DeveloperToken(QString e)
{
    token = e;

    QRegularExpression tokenRegex("^[a-z0-9\\-\\_]{16,}\\.[a-z0-9\\-\\_]{16,}\\.[a-z0-9\\-\\_]{16,}", QRegularExpression::CaseInsensitiveOption);

    if (e.isEmpty() || !tokenRegex.match(e).hasMatch())
        throw new Error("Invalid token.");
    //eyJ0eXAiOiAiSldUIiwgImFsZyIgOiAiSFMyNTYifQ
    //eyJpc3MiOiAiYWFkeWZ0aWgiLCAiZXhwIjogMTcxMjk1MjA4NH0
    //UeGoVWq8HQpiQww5hb79jL_hT9_yL2Ecrn4GKTjA06Y
    QStringList jwt = e.split('.');
    JObject header = decode(jwt[0]);
    JObject payload = decode(jwt[1]);

    expiration = QDateTime::fromSecsSinceEpoch(payload["exp"].toLongLong());
    if (isExpired()) {
        throw new Error("Initialized with an expired token.");
    }

    teamId = payload["iss"].toString();
    keyId = header["kid"].toString();
}

bool DeveloperToken::isExpired() {
    return expiration < QDateTime::currentDateTime();
}

JObject DeveloperToken::decode(QString e) {

    QByteArray data = QByteArray::fromBase64(e.toUtf8());
    QJsonObject json = QJsonDocument::fromJson(data).object();

    JObject jObj;
    foreach (QString key, json.keys()) {
        jObj[key] = json[key].toVariant();
    }
    return jObj;
}

