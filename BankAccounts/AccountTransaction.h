#pragma once

#include <iostream>
#include <iomanip>

#ifndef ACCTX_H
#define ACCTX_H

using namespace std;

// Hold monthly account statistics
struct AccountTransaction
{
private:
	double _startingBalance{ 0.00 };
	double _withdrawalAmount{ 0.00 };
	double _depositAmount{ 0.00 };
	double _serviceFees{ 0.00 };
	double _immediateFees{ 0.00 };
	double _interestEarned{ 0.00 };
	int _totalWithdrawals{ 0 };
	int _totalDeposits{ 0 };

public:
	// Get's the number of withdrawals made by the customer
	int getNumWithdrawals() { return _totalWithdrawals; }

	// Get's the number of deposits made by the customer
	int getNumDeposits() { return _totalDeposits; }

	// Get's the unapplied monthly service fees
	double getServiceFees() { return _serviceFees; }

	// Get's all service fees charged to account
	double getTotalServiceFees() { return getServiceFees() + _immediateFees; }

	// Get the interest earned for the month
	double getInterestEarned() { return _interestEarned; }

	// Adds to the amount deposited and increments deposit counter
	void addDeposit(double amount)
	{
		_depositAmount += amount;
		_totalDeposits++;
	}

	// Adds to the amount withdrawan and increments withdrawal counter
	void addWithdrawal(double amount)
	{ 
		_withdrawalAmount += amount;
		_totalWithdrawals++;
	}

	// Adds the fee to total fees
	// Applied and unapplied fees are tracked separately.
	void addFee(double amount, bool alreadyApplied = false)
	{
		if (alreadyApplied)
		{
			_immediateFees += amount;
		}
		else
		{
			_serviceFees += amount;
		}
	}

	// Adds to the interest amount
	void addInterest(double amount) { _interestEarned = amount; }

	// Resets counters
	void startNewMonth(double startingBalance)
	{
		_startingBalance = startingBalance;
		_withdrawalAmount = 0.00;
		_depositAmount = 0.00;
		_serviceFees = 0.00;
		_totalWithdrawals = 0;
		_totalDeposits = 0;
	}

	// Displays monthly stats
	void displayStatistics(double endingBalance)
	{
		cout << setprecision(2) << fixed;
		cout << "STARTING BAL: $" << _startingBalance << endl;
		cout << "NUM WITHDRAWALS: " << _totalWithdrawals << endl;
		cout << "NUM DEPOSITS   : " << _totalDeposits << endl;
		cout << "TOTAL WITHDRAWN: $" << _withdrawalAmount << endl;
		cout << "TOTAL DEPOSITED: $" << _depositAmount << endl;
		cout << "FEES & CHARGES : $" << getTotalServiceFees() << endl;
		cout << "INTEREST EARNED: $" << getInterestEarned() << endl;
		cout << string(30, '=') << endl;
		cout << "ENDING BALALANCE : $" << endingBalance << endl << endl;
	}
};
#endif // !ACCTX_H


