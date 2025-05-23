#include "cryptocoins.h"
#include "http.h"
#include "defines.h"

#include <QJsonArray>

CryptoCoins::CryptoCoins(const std::string& platformName)
    : platform(platformName)
{
}

std::string CryptoCoins::name() const {
    return platform;
}

void CryptoCoins::runParser()
{
    QJsonObject json = Http::get(COINS_API_URL);
    QJsonArray data = json["data"].toArray();

    for (const QJsonValue& item : data) {
        QJsonObject obj = item.toObject();
        std::string base = obj["baseTokenId"].toString().toStdString();
        std::string quote = obj["quoteTokenId"].toString().toStdString();
        std::string priceStr = obj["lastPrice"].toString().toStdString();

        if (quote == "PHP" && !priceStr.empty()) {
            double price = std::stod(priceStr);
            addCryptoPrice(base, price);
        }
    }
}

