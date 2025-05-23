#include "icryptobase.h"


void ICryptoBase::setTradeFee(double feePercent) { tradeFee = feePercent; }
void ICryptoBase::setWithdrawalFee(double fee)   { withdrawalFee = fee; }
void ICryptoBase::setDepositFee(double fee)      { depositFee = fee; }

double ICryptoBase::getTradeFee() const { return tradeFee; }
double ICryptoBase::getWithdrawalFee() const { return withdrawalFee; }
double ICryptoBase::getDepositFee() const { return depositFee; }


void ICryptoBase::addCryptoPrice(const std::string& symbol, double price) {
    cryptoPrices[symbol] = price;
}

double ICryptoBase::getCryptoPrice(const std::string& symbol) const {
    auto it = cryptoPrices.find(symbol);
    return it != cryptoPrices.end() ? it->second : 0.0;
}

const std::map<std::string, double>& ICryptoBase::getAllPrices() const {
    return cryptoPrices;
}

double ICryptoBase::getBTCPHP() { return getCryptoPrice("BTC"); }


void ICryptoBase::setReferenceRate(const std::string& symbol, double price) {
    referenceRates[symbol] = price;
}
double ICryptoBase::getReferenceRate(const std::string& symbol) const {
    auto it = referenceRates.find(symbol);
    return it != referenceRates.end() ? it->second : 0.0;
}


void ICryptoBase::setFiatRate(double rate) { fiatRate = rate; }
double ICryptoBase::getFiatRate() const { return fiatRate; }
