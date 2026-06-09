#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <memory>
#include "Person.h"
#include "Transaction.h"

class Account {
private:
    // שימוש ב-vector פותר לחלוטין את ניהול הזיכרון הידני והצורך במשתני count/size
    std::vector<std::shared_ptr<Person>> m_persons;
    std::vector<std::shared_ptr<Transaction>> m_transactionList;
    
    int m_accountNumber;
    double m_balance;
    
    // Mutex להגנת היתרה והפעולות בחשבון במצב של Multi-threading
    mutable std::mutex m_accountMutex;

public:
    Account();
    Account(const std::vector<std::shared_ptr<Person>>& persons, double balance);
    Account(const Person& person, double balance);
    Account(const Account& other); 
    // אין יותר צורך ב-Destructor, Copy Constructor או Assignment Operator ידניים!
    // ה-vector והמחלקות המודרניות מנהלים את הזיכרון בעצמם (Rule of Zero).
    ~Account() = default;

    // מריצים פעולות בצורה בטוחה (Thread-Safe)
    void Withdraw(double amount, const std::string& date);
    void Deposit(double amount, const std::string& date);
    
    void AddPerson(const Person& newPerson, double amount);
    void DeletePerson(const Person& oldPerson);

    // Getters ו-Setters מודרניים
    double GetBalance() const;
    int GetAccountNumber() const;
    const std::vector<std::shared_ptr<Person>>& GetPersons() const;
    const std::vector<std::shared_ptr<Transaction>>& GetTransactions() const;
};