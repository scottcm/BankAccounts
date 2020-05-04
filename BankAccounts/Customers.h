#pragma once

#include "BankCustomer.h"
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"

#ifndef CUSTOMERS_H
#define CUSTOMERS_H

class Customers
{
private:
	const int STARTING_CUSTOMER_ID = 10000;
	const static int ACCT_ACTION_SIZE = 4;
	const static int SUBACCT_ACTION_SIZE = 4;
	const static int SUBACCT_SIZE = 2;
	const string ACCT_ACTIONS[ACCT_ACTION_SIZE] = { "Manage Accounts", "Update Customer Info", "New Customer", "Close All Accounts" };
	const string SUBACCT_ACTIONS[SUBACCT_ACTION_SIZE] = { "Deposit", "Withdrawal", "Create Sub-account", "Close Sub-account" };
	const string SUBACCT_TYPES[SUBACCT_SIZE] = { "Savings", "Checkings" };
	const static int EXIT_RESPONSE = -1;

	const static int MANAGE_ACCT = 0;
	const static int UPDATE_ACCT = 1;
	const static int CREATE = 2;
	const static int DELETE = 3;

	const static int DEPOSIT = 0;
	const static int WITHDRAW = 1;

	const static int SAVINGS = 0;
	const static int CHECKING = 1;

	const string ENTER_CUST_ID = "Enter your customer ID (" + to_string(STARTING_CUSTOMER_ID) + " to quit): ";

	map<int, BankCustomer*> _customers;
	int _currCustomerId = STARTING_CUSTOMER_ID;

	const int getNextCustomerId() { return ++_currCustomerId; }
	bool askYesNo(string question);
	string requestUserInputString(string, int, int);
	int requestUserInput(string, int, int);
	double requestUserInput(string, double, double);
	int makeSelection(string, const string[], int);
	
	BankCustomer* getCustomer(int accountNum)
	{
		if (_customers.count(accountNum))
		{
			return _customers[accountNum];
		}

		return nullptr;
	}

	int selectCustomerAction(int);
	AccountType selectAccountType();
	int selectSubAccount(BankCustomer*, AccountType);
	BankCustomer* createNewCustomer();
	void updateCustomerAddress(BankCustomer* customer);
	BankCustomer* requestCustomer(int);
	int retrieveCustomerId();
	void updateCustomerInfo(int);
	void useAccount(int);
	int createCustomer();
	void deleteCustomer(int);
	void openSubAccount(int, AccountType);
	void closeSubAccount(int, AccountType);
	void makeDeposit(int, AccountType);
	void makeWithdrawal(int, AccountType);
	void displayMenuHeader(string);

public:
	Customers()
	{ }
	~Customers();

	bool customerExists(int customerId) { return _customers.count(customerId); }

	void runApplication();
};

#endif // !CUSTOMERS_H