#pragma once
#include "BankAccount.h"

#ifndef CHECKING_H

#define CHECKING_H

class CheckingAccount :
	public BankAccount
{
private:
	// global variables

public:
	CheckingAccount(double, double, int);

	// Accessors

	// Virtual function implementations
};

#endif // !CHECKING_H

