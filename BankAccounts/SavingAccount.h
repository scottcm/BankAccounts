#pragma once
#include "BankAccount.h"

#ifndef SAVING_H

#define SAVING_H

class SavingAccount :
	public BankAccount
{
private:
	const int ACTIVE = 1;
	const int INACTIVE = 0;
	const string STATUS_CODE[2] = { "I", "A" };

	// global variables
	int _status;

public:
	SavingAccount(double, double, int);

	// Accessors
	const string getStatusCode() const
	{
		return STATUS_CODE[_status];
	}
};

#endif // !SAVING_H

