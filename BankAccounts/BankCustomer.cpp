#include <iostream>
#include <iomanip>
#include "BankCustomer.h"
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"

using namespace std;

// Constructor
BankCustomer::BankCustomer(int customerNum, string firstName, string lastName)
{
	_firstName = firstName;
	_lastName = lastName;
	_customerNum = customerNum;
}

// Destructor - Needed to release the memory allocated for the customers bank accounts
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
BankAccount* BankCustomer::findNextAccountOfType(AccountType accountType, int startingOffset)
{
	BankAccount* account = nullptr;

	if (accountType != AccountType::Invalid)
	{
		int suffix = static_cast<int>(accountType);

		// Use a linear search for bank account because the # of accounts is small
		for (int offset = startingOffset + 1; offset < 100; offset++)
		{
			if (BankCustomer::_accounts.count(suffix + offset) && BankCustomer::_accounts[suffix + offset]->getAccountType() == accountType)
			{
				account = BankCustomer::_accounts[suffix + offset];
				break;
			}
		}
	}

	return account;
}

// If there is room for another account of the specified type return
// the next suffix for the specified account type, otherwise return 0
const int BankCustomer::getNextSuffixOfType(AccountType accountType)
{
	int lastSuffix = static_cast<int>(accountType);

	// Find the next account suffix using a linear search because the 
	// list is small.
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

// Create the customers bank account
int BankCustomer::createSubAccount(AccountType accountType, double startingBalance, double annualInterestRate)
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
	else
	{
		suffix = 0;
	}
	
	return suffix;
}

// Delete the specified account
void BankCustomer::deleteSubAccount(int suffix)
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

// Display the customer's information
void BankCustomer::displayCustomerInfo()
{
	cout << "CUSTOMER INFORMATION\n";
	cout << "Cust Name: " << this->getFullName() << endl;
	cout << "Account #: " << this->getAccountNum() << endl;
	cout << "Num Accounts: " << this->getNumAccounts() << endl << endl;
}

// Display the customer's address
void BankCustomer::displayCustomerAddr()
{
	cout << "CUSTOMER ADDRESS\n";
	cout << "Address 1: " << getAddress1() << endl;
	cout << "Address 2: " << getAddress2() << endl;
	cout << "City: " << getCity() << endl;
	cout << "State: " << getState() << endl;
	cout << "Zip: " << getZipCode() << endl << endl;
}

// Display all the customer's savings accounts
void BankCustomer::displaySavingsAccounts()
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
		displayAccountHeader(AccountType::Savings);

		// Display data
		do
		{
			displayAccountInfo(acct);

			acct = this->getNextSavingAccount(acct->getAccountOffset());
		} while (acct != nullptr);
	}

	cout << endl << endl;
}

// Display all the customer's checking accounts
void BankCustomer::displayCheckingsAccounts()
{
	CheckingAccount* acct = getFirstCheckingAccount();
	
	cout << "Checking Accounts\n";

	if (acct == nullptr)
	{
		cout << "You have no checking accounts with us.\n";
	}
	else
	{
		// Display table header
		displayAccountHeader(AccountType::Checkings);

		// Display data
		do
		{
			displayAccountInfo(acct);

			acct = this->getNextCheckingAccount(acct->getAccountOffset());
		} while (acct != nullptr);
	}

	cout << endl << endl;
}

// Display a header for account data
void BankCustomer::displayAccountHeader(AccountType accountType)
{
	if (accountType == AccountType::Checkings)
	{
		cout << setw(ACCOUNT_WIDTH) << left << "Account #" <<
			setw(DESC_WIDTH) << left << "Description" <<
			setw(BALANCE_WIDTH) << "Balance" <<
			" APR\n";
		cout << string(ACCOUNT_WIDTH + DESC_WIDTH + BALANCE_WIDTH + APR_WIDTH, '-') << endl;
	}
	else if (accountType == AccountType::Savings)
	{
		cout << setw(ACCOUNT_WIDTH) << left << "Account #" <<
			setw(DESC_WIDTH) << left << "Description" <<
			setw(BALANCE_WIDTH) << "Balance" <<
			setw(7) << " APR" <<
			"Status\n";

		cout << string(ACCOUNT_WIDTH + DESC_WIDTH + BALANCE_WIDTH + STATUS_WIDTH + APR_WIDTH, '-') << endl;
	}
}

// Display checking account data
void BankCustomer::displayAccountInfo(CheckingAccount* acct)
{
	if (acct != nullptr)
	{
		cout << setw(ACCOUNT_WIDTH) << left << acct->getAccountNumber(this->getAccountNum());
		cout << setw(DESC_WIDTH) << left << acct->getDescription();
		cout << "$" << setw(BALANCE_WIDTH) << left << fixed << setprecision(2) << acct->getBalance();
		cout << left << fixed << setprecision(2) << acct->getAnnualInterestRate() << endl;
	}
}

// Display saving account data
void BankCustomer::displayAccountInfo(SavingAccount* acct)
{
	if (acct != nullptr)
	{
		cout << setw(ACCOUNT_WIDTH) << left << acct->getAccountNumber(this->getAccountNum());
		cout << setw(DESC_WIDTH) << left << acct->getDescription();
		cout << "$" << setw(BALANCE_WIDTH) << left << fixed << setprecision(2) << acct->getBalance();
		cout << setw(APR_WIDTH) << left << fixed << setprecision(2) << acct->getAnnualInterestRate();
		cout << setw(STATUS_WIDTH) << left << acct->getStatusCode() << endl;
	}
}

// Display bank account data for the specified suffix
void BankCustomer::displayAccountInfo(int suffix)
{
	AccountType accountType = BankAccount::identifyAccountType(suffix);
	if (accountType == AccountType::Invalid)
	{
		cout << "Invalid account type\n";
		return;
	}

	cout << endl << endl;
	displayAccountHeader(accountType);

	// Display the account data
	if (accountType==AccountType::Savings)
	{
		SavingAccount* saving = (SavingAccount*)getAccount(suffix);
		displayAccountInfo(saving);
	}
	else if (accountType == AccountType::Checkings)
	{
		CheckingAccount* checking = (CheckingAccount*)getAccount(suffix);
		displayAccountInfo(checking);
	}
}