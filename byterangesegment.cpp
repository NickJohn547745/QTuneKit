#include "byterangesegment.h"

ByteRangeSegment::ByteRangeSegment(QObject *parent, QUrl p_url, int p_startByte, int p_length, bool p_isInitSegment)
    : QObject(parent)
{
    url = p_url;
    isInitSegment = p_isInitSegment;
    startByte = p_startByte;
    length = p_length;
    endByte = startByte + length - 1;
    range = QString("bytes=%1-%2").arg(startByte).arg(endByte);
    manager = new QNetworkAccessManager(this);
}

QFuture<QByteArray> ByteRangeSegment::load() {
    QPromise<QByteArray> promise;
    QFuture<QByteArray> future = promise.future();

    QNetworkRequest request(url);
    request.setRawHeader("Range", range.toUtf8());

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, promise]() mutable {
        if (reply->error() != QNetworkReply::NoError) {
            promise.setException(std::runtime_error(reply->errorString().toStdString()));
        } else {
            QByteArray data = reply->readAll();
            promise.addResult(data);
        }
        reply->deleteLater();
        promise.finish();
    });

    return future;

    return QPromise<QByteArray>([this](const QPromiseResolve<QString>& resolve,
                                const QPromiseReject<QString>& reject) {

    });

    d = arguments;
    return new Promise(function (h, p) {
                           var y = load.apply(n, d);
                           function _next(load) {
                               asyncGeneratorStep$J(y, h, p, _next, _throw, "next", load);
                           }
                           function _throw(load) {
                               asyncGeneratorStep$J(y, h, p, _next, _throw, "throw", load);
                           }
                           _next(void 0);
                       });
}

auto ByteRangeSegment::asyncGeneratorStep$J(JObject e, n, d, func h, func p, QString y, func m) {
    try {
        var g = e[y](m);
        b = g.value;
    } catch (z) {
        return void d(z);
    }
    g.done ? n(b) : Promise.resolve(b).then(h, p);
}
