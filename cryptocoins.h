#ifndef CRYPTOCOINS_H
#define CRYPTOCOINS_H

#include "icryptobase.h"

class CryptoCoins : public ICryptoBase {
public:
    explicit CryptoCoins(const std::string& platformName);
    std::string name() const override;
    void runParser() override;

private:
    std::string platform;
};

#endif // CRYPTOCOINS_H
