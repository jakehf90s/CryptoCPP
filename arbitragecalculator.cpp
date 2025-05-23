#include "arbitragecalculator.h"
#include <cmath>
#include "cryptobinance.h"

ArbitrageCalculator::ArbitrageCalculator(double thread_amount_php): m_trade_amount(thread_amount_php)
{

}

void ArbitrageCalculator::addCrypto(ICryptoBase* crypto) {
    m_cryptos.push_back(crypto);
}

void ArbitrageCalculator::calculateArbitrage(ICryptoBase* buyPlatform, std::vector<ArbitrageResult>& outResults)
{
    double fiatRate = buyPlatform->getFiatRate(); // USDT to PHP conversion

    for (ICryptoBase* sellPlatform : m_cryptos) {
        if (buyPlatform == sellPlatform) return; //skip, its the sample platform

        const auto& prices = sellPlatform->getAllPrices();

        for (const auto& [symbol, sellRate] : prices) {
            if (sellRate <= 0) continue;

            double refRate = buyPlatform->getReferenceRate(symbol); // crypto to USDT conversion
            if (refRate <= 0) continue;

            double usdt = m_trade_amount / fiatRate;
            usdt *= (1.0 - buyPlatform->getTradeFee());

            double cryptoAmount = usdt / refRate;
            cryptoAmount -= sellPlatform->getDepositFee();

            double phpReceived = cryptoAmount * sellRate;
            phpReceived *= (1.0 - sellPlatform->getTradeFee());
            phpReceived -= sellPlatform->getWithdrawalFee() * sellRate;

            double profit = phpReceived - m_trade_amount;

            ArbitrageResult result;
            result.buyCrypto = buyPlatform;
            result.buyCryptoType = symbol;
            result.sellCrypto = sellPlatform;
            result.sellCryptoType = sellPlatform->name();
            result.possibleProfit = profit;

            outResults.push_back(result);
        }
    }
}

std::vector<ArbitrageResult> ArbitrageCalculator::calculateArbitrage()
{
    std::vector<ArbitrageResult> results;
    for (ICryptoBase* cryptoNow: m_cryptos) {
        calculateArbitrage(cryptoNow, results);
    }
    return results;
}

std::vector<ICryptoBase *> ArbitrageCalculator::cryptos() const
{
    return m_cryptos;
}
