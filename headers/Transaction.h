#pragma once
#include <string>
#include <memory>

// הצהרה קדימה (Forward Declaration) כדי למנוע מעגליות כיוון ש-Account מכיל Transaction
class Account; 

class Transaction {
private:
    std::shared_ptr<Account> m_source;
    std::shared_ptr<Account> m_destination;
    double m_amount;
    std::string m_date;

public:
    // בנאים
    Transaction();
    Transaction(std::shared_ptr<Account> source, std::shared_ptr<Account> destination, double amount, const std::string& date);
    Transaction(const Transaction& other) = default; // בנאי העתקה אוטומטי ותקין
    ~Transaction() = default;

    // Getters
    std::shared_ptr<Account> GetSource() const;
    std::shared_ptr<Account> GetDes() const;
    double GetAmount() const;
    std::string GetDate() const;
};