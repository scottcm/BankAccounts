#pragma once
#include "BankAccount.h"

const double BankAccount::deposit(const double amount)
{
	_balance += amount;
	_monthTx.addDeposit(amount);

	return _balance;
}

// Withdraw function must be implemented by child classes.
	// Subtracts the amount from the balance
	// - double amount: The amount to withdraw
const double BankAccount::withdrawal(const double amount)
{
	_balance -= amount;
	_monthTx.addWithdrawal(amount);

	return getBalance();
}

// Calculates the monthly interest and adds that amount to the balance.
void BankAccount::calcInt()
{
	double interestEarned = _balance * getMonthlyInterestRate();
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
	_monthTx.displayStatistics(_balance);
	resetMonthlyCounters();
}