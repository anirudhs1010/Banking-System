#ifndef BANKING_SYSTEM_IMPL_HPP_
#define BANKING_SYSTEM_IMPL_HPP_

#include "banking_system.hpp"
#include <unordered_map>

class BankingSystemImpl : public BankingSystem {
        private:
                std::unordered_map<std::string, int> accounts;
        public:
                bool CreateAccount(int timestamp, const std::string&account_id);
                std::optional<int> Deposit(int timestamp, const std::string& account_id, int amount);
                std::optional<int> Transfer(int timestamp, const std::string& source_account_id, const std::string& target_account_id, int amount);  
                std::vector<std::string> TopSpenders(int timestamp, int n);   
};

#endif  // BANKING_SYSTEM_IMPL_HPP_
