#pragma once
#include <vector>
#include <map>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>

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

	int _accountNum;
	map<int, BankAccount*> _accounts;
	string _firstName, _lastName;	// First and last name of customer
	string _address1, _address2;
	string _city, _state, _zipCode;

	const int getNextSuffixOfType(AccountType accountType);
	BankAccount* findAccount(int suffix);

protected:
	virtual void displayAccountInfo(CheckingAccount*);
	virtual void displayAccountInfo(SavingAccount*);
	void displayAccountHeader(AccountType);

public:
	const static int MIN_NAME_LENGTH = 2;
	const static int MIN_ADDR_LENGTH = 5;
	const static int MIN_CITY_LENGTH = 2;
	const static int MIN_STATE_LENGTH = 2;
	const static int MIN_ZIP_LENGTH = 5;
	const static int MAX_NAME_LENGTH = 255;
	const static int MAX_ADDR_LENGTH = 255;
	const static int MAX_CITY_LENGTH = 255;
	const static int MAX_STATE_LENGTH = 48;		// State of Rhode Island and Providence Plantations
	const static int MAX_ZIP_LENGTH = 10;

	BankCustomer(int, string, string);
	~BankCustomer();

	/* Accessors */
	const int getAccountNum() const { return _accountNum; }
	const string getFullName() const { return _firstName + " " + _lastName; }
	const string getFirstName() const { return _firstName; }
	const string getLastName() const { return _lastName; }
	const string getAddress1() const { return _address1; }
	const string getAddress2() const { return _address2; }
	const string getCity() const { return _city; }
	const string getState() const { return _state; }
	const string getZipCode() const { return _zipCode; }
	const string getLocation() const { return (getCity() + ", " + getState() + "  " + getZipCode()); }
	const string getFullAddress() const
	{
		return (getFullName() + "\n" +
			getAddress1() + "\n" +
			getAddress2() + "\n" +
			getLocation());
	}
	const bool suffixExists(int suffix) const { return _accounts.count(suffix); }
	const unsigned int getNumAccounts() { return _accounts.size(); }

	BankAccount* findNextAccountOfType(AccountType accountType, int startingOffset);

	// Returns the first savings account if one exists, otherwise nullptr
	SavingAccount* getFirstSavingAccount()
	{
		BankAccount* account = BankCustomer::findNextAccountOfType(AccountType::Savings, -1);
		return (SavingAccount*)account;
	}

	// Returns the next savings account after the offset
	// int currOffset: The offset from AccountType::Savings
	SavingAccount* getNextSavingAccount(int currOffset)
	{
		BankAccount* account = account = BankCustomer::findNextAccountOfType(AccountType::Savings, currOffset);
		return (SavingAccount*)account;
	}

	// Returns the first checking account if one exists, otherwise null ptr
	CheckingAccount* getFirstCheckingAccount()
	{
		BankAccount* account = BankCustomer::findNextAccountOfType(AccountType::Checkings, -1);
		return (CheckingAccount*)account;
	}

	// Returns the next checking account after the offset
	// int currOffset: The offset from AccountType::Checkings
	CheckingAccount* getNextCheckingAccount(int currOffset)
	{
		BankAccount* account = BankCustomer::findNextAccountOfType(AccountType::Checkings, currOffset);
		return (CheckingAccount*)account;
	}

	BankAccount* getAccount(int suffix);

	/* Mutators */
	void setFirstName(string firstName) { _firstName = firstName; }
	void setLastName(string lastName) { _lastName = lastName; }
	void setAddress1(string address1) { _address1 = address1; }
	void setAddress2(string address2) { _address2 = address2; }
	void setCity(string city) { _city = city.substr(0, MAX_CITY_LENGTH); }
	void setState(string state) { _state = state.substr(0, MAX_STATE_LENGTH); }
	void setZipCode(string zipCode)
	{
		if (zipCode.length() == MIN_ZIP_LENGTH || zipCode.length() == MAX_ZIP_LENGTH)
		{
			_zipCode = zipCode;
		}
	}

	/* Other functions */
	int createSubAccount(AccountType, double, double);
	void deleteSubAccount(int);
	void displayCustomerInfo();
	void displayCheckingsAccounts();
	void displaySavingsAccounts();
	virtual void displayAccountInfo(int);
};

#endif // !CUSTOMER_H