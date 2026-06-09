#include <iostream>
#include <thread>
#include <vector>
#include "Bank.h"
#include "Account.h"
#include "Person.h"

// פונקציה שתורץ על ידי התהליכונים במקביל
void SimulationDeposit(std::shared_ptr<Account> account, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        account->Deposit(10.0, "09/06/2026"); // הפקדה של 10 שקלים בכל פעם
    }
}

int main() {
    std::cout << "--- Starting Bank Simulation ---" << std::endl;

    // 1. יצירת בנק ולקוח
    Bank myBank("Leumi", 10);
    Person customer("Yossi", 123456);

    // 2. פתיחת חשבון חדש עם יתרה התחלתית של 0
    myBank.AddAccount(customer, 0.0);
    
    // שליפת החשבון שיצרנו מתוך הוקטור של הבנק
    auto accounts = myBank.GetAccounts();
    if (accounts.empty()) {
        std::cerr << "Error: Account was not created!" << std::endl;
        return 1;
    }
    auto sharedAccount = accounts[0];

    std::cout << "Initial Balance: " << sharedAccount->GetBalance() << " ILS" << std::endl;

    // 3. יצירת שני תהליכונים שיגשו לאותו החשבון במקביל
    int actionsPerThread = 1000;
    
    // תהליכון 1 - כספומט
    std::thread atmThread(SimulationDeposit, sharedAccount, actionsPerThread);
    
    // תהליכון 2 - אפליקציה
    std::thread mobileThread(SimulationDeposit, sharedAccount, actionsPerThread);

    // 4. המשגר (main) מחכה ששני התהליכונים יסיימו את עבודתם (Join)
    atmThread.join();
    mobileThread.join();

    // 5. בדיקת היתרה הסופית
    std::cout << "--- Simulation Finished ---" << std::endl;
    std::cout << "Expected Balance: " << (actionsPerThread * 2 * 10.0) << " ILS" << std::endl;
    std::cout << "Actual Balance:   " << sharedAccount->GetBalance() << " ILS" << std::endl;

    return 0;
}