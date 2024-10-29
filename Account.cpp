#include "Account.h"

Account :: Account() {
	m_persons = NULL;
	m_transactionList = NULL;//מערך של כל הפעולות בחשבון
	m_numberOfTransaction = 0;//מספר פעולות בחשבון 
	m_totalPersons = 0;//כמות אנשים בחשבון
	m_accountNumber = 0;//מספר החשבון 
	m_balance = 0;//מצב עובר ושב - סכום כסף
}

Account::Account(Person** persons, int count, double balance) 
{
	m_numberOfTransaction = 0;
	m_totalPersons = count;
	SetPersons(persons, count);//רשימת אנשים לחשבון
	SetBalance(balance);
	SetTransactions(NULL, 0);
	for (int i = 0; i < m_totalPersons; i++) {
		m_accountNumber += m_persons[i]->GetId();
	}
}

Account::Account(const Person& person, double balance) {
	m_totalPersons = 1;
	m_persons = new Person * [m_totalPersons];
	m_persons[0] = new Person(person);

	SetBalance(balance);
	m_transactionList = NULL;
	m_numberOfTransaction = 0;

	m_accountNumber = person.GetId();
}

Account::Account(const Account& other) {

	m_accountNumber = other.m_accountNumber;
	m_numberOfTransaction = 0;
	//m_totalPersons = 0;
	m_persons = NULL;
	m_transactionList = NULL;
	SetPersons(other.m_persons, other.m_totalPersons);
	SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
	m_balance = other.m_balance;
	
}

Account ::~Account() {
	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		delete m_transactionList[i];
	}
	delete[] m_transactionList;
	m_transactionList = NULL;
	m_numberOfTransaction = 0;

	for (int i = 0; i < m_totalPersons; i++)
	{
		delete m_persons[i];
	}
	delete[] m_persons;
	m_persons = NULL;
	m_totalPersons = 0;
}

void Account::SetPersons(Person** persons, int count) {
	clearPersons();

	m_persons = new Person*[count];
	for (int i = 0; i < count; i++)
	{
		m_persons[i] = persons[i];
	}
	m_totalPersons = count;
}
void Account::SetAccountNumber(int number){
	m_accountNumber = number;
}
void Account::SetBalance(double balance) {
	m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count) {
	clearTransactions();

	m_transactionList = new Transaction * [count];
	for (int i = 0; i < count; i++)
	{
		m_transactionList[i] = newTransaction[i];
	}
	m_numberOfTransaction = count;
}

Transaction** Account::GetTransactions() { return m_transactionList; }
int	Account::GetNumOfTransactions() { return m_numberOfTransaction;  }
Person** Account::GetPersons() const { return m_persons; }
int	Account::GetTotalPersons()const { return m_totalPersons; }
int	Account::GetAccountNumber() const { return m_accountNumber; }
double Account::GetBalance() const { return m_balance; }

void Account::Withdraw(double amount, const char* date) {
	Transaction* t = new Transaction(this, this, amount, date);
	Transaction** temp = new Transaction * [m_numberOfTransaction + 1];
	for (int i = 0; i < m_numberOfTransaction; i++) {
		temp[i] = m_transactionList[i];
	}
	delete[] m_transactionList;
	m_transactionList = temp;
	m_transactionList[m_numberOfTransaction] = t;
	m_transactionList++;
	this->SetBalance(m_balance-amount);
}
void Account::Deposit(double amount, const char* date) {
	Transaction* t = new Transaction(this, this, amount, date);
	Transaction** temp = new Transaction * [m_numberOfTransaction + 1];

	for (int i = 0; i < m_numberOfTransaction; i++) {
		temp[i] = m_transactionList[i];
	}
	delete[] m_transactionList;
	m_transactionList = temp;
	m_transactionList[m_numberOfTransaction] = t;
	m_numberOfTransaction++;
	this->SetBalance(m_balance + amount);
	//delete[] temp;?
}
void Account:: AddPerson(const Person& newPerson, double amount) {
	for (int i = 0; i < m_totalPersons; i++) {
		if (newPerson.GetId() == m_persons[i]->GetId())
			return;
	}

	Person** temp = new Person * [m_totalPersons + 1];
	for (int i = 0; i < m_totalPersons; i++)
	{
		temp[i] = m_persons[i];
	}
	temp[m_totalPersons] = new Person(newPerson); 
	m_totalPersons++;
	delete[] m_persons;
	m_persons = temp;
	m_balance += amount;
}

void Account::DeletePerson(const Person& oldPerson)
{
	if (m_totalPersons == 1 && m_persons[0]->GetId() == oldPerson.GetId())
	{
		clearPersons();
		return;
	}
	for (int i = 0; i < m_totalPersons; i++)
	{
		if (m_persons[i]->GetId() == oldPerson.GetId())
		{
			for (int j = i; j < m_totalPersons - 1; j++)
			{
				m_persons[j] = new Person(*m_persons[j + 1]);
			}
			m_totalPersons--;
			SetPersons(m_persons, m_totalPersons);
		}
	}
	return;
}

void Account::AddTransaction(const Transaction& newTransaction)
{
	Account* des = newTransaction.GetDes();
	Account* src = newTransaction.GetSource();

	// transaction for m_source

	Transaction** temp = new Transaction * [des->m_numberOfTransaction + 1];
	for (int i = 0; i < des->m_numberOfTransaction; i++) {
		temp[i] = des->m_transactionList[i];
	}
	temp[des->m_numberOfTransaction] = new Transaction(newTransaction);
	delete[] des->m_transactionList;
	des->m_transactionList = temp;
	des->m_numberOfTransaction++;
	des->SetBalance(des->m_balance + newTransaction.GetAmount());

	//  transaction for m_destination
	Transaction** temp2 = new Transaction * [src->m_numberOfTransaction + 1];
	for (int i = 0; i < src->m_numberOfTransaction; i++) {
		temp2[i] = src->m_transactionList[i];
	}
	temp2[src->m_numberOfTransaction] = new Transaction(newTransaction);
	delete[] src->m_transactionList;
	src->m_transactionList = temp;
	src->m_numberOfTransaction++;
	src->SetBalance(src->m_balance - newTransaction.GetAmount());
}

void Account::clearTransactions() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = NULL;
	}
	m_transactionList = nullptr;
}
void Account::clearPersons() {
	for (int i = 0; i < m_totalPersons; i++) {
		m_persons[i] = NULL;
	}
	m_persons = nullptr;
}
