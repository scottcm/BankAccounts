#pragma once
#include "BankAccount.h"

// make a deposit for the specified amount
const double BankAccount::deposit(const double amount)
{
	if (amount > 0)
	{
		_balance += amount;
		_monthTx.addDeposit(amount);
	}

	return _balance;
}

// Withdraw function must be implemented by child classes.
	// Subtracts the amount from the balance
	// - double amount: The amount to withdraw
const double BankAccount::withdrawal(const double amount)
{
	if (amount > 0)
	{
		_balance -= amount;
		_monthTx.addWithdrawal(amount);
	}

	return getBalance();
}

// Calculates the monthly interest and adds that amount to the balance.
void BankAccount::calcInt()
{
	double interest = (getMonthlyInterestRate() / 100.00);	// Convert interest rate to decimal;
	double interestEarned = _balance * interest;
	_balance += interestEarned;
	_monthTx.addInterest(interestEarned);
}

// Performs the monthly account processing.
// Subtracts the monthly service charges, adds monthly interest by calling calcInt(),
// and the resets the number of withdrawals, deposits, monthly service charge, and monthly interest to 0
void BankAccount::monthlyProc()
{
	_balance -= _monthTx.getServiceFees();
	calcInt();

	cout << "Monthly Stats: *** " << getAccountSuffix() << ": " << getDescription() << endl;
	_monthTx.displayStatistics(_balance);
	resetMonthlyCounters();
}

// Adds the service charge specified
// If applyNow is true then the amount is immediately withdrawn
// Otherwise, the fee is withdrawn during monthly processing
void BankAccount::addServiceCharge(double amount, bool applyNow)
{
	_monthTx.addFee(amount, applyNow);
	if (applyNow)
	{
		_balance -= amount;
	}
}