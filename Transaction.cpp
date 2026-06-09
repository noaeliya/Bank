#include "Transaction.h"
#include "Account.h"

Transaction::Transaction() : m_source(nullptr), m_destination(nullptr), m_amount(0.0), m_date("") {}

Transaction::Transaction(std::shared_ptr<Account> source, std::shared_ptr<Account> destination, double amount, const std::string& date)
    : m_source(source), m_destination(destination), m_amount(amount), m_date(date) {}

std::shared_ptr<Account> Transaction::GetSource() const { 
    return m_source; 
}

std::shared_ptr<Account> Transaction::GetDes() const { 
    return m_destination; 
}

double Transaction::GetAmount() const { 
    return m_amount; 
}

std::string Transaction::GetDate() const { 
    return m_date; 
}