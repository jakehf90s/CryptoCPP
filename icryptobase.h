#ifndef ICRYPTOBASE_H
#define ICRYPTOBASE_H

#include <string>
#include <map>

class ICryptoBase {
public:
    virtual ~ICryptoBase() = default;
    virtual std::string name() const = 0;
    virtual double getBTCPHP();
    virtual void runParser() = 0;

    // Fee setters
    void setTradeFee(double feePercent);
    void setWithdrawalFee(double fee);
    void setDepositFee(double fee);

    // Fee getters
    double getTradeFee() const;
    double getWithdrawalFee() const;
    double getDepositFee() const;

    // Price management
    void addCryptoPrice(const std::string& symbol, double price);
    double getCryptoPrice(const std::string& symbol) const;
    const std::map<std::string, double>& getAllPrices() const;

    // Reference rate: e.g. BTC → USDT
    void setReferenceRate(const std::string& symbol, double price);
    double getReferenceRate(const std::string& symbol) const;

    // Fiat rate: USDT → PHP (Binance P2P)
    void setFiatRate(double rate);
    double getFiatRate() const;

protected:
    double tradeFee = 0.0;
    double withdrawalFee = 0.0;
    double depositFee = 0.0;

    std::map<std::string, double> cryptoPrices;
    std::map<std::string, double> referenceRates;
    double fiatRate = 0.0; // e.g. USDT to PHP
};

#endif // ICRYPTOBASE_H
