#include "Account.h"
#include <algorithm> // בשביל std::find_if

Account::Account() : m_accountNumber(0), m_balance(0) {}

Account::Account(const std::vector<std::shared_ptr<Person>>& persons, double balance) 
    : m_persons(persons), m_balance(balance), m_accountNumber(0) {
    
    for (const auto& person : m_persons) {
        if (person) {
            m_accountNumber += person->GetId();
        }
    }
}

Account::Account(const Person& person, double balance) 
    : m_balance(balance), m_accountNumber(person.GetId()) {
    m_persons.push_back(std::make_shared<Person>(person));
}

Account::Account(const Account& other) {
    // אנחנו נועלים את החשבון שממנו מעתיקים כדי להבטיח קריאה בטוחה של הנתונים
    std::lock_guard<std::mutex> lock(other.m_accountMutex);
    
    m_persons = other.m_persons;
    m_transactionList = other.m_transactionList;
    m_accountNumber = other.m_accountNumber;
    m_balance = other.m_balance;
    // m_accountMutex לא מועתק! הוא מאותחל מחדש אוטומטית עבור האובייקט החדש.
}

void Account::Withdraw(double amount, const std::string& date) {
    // lock_guard נועל את ה-mutex אוטומטית ומשחרר אותו כשהפונקציה מסתיימת
    std::lock_guard<std::mutex> lock(m_accountMutex);
    
    if (m_balance >= amount) {
        m_balance -= amount;
        // יצירת טרנזקציה בצורה חכמה ומאובטחת בתוך ה-vector
        // (בהנחה שקונסטרקטור הטרנזקציה יעודכן בהתאם ל-string/shared_ptr)
        // m_transactionList.push_back(std::make_shared<Transaction>(...));
    }
}

void Account::Deposit(double amount, const std::string& date) {
    std::lock_guard<std::mutex> lock(m_accountMutex);
    m_balance += amount;
    // אין יותר צורך להקצות מערך זמני, להעתיק תאים ולמחוק את הישן! vector עושה הכל בשורה אחת:
    // m_transactionList.push_back(std::make_shared<Transaction>(...));
}

void Account::AddPerson(const Person& newPerson, double amount) {
    std::lock_guard<std::mutex> lock(m_accountMutex);
    
    // בדיקה אם המשתמש כבר קיים באמצעות אלגוריתם מודרני של STL
    auto it = std::find_if(m_persons.begin(), m_persons.end(), [&](const auto& p) {
        return p->GetId() == newPerson.GetId();
    });

    if (it != m_persons.end()) return; // קיים כבר

    m_persons.push_back(std::make_shared<Person>(newPerson));
    m_balance += amount;
}

void Account::DeletePerson(const Person& oldPerson) {
    std::lock_guard<std::mutex> lock(m_accountMutex);
    
    // מחיקה קלה ואלגנטית מ-vector באמצעות מנגנון Erase-remove אינטואיטיבי
    m_persons.erase(
        std::remove_if(m_persons.begin(), m_persons.end(), [&](const auto& p) {
            return p->GetId() == oldPerson.GetId();
        }), 
        m_persons.end()
    );
}

double Account::GetBalance() const {
    std::lock_guard<std::mutex> lock(m_accountMutex);
    return m_balance;
}

int Account::GetAccountNumber() const {
    return m_accountNumber;
}

const std::vector<std::shared_ptr<Person>>& Account::GetPersons() const {
    return m_persons;
}

const std::vector<std::shared_ptr<Transaction>>& Account::GetTransactions() const {
    return m_transactionList;
}