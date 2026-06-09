#pragma once
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include "Account.h"
#include "Person.h"

class Bank {
private:
    std::string m_name;
    // וקטור שמנהל בצורה אוטומטית ובטוחה את כל החשבונות בבנק
    std::vector<std::shared_ptr<Account>> m_accounts;
    int m_bankCode;
    double m_totalBalance;

    // Mutex להגנה על פעולות הבנק (הוספה/מחיקה של חשבונות) בריצה מרובת תהליכונים
    mutable std::mutex m_bankMutex;

public:
    // בנאים ומפרק
    Bank();
    Bank(const std::string& name, int code);
    ~Bank() = default; // ה-vector וה-string משחררים את עצמם, אין צורך ב-delete ידני

    // פונקציות ניהול חשבונות (משודרגות ל-Thread-Safe)
    void AddAccount(const Account& account);
    void AddAccount(const Person& per, double amount);
    void AddPerson(const Person& newPerson, const Account& account, double amount);
    void DeleteAccount(const Account& account);
    void DeletePerson(const Person& p);

    // Getters ו-Setters מודרניים
    void SetBankName(const std::string& name);
    void SetCode(int code);
    void SetTotal(double total);

    std::string GetBankName() const;
    int GetCode() const;
    double GetTotal() const;
    const std::vector<std::shared_ptr<Account>>& GetAccounts() const;
};