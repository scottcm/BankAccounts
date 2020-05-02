#pragma once
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

// Includes
#include <objbase.h>
#include <string>
#include <sstream>

// Generate GUID requires OLE32
#pragma comment(lib, "ole32.lib")

using namespace std;


class BankAccount
{
private:
	GUID _accountId;					// account ID. Must be unique
	double _balance;					// account balance
	double _monthInterestEarned;		// amount of interest earned this month
	double _ytdInterestEarned;			// year-to-date interest earned
	double _serviceCharges;				// amount of service charges in dollars
	double _annualInterestRate;			// annual interest rate of the account
	int _numMonthDeposits;				// number of deposits for the month
	int _numMonthWithdrawals;			// number of withdrawals for the month
	
	
	// Private constructor - This code should never be modified by children
	BankAccount()
	{
		_balance = 0;
		_annualInterestRate = 0;
		_serviceCharges = 0;
		_numMonthDeposits = 0;
		_numMonthWithdrawals = 0;
		_monthInterestEarned = 0;
		_ytdInterestEarned = 0;

		// Assign account ID
		::CoInitialize(0);	// Initialize COM - Windows
		::CoCreateGuid(&_accountId);	// Assign a random GUID to _accountId
		::CoUninitialize();	// Unitialize COM
	}

protected:
	void resetMonthlyCounters()
	{
		_serviceCharges = 0;
		_numMonthDeposits = 0;
		_numMonthWithdrawals = 0;
		_monthInterestEarned = 0;
	}

	void resetYtdInterestEarned()
	{
		_ytdInterestEarned = 0;
	}

	void setServiceCharge(double* amount)
	{
		_serviceCharges += (*amount);
	}

public:
	// Constructor
	BankAccount(double balance, double interestRate) : BankAccount()
	{
		// Initialize balance and interest rate variables
	}

	// Accessors and Settors
	const double getBalance() const
	{
		return _balance;
	}

	const double getYtdInterest() const
	{
		return _ytdInterestEarned;
	}

	const double getMonthlyInterestRate() const
	{
		return (_annualInterestRate / 12);
	}

	const double getAnnualInterestRate() const
	{
		return _annualInterestRate;
	}

	const int getNumWithdrawals()
	{
		return _numMonthWithdrawals;
	}

	const int getNumDeposits()
	{
		return _numMonthDeposits;
	}

	// Returns the AccountID as a string
	const string getAccountId();

	const double deposit(const double* amount);
	
	const double withdrawal(const double* amount);

	void calcInt();

	void monthlyProc();
};

#endif // !BANK_ACCOUNT_H