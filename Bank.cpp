#include "Bank.h"
#include <algorithm>

Bank::Bank() : m_name(""), m_bankCode(0), m_totalBalance(0.0) {}

Bank::Bank(const std::string& name, int code) 
    : m_name(name), m_bankCode(code), m_totalBalance(0.0) {}

void Bank::SetBankName(const std::string& name) {
    m_name = name;
}

void Bank::SetCode(int code) {
    m_bankCode = code;
}

void Bank::SetTotal(double total) {
    m_totalBalance = total;
}

std::string Bank::GetBankName() const {
    return m_name;
}

int Bank::GetCode() const {
    return m_bankCode;
}

double Bank::GetTotal() const {
    std::lock_guard<std::mutex> lock(m_bankMutex);
    return m_totalBalance;
}

const std::vector<std::shared_ptr<Account>>& Bank::GetAccounts() const {
    return m_accounts;
}

void Bank::AddAccount(const Account& account) {
    std::lock_guard<std::mutex> lock(m_bankMutex);
    
    // בדיקה אם החשבון כבר קיים בבנק
    auto it = std::find_if(m_accounts.begin(), m_accounts.end(), [&](const auto& acc) {
        return acc->GetAccountNumber() == account.GetAccountNumber();
    });

    if (it != m_accounts.end()) return; // החשבון כבר קיים

    m_accounts.push_back(std::make_shared<Account>(account));
    m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person& per, double amount) {
    // יוצר חשבון חדש ישירות לתוך הוקטור
    auto newAccount = std::make_shared<Account>(per, amount);
    AddAccount(*newAccount);
}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {
    std::lock_guard<std::mutex> lock(m_bankMutex);
    
    for (auto& acc : m_accounts) {
        if (acc->GetAccountNumber() == account.GetAccountNumber()) {
            acc->AddPerson(newPerson, amount);
            m_totalBalance += amount;
            return;
        }
    }
    // אם החשבון לא נמצא, פותח חשבון חדש עבור האדם
    std::lock_guard<std::mutex> unlock(m_bankMutex); // משחרר זמנית לפני קריאה ל-AddAccount שנועלת בעצמה
    AddAccount(newPerson, amount);
}

void Bank::DeleteAccount(const Account& account) {
    std::lock_guard<std::mutex> lock(m_bankMutex);
    
    auto it = std::find_if(m_accounts.begin(), m_accounts.end(), [&](const auto& acc) {
        return acc->GetAccountNumber() == account.GetAccountNumber();
    });

    if (it != m_accounts.end()) {
        m_totalBalance -= (*it)->GetBalance();
        m_accounts.erase(it);
    }
}

void Bank::DeletePerson(const Person& p) {
    std::lock_guard<std::mutex> lock(m_bankMutex);
    
    for (auto it = m_accounts.begin(); it != m_accounts.end(); ) {
        auto& acc = *it;
        
        // מחיקת האדם מתוך החשבון הספציפי
        acc->DeletePerson(p);
        
        // אם לא נשארו אנשים המשוייכים לחשבון, נסגור את החשבון כולו
        if (acc->GetPersons().empty()) {
            m_totalBalance -= acc->GetBalance();
            it = m_accounts.erase(it); // מוחק ומקדם את האיטרטור בצורה בטוחה
        } else {
            ++it;
        }
    }
}