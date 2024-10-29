#include "Bank.h"

Bank::Bank() {
    m_name = NULL;;
    m_account = NULL;
    m_bankCode = 0;;
    m_numbeOfAccounts = 0;
    m_totalBalance = 0;
}

Bank::Bank(const char* name, int code) {
    SetBankName(name);
    SetCode(code);
    SetAccount(NULL,0);
    SetTotal(0);
    m_numbeOfAccounts = 0;
}

Bank::~Bank() {
    delete m_name; m_numbeOfAccounts;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        delete m_account[i];
    }
    delete m_account;
    m_account = NULL;
    m_numbeOfAccounts = 0;
}

void Bank::SetBankName(const char* name) {
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

void Bank::SetAccount(Account** account, int numbeOfAccounts) {
    for (int i = 0; i < numbeOfAccounts; i++) {
        m_account[i] = account[i];
    }
    m_numbeOfAccounts = numbeOfAccounts;
}

void Bank::SetTotal(double total) {
    m_totalBalance = total;
}

void Bank::SetCode(int code) {
    m_bankCode = code;
}

const char* Bank::GetBankName() const {
    return m_name;
}

Account** Bank::GetAccounts() const {
    return m_account;
}

int	Bank::GetNumberOfAccounts() const {
    return m_numbeOfAccounts;
}

double Bank::GetTotal() const {
    return m_totalBalance;
}

int	Bank::GetCode() const {
    return m_bankCode;
}

void Bank::AddAccount(const Account& account) {
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (account.GetAccountNumber() == m_account[i]->GetAccountNumber())
            return;
    }

    Account** temp = new Account * [m_numbeOfAccounts + 1];
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        temp[i] = m_account[i];
    }
    temp[m_numbeOfAccounts] = new Account(account);
    m_numbeOfAccounts++;
    delete[] m_account;
    m_account = temp;
    m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person& per, double amount) 
 {
        Account* account = new Account(per, amount);
        AddAccount(*account);
 };//open an account for a person using an account copy constarctor,
    //and then add their account to the set of accounts in the bank


void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (account.GetAccountNumber() == m_account[i]->GetAccountNumber())
        {
            m_account[i]->AddPerson(newPerson, amount);
            m_totalBalance += amount;
            return;
        }
    }
    AddAccount(newPerson, amount);
}
  

void Bank::DeleteAccount(const Account& account)
{
	if (m_numbeOfAccounts == 1 && m_account[0]->GetAccountNumber() == account.GetAccountNumber())
	{
		m_account[0] = NULL;
		delete[] m_account;
		return;
	}
	for (int i = 0; i < m_numbeOfAccounts; i++)
	{
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
		{
			for (int j = i; j < m_numbeOfAccounts - 1; j++)
			{
				m_account[j] = m_account[j + 1];
			}
			m_numbeOfAccounts--;
			SetTotal(m_totalBalance - account.GetBalance());
			break;
		}
	}
	return;
}
void Bank::DeletePerson(const Person& p)
{
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {


        if (m_account[i]->GetPersons()[m_account[i]->GetTotalPersons() - 1]->GetId() == p.GetId())
        {
            DeleteAccount(*m_account[i]);
            break;
        }

        m_account[i]->DeletePerson(p);

        if (m_account[i]->GetTotalPersons() == 0)
        {
            DeleteAccount(*m_account[i]);
        }
    }
}