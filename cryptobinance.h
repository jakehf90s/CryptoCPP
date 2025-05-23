#ifndef CRYPTOBINANCE_H
#define CRYPTOBINANCE_H

#include "icryptobase.h"

class CryptoBinance : public ICryptoBase {
public:
    explicit CryptoBinance(const std::string& platformName);
    std::string name() const override;
    void runParser() override;
private:
    std::string platform;

    void fetchAndParseSpotPrices();
    void fetchAndSetFiatRate();
};

#endif // CRYPTOBINANCE_H
