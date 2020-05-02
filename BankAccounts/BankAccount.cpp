#pragma once
#include "BankAccount.h"


const string BankAccount::getAccountId()
{
	ostringstream oss;		// output stream used to create the string

	// Found code to convert GUID to string
	// https://stackoverflow.com/questions/1672677/print-a-guid-variable
	oss << std::uppercase;
	oss.width(8);
	oss << std::hex << _accountId.Data1 << '-';

	oss.width(4);
	oss << std::hex << _accountId.Data2 << '-';

	oss.width(4);
	oss << std::hex << _accountId.Data3 << '-';

	oss.width(2);
	oss << std::hex
		<< static_cast<short>(_accountId.Data4[0])
		<< static_cast<short>(_accountId.Data4[1])
		<< '-'
		<< static_cast<short>(_accountId.Data4[2])
		<< static_cast<short>(_accountId.Data4[3])
		<< static_cast<short>(_accountId.Data4[4])
		<< static_cast<short>(_accountId.Data4[5])
		<< static_cast<short>(_accountId.Data4[6])
		<< static_cast<short>(_accountId.Data4[7]);
	oss << std::nouppercase;

	return oss.str();
}

const double BankAccount::deposit(const double* amount)
{
	_balance += (*amount);
	_numMonthDeposits++;

	return _balance;
}

// Withdraw function must be implemented by child classes.
	// Subtracts the amount from the balance
	// - double amount: The amount to withdraw
const double BankAccount::withdrawal(const double* amount)
{
	_balance -= (*amount);
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