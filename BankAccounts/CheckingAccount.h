#pragma once
#include "BankAccount.h"

#ifndef CHECKING_H
#define CHECKING_H

class CheckingAccount :
	public BankAccount
{
private:
	// constants
	double PER_CHECK_FEE = 0.10;
	double MONTHLY_FEE = 5.00;
	double OVERDRAFT_FEE = 15.00;

public:
	CheckingAccount(double, double, int);

	// Virtual function implementations
	virtual const double withdrawal(const double amount);
	virtual void monthlyProc();
};

#endif // !CHECKING_H

