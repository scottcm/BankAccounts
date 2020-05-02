#include "SavingAccount.h"

// Constructors
SavingAccount::SavingAccount(double balance, double apr, int suffixOffset) :
	BankAccount(balance, apr, AccountType::Savings, suffixOffset)
{
	// Saving account specific initialization here
	_status = INACTIVE;
}

// Override BankAccount::withdrawal


// Override BankAcccount::deposit


// Override BankAcccount::calcInt


// Override BankAcccount::monthlyProc



// Other member functions
