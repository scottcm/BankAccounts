#pragma once
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

// Includes
#include <string>

using namespace std;

enum class AccountType : int { Invalid = 0, Savings = 100, Checkings = 200 };


class BankAccount
{
private:
	AccountType _accountType;			// The type of account
	double _annualInterestRate;			// annual interest rate of the account
	short _suffix;						// account suffix	
	string _description;				// Account description

protected:
	
	double _balance;					// account balance
	double _monthInterestEarned;		// amount of interest earned this month
	double _ytdInterestEarned;			// year-to-date interest earned
	double _serviceCharges;				// amount of service charges in dollars
	int _numMonthDeposits;				// number of deposits for the month
	int _numMonthWithdrawals;			// number of withdrawals for the month

	// Resets counters and monthly variables to 0
	// service charges, # of deposits, # of withdrawals, and monthly interest
	void resetMonthlyCounters()
	{
		_serviceCharges = 0;
		_numMonthDeposits = 0;
		_numMonthWithdrawals = 0;
		_monthInterestEarned = 0;
	}

	// Resets the year-to-date interest earned on the account
	void resetYtdInterestEarned()
	{
		_ytdInterestEarned = 0;
	}

	// Add a service charge
	// double amount: The amount of service charge to add
	void addServiceCharge(double amount)
	{
		_serviceCharges += amount;
	}

public:
	// Default constructor
	BankAccount()
	{
		_balance = 0;
		_annualInterestRate = 0;
		_accountType = AccountType::Invalid;
		_suffix = 0;

		_serviceCharges = 0;
		_numMonthDeposits = 0;
		_numMonthWithdrawals = 0;
		_monthInterestEarned = 0;
		_ytdInterestEarned = 0;
		_description = "";
	}

	// Constructor
	BankAccount(double balance, double annualInterestRate, AccountType accountType, int accountOffset) : BankAccount()
	{
		_balance = balance;
		_annualInterestRate = annualInterestRate;
		_accountType = accountType;
		_suffix = static_cast<int>(_accountType) + accountOffset;
	}

	// Accessors
	const AccountType getAccountType() const { return _accountType; }
	const int getAccountSuffix() const { return _suffix; }
	const int getAccountOffset() const { return getAccountSuffix() - static_cast<int>(getAccountType()); }
	const string getDescription() const { return _description; }
	const double getBalance() const { return _balance; }
	const double getYtdInterest() const { return _ytdInterestEarned; }
	const double getMonthlyInterestRate() const { return (_annualInterestRate / 12); }
	const double getAnnualInterestRate() const { return _annualInterestRate; }
	const int getNumWithdrawals() const { return _numMonthWithdrawals; }
	const int getNumDeposits() const { return _numMonthDeposits; }
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

		switch (suffix)
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

	virtual const double deposit(const double amount);
	virtual const double withdrawal(const double amount);
	virtual void calcInt();
	virtual void monthlyProc();
};

#endif // !BANK_ACCOUNT_H