#ifndef MKERROR_H
#define MKERROR_H

#include <QMap>
#include <QSet>
#include <QString>

#include "error.h"
#include "jobject.h"

// Enum error mappings (unused)
/*
enum ErrorOccurence {
    ACCESS_DENIED = 0x01,
    AGE_VERIFICATION = 0x02,
    AUTHORIZATION_ERROR = 0x03,
    BUFFER_STALLED_ERROR = 0x04,
    CONFIGURATION_ERROR = 0x05,
    CONTENT_EQUIVALENT = 0x06,
    CONTENT_RESTRICTED = 0x07,
    CONTENT_UNAVAILABLE = 0x08,
    CONTENT_UNSUPPORTED = 0x09,
    DEVICE_LIMIT = 0x10,
    GEO_BLOCK = 0x11,
    INVALID_ARGUMENTS = 0x11,
    PLAYREADY_CBC_ENCRYPTION_ERROR = 0x12,
    MEDIA_CERTIFICATE = 0x13,
    MEDIA_DESCRIPTOR = 0x14,
    MEDIA_LICENSE = 0x15,
    MEDIA_KEY = 0x16,
    MEDIA_PLAYBACK = 0x17,
    MEDIA_SESSION = 0x18,
    NETWORK_ERROR = 0x19,
    NOT_FOUND = 0x20,
    PARSE_ERROR = 0x21,
    PLAY_ACTIVITY = 0x22,
    QUOTA_EXCEEDED = 0x23,
    REQUEST_ERROR = 0x24,
    SERVER_ERROR = 0x25,
    SERVICE_UNAVAILABLE = 0x26,
    STREAM_UPSELL = 0x27,
    SUBSCRIPTION_ERROR = 0x28,
    TOKEN_EXPIRED = 0x29,
    UNAUTHORIZED_ERROR = 0x30,
    UNKNOWN_ERROR = 0x31,
    UNSUPPORTED_ERROR = 0x32,
    USER_INTERACTION_REQUIRED = 0x33,
    INTERNAL_ERROR = 0x34,
    OUTPUT_RESTRICTED = 0x35,
    WIDEVINE_CDM_EXPIRED = 0x36
};
*/

class MKError : public Error
{
    Q_OBJECT
public:
    MKError(JObject e, QString n);

    static MKError playActivityError(JObject e);
    static MKError parseError(JObject e);
    static MKError responseError(JObject e);
    static MKError serverError(JObject e, QString n = "UNKNOWN_ERROR");
    static MKError internalError(JObject e);

    static QMap<QString, QString> errorMap;

private:
    void preInitialization();
    void postInitialization();

    QString name;
    QString errorCode;
    QString message;
    QString description;

    QMap<int, QString> httpErrorCodes;
    QMap<int, QString> appErrorCodes;
    QSet<QString> errorList;
};

#endif // MKERROR_H
