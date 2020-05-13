#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(double balance, double apr, int suffixOffset) :
	BankAccount(balance, apr, AccountType::Checkings, suffixOffset)
{
	// Saving account specific initialization here
}

// Makes a withdrawal from the checking account
const double CheckingAccount::withdrawal(const double amount)
{
	double currBalance = getBalance();
	double endBalance = currBalance - amount;

	// If the withdrawal would take the account negative, charge a fee and do NOT make withdrawal
	if (endBalance < 0)
	{
		addServiceCharge(OVERDRAFT_FEE, true);
	}
	else
	{
		BankAccount::withdrawal(amount);
	}

	return getBalance();
}

// Performs monthly processing
void CheckingAccount::monthlyProc()
{
	double wdFee;

	// Add monthly fee
	addServiceCharge(MONTHLY_FEE);

	// Add per check fee
	wdFee = getNumWithdrawals() * PER_CHECK_FEE;
	addServiceCharge(wdFee);

	// Perform monthly processing
	BankAccount::monthlyProc();
}