#ifndef HTTP_H
#define HTTP_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

//todo: Proxy support

class Http {
public:
    static QJsonObject post(const QString &url, const QJsonObject &payload);
    static QJsonObject get(const QString &url);
};

#endif // HTTP_H
