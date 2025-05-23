#ifndef ARBITRAGECALCULATOR_H
#define ARBITRAGECALCULATOR_H

#include "icryptobase.h"
#include <vector>
#include <QString>


struct ArbitrageResult {
    ICryptoBase* buyCrypto;
    std::string buyCryptoType;
    ICryptoBase* sellCrypto;
    std::string sellCryptoType;
    double possibleProfit;
};

class ArbitrageCalculator {
public:
    ArbitrageCalculator(double thread_amount_php);
    void addCrypto(ICryptoBase* crypto);
    std::vector<ArbitrageResult> calculateArbitrage();
    std::vector<ICryptoBase*> cryptos() const;
private:
    std::vector<ICryptoBase*> m_cryptos;
    void calculateArbitrage(ICryptoBase* buyPlatform, std::vector<ArbitrageResult> &outResults);
    double m_trade_amount;
};

#endif // ARBITRAGECALCULATOR_H
