#include "banking_system_impl.hpp"

// TODO: implement interface methods here
std::unordered_map<std::string, int> accounts;
bool BankingSystemImpl::CreateAccount(int timestamp, const std::string& account_id) {
    if (accounts.find(account_id) != accounts.end())
        return false;
    accounts[account_id] = 0;
    return true;
}

std::optional<int> BankingSystemImpl::Deposit(int timestamp, const std::string& account_id, int amount) {
    if (accounts.find(account_id) == accounts.end()) {
        return std::nullopt;
    }
    accounts[account_id] += amount;
    return accounts[account_id];
}

std::optional<int> BankingSystemImpl::Transfer(int timestamp, const std::string& source_account_id, const std::string& target_account_id, int amount) {
    if (accounts.find(source_account_id) == accounts.end() || accounts.find(target_account_id) == accounts.end()) {
        return std::nullopt;
    }
    if (source_account_id == target_account_id)
        return std::nullopt;
    if (accounts[source_account_id] < amount)
        return std::nullopt;
    
    accounts[source_account_id] -= amount;
    accounts[target_account_id] += amount;
    return accounts[source_account_id];
}
