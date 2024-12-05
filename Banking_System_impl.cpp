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
std::vector<std::string> BankingSystemImpl::TopSpenders(int timestamp, int n) {
    // Create a vector to store accounts with their outgoing amounts
    std::vector<std::pair<std::string, int>> spenders;

    // Iterate through all accounts and calculate total outgoing transactions
    for (const auto& account : accounts) {
        const std::string& account_id = account.first;
        int outgoing = 0;

        // Assuming a data structure `transactions` that stores outgoing transfers
        if (accounts.find(account_id) != accounts.end()) {
            outgoing = accounts[account_id]; // Total outgoing for this account
        }

        // Add the account and its outgoing amount to the vector
        spenders.emplace_back(account_id, outgoing);
    }

    // Sort the spenders vector based on outgoing amount in descending order
    // If there is a tie, sort alphabetically by account_id
    std::sort(spenders.begin(), spenders.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first < b.first; // Alphabetical order if outgoing amounts are equal
        }
        return a.second > b.second; // Descending order of outgoing amounts
    });

    // Prepare the result vector with the top n spenders
    std::vector<std::string> result;
    for (size_t i = 0; i < std::min(n, static_cast<int>(spenders.size())); ++i) {
        result.push_back(spenders[i].first + "(" + std::to_string(spenders[i].second) + ")");
    }

    return result;
}
