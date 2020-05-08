#pragma once
#include "BankAccount.h"

#ifndef SAVING_H

#define SAVING_H

class SavingAccount :
	public BankAccount
{
private:
	const string ACTIVE = "A";
	const string INACTIVE = "I";
	const double MIN_ACTIVE_BAL = 25.00;
	const double WITHDRAW_FEE = 1.00;
	const int MAX_NUM_WITHDRAWAL = 4;

public:

	SavingAccount(double, double, int);

	// Accessors
	const bool isActive() const
	{
		//Returning if the balance is over $25
		return getBalance() >= MIN_ACTIVE_BAL;
	}

	const string getStatusCode() const
	{
		//If active return A, if inactive return I
		if (isActive())
			return ACTIVE;
		else
			return INACTIVE;
	}

	//Override
	virtual const double deposit(const double amount);
	virtual const double withdrawal(const double amount);
	virtual void monthlyProc();
};

#endif // !SAVING_H