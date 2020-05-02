#include <iostream>
#include <iomanip>
#include "BankCustomer.h"
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"

using namespace std;

BankCustomer::BankCustomer(int customerId, string firstName, string lastName)
{
	_firstName = firstName;
	_lastName = lastName;
	_customerId = customerId;
}

BankCustomer::~BankCustomer()
{
	map<int, BankAccount*>::iterator accts;
	
	for (accts = _accounts.begin(); accts != _accounts.end(); accts++)
	{
		delete (accts->second);
	}
}

// Return the bank account with the specified suffix, nullptr if the suffix is not found
BankAccount* BankCustomer::findAccount(int suffix)
{
	if (BankCustomer::_accounts.count(suffix))
	{
		return BankCustomer::_accounts[suffix];
	}
	
	return nullptr;
}


// Uses a linear search because it is more likely that the first of a type is at the beginning
BankAccount* BankCustomer::findFirstAccountOfType(AccountType accountType, int startingOffset)
{
	BankAccount* account = nullptr;
	int suffix = static_cast<int>(accountType);

	for (int offset = startingOffset; offset < 100; offset++)
	{
		if (BankCustomer::_accounts.count(suffix + offset) && BankCustomer::_accounts[suffix+offset]->getAccountType() == accountType)
		{
			account = BankCustomer::_accounts[suffix + offset];
			break;
		}
	}

	return account;
}

// If there is room for another account of the specified type return
// the next suffix for the specified account type, otherwise return 0
const int BankCustomer::getNextSuffixOfType(AccountType accountType)
{
	int lastSuffix = static_cast<int>(accountType);

	for (int i = 0; i < 100; i++)
	{
		lastSuffix += i;
		if (!BankCustomer::_accounts.count(lastSuffix))
		{
			return lastSuffix;
		}
	}

	// Max account reached for this account type
	return 0;
}

int BankCustomer::createAccount(AccountType accountType, double startingBalance, double annualInterestRate)
{
	int suffix = BankCustomer::getNextSuffixOfType(accountType);

	// If suffix is 0 then customer has max # of accounts of the specified type
	if (suffix)
	{
		int offset = suffix - static_cast<int>(accountType);
		switch (accountType)
		{
		case AccountType::Savings:
			BankCustomer::_accounts[suffix] = new SavingAccount(startingBalance, annualInterestRate, offset);
			break;
		case AccountType::Checkings:
			BankCustomer::_accounts[suffix] = new CheckingAccount(startingBalance, annualInterestRate, offset);
			break;
		}
	}
	
	return suffix;
}

void BankCustomer::deleteAccount(int suffix)
{
	if (_accounts.count(suffix))
	{
		delete _accounts[suffix];
		BankCustomer::_accounts.erase(suffix);
	}
}

// Returns the specified account if it exists, otherwise returns nullptr
BankAccount* BankCustomer::getAccount(int suffix)
{
	BankAccount* account = nullptr;

	if (BankCustomer::_accounts.count(suffix))
	{
		account = BankCustomer::_accounts[suffix];
	}

	return account;
}

void BankCustomer::DisplayCustomerInfo()
{
	cout << "Cust Name: " << this->getFullName() << endl;
	cout << "Account #: " << this->getCustomerId() << endl;
	cout << "Num Accounts: " << this->getNumAccounts() << endl << endl;
}

void BankCustomer::DisplaySavingsAccounts()
{
	SavingAccount* acct = this->getFirstSavingAccount();
	cout << "Saving Accounts\n";

	if (acct == nullptr)
	{
		cout << "You have no saving accounts with us.\n";
	}
	else
	{
		// Display table header
		cout << setw(ACCOUNT_WIDTH) << left << "Account #" <<
			setw(DESC_WIDTH) << left << "Description" <<
			setw(BALANCE_WIDTH) << "Balance" <<
			setw(7) << " APR" <<
			"Status\n";

		cout << string(ACCOUNT_WIDTH + DESC_WIDTH + BALANCE_WIDTH + STATUS_WIDTH + APR_WIDTH, '-') << endl;
		// Display data
		do
		{
			cout << setw(ACCOUNT_WIDTH) << left << acct->getAccountNumber(this->getCustomerId());
			cout << setw(DESC_WIDTH) << left << acct->getDescription();
			cout << "$" << setw(BALANCE_WIDTH) << left << fixed << setprecision(2) << acct->getBalance();
			cout << setw(APR_WIDTH) << left << fixed << setprecision(2) << acct->getAnnualInterestRate();
			cout << setw(STATUS_WIDTH) << left << acct->getStatusCode() << endl;

			acct = this->getNextSavingAccount(acct->getAccountOffset());
		} while (acct != nullptr);
	}

	cout << endl << endl;
}

void BankCustomer::DisplayCheckingsAccounts()
{
	CheckingAccount* acct = this->getFirstCheckingAccount();
	
	cout << "Checking Accounts\n";

	if (acct == nullptr)
	{
		cout << "You have no checking accounts with us.\n";
	}
	else
	{
		// Display table header
		cout << setw(ACCOUNT_WIDTH) << left << "Account #" <<
			setw(DESC_WIDTH) << left << "Description" <<
			setw(BALANCE_WIDTH) << "Balance" <<
			" APR\n";
		cout << string(ACCOUNT_WIDTH + DESC_WIDTH + BALANCE_WIDTH + APR_WIDTH, '-') << endl;

		// Display data
		do
		{
			cout << setw(ACCOUNT_WIDTH) << left << acct->getAccountNumber(this->getCustomerId());
			cout << setw(DESC_WIDTH) << left << acct->getDescription();
			cout << "$" << setw(BALANCE_WIDTH) << left << fixed << setprecision(2) << acct->getBalance();
			cout << left << fixed << setprecision(2) << acct->getAnnualInterestRate() << endl;

			acct = this->getNextCheckingAccount(acct->getAccountOffset());
		} while (acct != nullptr);
	}

	cout << endl << endl;
}