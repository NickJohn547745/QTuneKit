#ifndef BYTERANGESEGMENT_H
#define BYTERANGESEGMENT_H

#include <QUrl>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QPromise>
#include <QPromiseResolve>
#include <QPromiseReject>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrentRun>

class ByteRangeSegment : public QObject
{
    Q_OBJECT
public:
    ByteRangeSegment(QObject *parent = nullptr, QUrl p_url = QUrl(), int p_startByte = 0, int p_length = 0, bool p_isInitSegment = false);

    QFuture<QByteArray> load();

private:
    QUrl url;
    bool isInitSegment;
    int startByte;
    int length;
    int endByte;
    QString range;

    QNetworkAccessManager *manager;
};

#endif // BYTERANGESEGMENT_H
