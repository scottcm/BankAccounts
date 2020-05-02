#include "CheckingAccount.h"

// Constructor
CheckingAccount::CheckingAccount(double balance, double apr, int suffixOffset) :
	BankAccount(balance, apr, AccountType::Checkings, suffixOffset)
{
	// Checking account specific initialization here
}

// Override BankAccount::withdrawal


// Override BankAcccount::deposit


// Override BankAcccount::calcInt


// Override BankAcccount::monthlyProc


// Other member functions
