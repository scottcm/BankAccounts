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
	// Magic # constants
	const int STARTING_CUSTOMER_ID = 10000;
	const double MIN_AMOUNT = 0.00;
	const double MAX_AMOUNT = 100000.00;
	const double MIN_APR = 0.00;
	const double MAX_APR = 100.00;
	const static int EXIT_RESPONSE = -1;

	// Main menu constants
	const static int ACCT_ACTION_SIZE = 6;
	const static int MANAGE_ACCT = 0;
	const static int UPDATE_CUST = 1;
	const static int CREATE_CUST = 2;
	const static int DELETE_CUST = 3;
	const static int CHANGE_ID = 4;
	const static int MNTH_PROC = 5;
	
	const string ACCT_ACTIONS[ACCT_ACTION_SIZE] = { "Manage Accounts (Deposit/Withdrawal/Open/Close)",
		"Update Customer Info",
		"New Customer",
		"Close All Accounts",
		"Change Customer ID",
		"Perform Monthly Processing" };
	const string ENTER_CUST_ID = "Enter your customer ID (" + to_string(STARTING_CUSTOMER_ID) + " to quit): ";

	// Account management constants
	const static int SUBACCT_SIZE = 2;
	const static int SUBACCT_ACTION_SIZE = 5;

	const static int DEPOSIT = 0;
	const static int WITHDRAW = 1;
	const static int CREATE_ACCT = 2;
	const static int DELETE_ACCT = 3;
	const static int CHG_TYPE = 4;

	const static int SAVINGS = 0;
	const static int CHECKING = 1;

	const string SUBACCT_ACTIONS[SUBACCT_ACTION_SIZE] = { "Deposit", "Withdrawal", "Create Account", "Close Account", "Change Account Type" };
	const string SUBACCT_TYPES[SUBACCT_SIZE] = { "Savings", "Checkings" };
	
	// Global variables
	map<int, BankCustomer*> _customers;				// Holds all the customer accounts. Customer ID is the key
	int _currCustomerId = STARTING_CUSTOMER_ID;		// The current customer ID. Needed for generating the next ID

	// Private Accessors
	const int getNextCustomerId() { return ++_currCustomerId; }
	bool askYesNo(string question);
	string requestUserInputString(string, unsigned int, unsigned int);
	int requestUserInput(string, int, int);
	double requestUserInput(string, double, double);
	int makeSelection(string, const string[], int);
	BankCustomer* getCustomer(int, bool = false);

	// Private Functions
	int selectCustomerAction(int);
	AccountType selectAccountType();
	int selectSubAccount(BankCustomer*, AccountType);
	void updateCustomerAddress(BankCustomer* customer);
	int retrieveCustomerId();
	void updateCustomerInfo(int);
	void selectAccountAction(int);
	int createCustomer();
	void deleteCustomer(int);
	void openSubAccount(int, AccountType);
	void closeSubAccount(int, AccountType);
	void makeDeposit(int, AccountType);
	void makeWithdrawal(int, AccountType);
	void displayMenuHeader(string);
	void performMonthlyMainenance(int);

public:
	Customers()
	{ }
	~Customers();

	// Public functions

	// Returns true if the specified customerId exists, otherwise false
	bool customerExists(int customerId) { return _customers.count(customerId); }

	// Runs the banking application
	void runApplication();
};

#endif // !CUSTOMERS_H