#pragma once
#include <vector>
#include <map>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"

using namespace std;

#ifndef CUSTOMER_H
#define CUSTOMER_H

class BankCustomer
{
private:
	const int ACCOUNT_WIDTH = 12;
	const int STATUS_WIDTH = 7;
	const int BALANCE_WIDTH = 10;
	const int DESC_WIDTH = 20;
	const int APR_WIDTH = 7;

	int _customerId;
	map<int, BankAccount*> _accounts;
	string _firstName, _lastName;	// First and last name of customer

	BankAccount* findAccount(int suffix);
	BankAccount* findFirstAccountOfType(AccountType accountType, int startingOffset);
	const int getNextSuffixOfType(AccountType accountType);

public:
	const int getCustomerId() { return _customerId; }
	const string getFullName() { return _firstName + " " + _lastName; }
	const string getFirstName() { return _firstName; }
	const string getLastName() { return _lastName; }
	const unsigned int getNumAccounts() { return _accounts.size(); }

	BankCustomer(int, string, string);
	~BankCustomer();

	SavingAccount* getFirstSavingAccount()
	{
		BankAccount* account = BankCustomer::findFirstAccountOfType(AccountType::Savings, 0);
		return (SavingAccount*)account;
	}

	SavingAccount* getNextSavingAccount(int currOffset)
	{
		BankAccount* account = account = BankCustomer::findFirstAccountOfType(AccountType::Savings, currOffset + 1);
		
		return (SavingAccount*)account;
	}

	CheckingAccount* getFirstCheckingAccount()
	{
		BankAccount* account = BankCustomer::findFirstAccountOfType(AccountType::Checkings, 0);
		return (CheckingAccount*)account;
	}

	CheckingAccount* getNextCheckingAccount(int currOffset)
	{
		BankAccount* account = BankCustomer::findFirstAccountOfType(AccountType::Checkings, currOffset + 1);

		return (CheckingAccount*)account;
	}

	virtual BankAccount* getFirstAccount()
	{
		return BankCustomer::_accounts.begin()->second;
	}

	BankAccount* getAccount(int suffix);

	int createAccount(AccountType, double, double);
	void deleteAccount(int);
	void DisplayCustomerInfo();
	void DisplayCheckingsAccounts();
	void DisplaySavingsAccounts();
};

#endif // !CUSTOMER_H