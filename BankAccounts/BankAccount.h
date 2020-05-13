#pragma once

// Includes
#include <string>
#include "AccountTransaction.h"
using namespace std;

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

enum class AccountType : int { Invalid = 0, Savings = 100, Checkings = 200 };

class BankAccount
{
private:
	AccountType _accountType;			// The type of account
	double _annualInterestRate;			// annual interest rate of the account
	double _balance;					// account balance
	short _suffix;						// account suffix	
	string _description;				// Account description
	AccountTransaction _monthTx;		// Monthly account transactions

	// Calculates interest
	void calcInt();
protected:
	// Resets monthly transaction counters to 0
	void resetMonthlyCounters()
	{
		_monthTx.startNewMonth(_balance);
	}

	const int getNumWithdrawals() { return _monthTx.getNumWithdrawals(); }
	const int getNumDeposits() { return _monthTx.getNumDeposits(); }

	// Add a service charge
	// double amount: The amount of service charge to add
	// bool wither to apply the fee immediately. Default is false
	void addServiceCharge(double, bool = false);


public:
	// Default constructor
	BankAccount()
	{
		_balance = 0;
		_annualInterestRate = 0;
		_accountType = AccountType::Invalid;
		_suffix = 0;

		_description = "";
	}

	// Constructor
	BankAccount(double balance, double apr, AccountType accountType, int accountOffset) : BankAccount()
	{
		_balance = balance;
		_monthTx.startNewMonth(balance);
		_annualInterestRate = apr;
		_accountType = accountType;
		_suffix = static_cast<int>(_accountType) + accountOffset;
	}

	// Accessors
	const AccountType getAccountType() const { return _accountType; }
	const int getAccountSuffix() const { return _suffix; }
	const int getAccountOffset() const { return getAccountSuffix() - static_cast<int>(getAccountType()); }
	const string getDescription() const { return _description; }
	const double getBalance() const { return _balance; }
	const double getMonthlyInterestRate() const { return (getAnnualInterestRate() / 12.00); }
	const double getAnnualInterestRate() const { return _annualInterestRate; }
	const string getAccountNumber(int customerId) const { return to_string(customerId) + ":" + to_string(_suffix); }
	/* END OF ACCESSORS */

	/* Mutators */
	void setDescription(string description) { _description = description; }

	/* Other functions */
	// Converts an integer suffix to its AccountType value
	// int suffix: the account suffix to convert
	// RETURN: AccountType
	static AccountType identifyAccountType(int suffix)
	{
		AccountType accountType = AccountType::Invalid;
		int rootSuffix = suffix - (suffix % 100);

		switch (rootSuffix)
		{
			case static_cast<int>(AccountType::Savings) :
				accountType = AccountType::Savings;
				break;
			case static_cast<int>(AccountType::Checkings) :
				accountType = AccountType::Checkings;
				break;
		}

		return accountType;
	}

	// Converts AccountType enum value to a string
	static string accountTypeToName(AccountType accountType)
	{
		switch (accountType)
		{
		case AccountType::Checkings: return "Checking";
		case AccountType::Savings: return "Savings";
		}

		return "Invalid";
	}

	// Deposits the specified amount
	virtual const double deposit(const double amount);

	// Withrdaws the specified amount
	virtual const double withdrawal(const double amount);

	// Performs monthly processing
	virtual void monthlyProc();
};

#endif // !BANK_ACCOUNT_H