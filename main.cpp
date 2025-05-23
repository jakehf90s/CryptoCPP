#include <QCoreApplication>
#include "cryptocoins.h"
#include "cryptobinance.h"
#include "arbitragecalculator.h"
#include "defines.h"
#include <iostream>
#include <thread>

//forward declare
void addCoinsPH(ArbitrageCalculator &arbitrageCalculator);
void addBinance(ArbitrageCalculator &arbitrageCalculator);


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ArbitrageCalculator arbitrageCalculator(TRADE_MONEY);
    addCoinsPH(arbitrageCalculator);
    addBinance(arbitrageCalculator);

    while (true) {
        std::cout << "\n=== Arbitrage Check ===\n";

        // Run price fetches in parallel so prices are fetched on the same time
        std::vector<std::thread> threads;
        for (ICryptoBase* crypto : arbitrageCalculator.cryptos()) {
            threads.emplace_back([crypto]() {
                crypto->runParser();
            });
        }
        for (std::thread& thread : threads) {
            thread.join();
        }

        // Arbitrage calculation
        auto results = arbitrageCalculator.calculateArbitrage();
        if (results.empty())
            std::cout << "No arbitrage detected, retrying in "
                      << LOOP_DELAY_MS / 1000
                      << " seconds...\n";

        for (const ArbitrageResult& result : results) {
            if (result.possibleProfit > 0) {
                std::cout << "[+] " << result.buyCryptoType
                          << " → " << result.sellCryptoType
                          << " | Profit: ₱" << result.possibleProfit << "\n";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_DELAY_MS));
    }

    return 0;
}




void addCoinsPH(ArbitrageCalculator &arbitrageCalculator)
{
    CryptoCoins* coins = new CryptoCoins("Coins.ph");
    coins->setTradeFee(0.005);
    coins->setDepositFee(0.0);
    coins->setWithdrawalFee(0.0016);
    arbitrageCalculator.addCrypto(coins);
}

void addBinance(ArbitrageCalculator &arbitrageCalculator)
{
    CryptoBinance* binance = new CryptoBinance("Binance");
    binance->setTradeFee(0.001);
    binance->setDepositFee(0.0);
    binance->setWithdrawalFee(0.0);
    arbitrageCalculator.addCrypto(binance);
}
