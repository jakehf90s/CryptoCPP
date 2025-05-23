#include "cryptobinance.h"
#include "http.h"
#include "defines.h"
#include <QJsonArray>

CryptoBinance::CryptoBinance(const std::string& platformName)
    : platform(platformName)
{
}

std::string CryptoBinance::name() const {
    return platform;
}

void CryptoBinance::runParser()
{
    fetchAndParseSpotPrices();
    fetchAndSetFiatRate();
}

void CryptoBinance::fetchAndParseSpotPrices() {
    QJsonObject json = Http::get(BINANCE_API_BTC_USDT_URL);
    QJsonArray prices = json[""].isArray() ? json[""].toArray() : QJsonArray();  // fallback

    if (prices.isEmpty()) {
        prices = json.value("data").toArray();  // for non-standard responses
    }

    for (const QJsonValue& item : prices) {
        QJsonObject obj = item.toObject();
        QString symbol = obj["symbol"].toString();
        double price = obj["price"].toString().toDouble();

        // only fetch symbols with USDT like BTCUSDT, ETHUSDT, etc.
        if (symbol.endsWith("USDT")) {
            std::string token = symbol.left(symbol.length() - 4).toStdString();
            setReferenceRate(token, price);
        }
    }
}

void CryptoBinance::fetchAndSetFiatRate() {
    QJsonObject payload{
        {"asset", "USDT"},
        {"fiat", "PHP"},
        {"tradeType", "BUY"},
        {"payTypes", QJsonArray{"GCash"}},
        {"page", 1},
        {"rows", 1}
    };

    QJsonObject json = Http::post(BINANCE_API_URL, payload);
    double rate = json["data"].toArray()[0].toObject()["adv"].toObject()["price"].toString().toDouble();

    setFiatRate(rate);
}
