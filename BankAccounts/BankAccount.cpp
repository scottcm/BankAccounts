#pragma once
#include "BankAccount.h"

const double BankAccount::deposit(const double amount)
{
	_balance += amount;
	_numMonthDeposits++;

	return _balance;
}

// Withdraw function must be implemented by child classes.
	// Subtracts the amount from the balance
	// - double amount: The amount to withdraw
const double BankAccount::withdrawal(const double amount)
{
	_balance -= amount;
	_numMonthWithdrawals++;

	return getBalance();
}

// Calculates the monthly interest and adds that amount to the balance.
void BankAccount::calcInt()
{
	_monthInterestEarned = _balance * getMonthlyInterestRate();
	_ytdInterestEarned += _monthInterestEarned;
	_balance += _monthInterestEarned;
}

// Performs the monthly account processing.
// Subtracts the monthly service charges, adds monthly interest by calling calcInt(),
// and the resets the number of withdrawals, deposits, monthly service charge, and monthly interest to 0
void BankAccount::monthlyProc()
{
	_balance -= _serviceCharges;
	calcInt();
	resetMonthlyCounters();
}