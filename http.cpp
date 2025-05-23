#include "http.h"
#include <QNetworkRequest>
#include <QJsonArray>

QJsonObject Http::post(const QString &url, const QJsonObject &payload) {
    QNetworkAccessManager manager;
    QNetworkRequest request((QUrl(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QEventLoop loop;
    QNetworkReply *reply = manager.post(request, QJsonDocument(payload).toJson());
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    return json.object();
}

QJsonObject Http::get(const QString &url) {
    QNetworkAccessManager manager;
    QNetworkRequest request((QUrl(url)));
    
    QEventLoop loop;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    return json.object();
}