#pragma once

#include <iostream>
#include <iomanip>

#ifndef ACCTX_H
#define ACCTX_H

using namespace std;

struct AccountTransaction
{
private:
	double _startingBalance{ 0.00 };
	double _withdrawalAmount{ 0.00 };
	double _depositAmount{ 0.00 };
	double _serviceFees{ 0.00 };
	double _interestEarned{ 0.00 };
	int _totalWithdrawals{ 0 };
	int _totalDeposits{ 0 };

public:
	int getNumWithdrawals() { return _totalWithdrawals; }
	int getNumDeposits() { return _totalDeposits; }
	double getServiceFees() { return _serviceFees; }
	double getInterestEarned() { return _interestEarned; }

	void addDeposit(double amount)
	{
		_depositAmount += amount;
		_totalDeposits++;
	}
	void addWithdrawal(double amount)
	{ 
		_withdrawalAmount += amount;
		_totalWithdrawals++;
	}
	void addFee(double amount) { _serviceFees += amount; }
	void addInterest(double amount) { _interestEarned = amount; }
	void startNewMonth(double startingBalance)
	{
		_startingBalance = startingBalance;
		_withdrawalAmount = 0.00;
		_depositAmount = 0.00;
		_serviceFees = 0.00;
		_totalWithdrawals = 0;
		_totalDeposits = 0;
	}
	void displayStatistics(double endingBalance)
	{
		cout << setprecision(2) << fixed;
		cout << "STARTING BAL: $" << _startingBalance << endl;
		cout << "NUM WITHDRAWALS: $" << _totalWithdrawals << endl;
		cout << "NUM DEPOSITS   : $" << _totalDeposits << endl;
		cout << "TOTAL WITHDRAWN: $" << _withdrawalAmount << endl;
		cout << "TOTAL DEPOSITED: $" << _depositAmount << endl;
		cout << "FEES & CHARGES : $" << _serviceFees << endl << endl;
		cout << "ENDING BALALANCE : $" << endingBalance << endl;
	}
};
#endif // !ACCTX_H


