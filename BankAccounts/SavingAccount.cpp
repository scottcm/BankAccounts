#include "SavingAccount.h"

// Constructors
SavingAccount::SavingAccount(double balance, double apr, int suffixOffset) :
	BankAccount(balance, apr, AccountType::Savings, suffixOffset)
{
	// Saving account specific initialization here

}

// Override BankAccount::withdrawal
const double SavingAccount::withdrawal(const double amount)
{
	//only make withdrawal if the account is ACTIVE
	if (isActive())
	{
		//Make a withdrawal if the amount greater than $0 and the balance remains positive
		if ((amount > 0) && ((getBalance() - amount) > 0))
		{
			BankAccount::withdrawal(amount);
		}
	}
	return getBalance();
}

// Override BankAcccount::deposit
const double SavingAccount::deposit(const double amount)
{
	//If active, make deposit
	if (isActive())
	{
		BankAccount::deposit(amount);
	}
	//Not active, deposit if the amount bring the balance up to ACTIVE
	else if (getBalance() + amount >= MIN_ACTIVE_BAL)
	{
		BankAccount::deposit(amount);
	}
	return getBalance();
}

// Override BankAcccount::monthlyProc
void SavingAccount::monthlyProc()
{
	//If number of withdrawal is greater than 4, charge $1 each time
	if (getNumWithdrawals() > MAX_NUM_WITHDRAWAL)
	{
		double fee = WITHDRAW_FEE * (getNumWithdrawals() - MAX_NUM_WITHDRAWAL);
		addServiceCharge(fee);
	}

	//Let parent function finish processing monthlyProc
	BankAccount::monthlyProc();
}


// Other member functions
