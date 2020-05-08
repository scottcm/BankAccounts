#include "CheckingAccount.h"

// Constructor
CheckingAccount::CheckingAccount(double balance, double apr, int suffixOffset) :
	BankAccount(balance, apr, AccountType::Checkings, suffixOffset)
		
#include <iostream>
#include "BankAccount.h"

using namespace std;

class CheckingAccount : public BankAccount{
private:
    //member variable to keep track
    //of how much is owed to the bank
    double owed;

public:
    //constructor, will call
    //constructor of parent class
    CheckingAccount(double b, double air) :
        BankAccount(b, air)
        {
            owed = 0.0;
        }

    //accessor function
    double getAmountOwed() const{
        return owed;
    }

    //withdraw() function of the checking account
    virtual void withdraw(double w){
        //check if withdrawal will create a negative balance
        if(w > balance){
            //print error message
            cout << fixed << setprecision(2);
            cout << "Cannot Withdraw! You attempted to check $";
            cout << w << " but current balance is $" << balance;
            cout << ".\nYou will be charged $15.00 for overdrafting.\n";

            //subtract 15 from balance
            balance -= 15.0;
        }
        //else, simply perform withdrawal
        else{
            BankAccount::withdraw(w);
        }
    }

    //monthlyProc() function of checking account
    virtual ServAndOwed monthlyProc(){
        //add fee to service charges
        serviceCharges += 5.0;

        //also add the charges per withdrawal
        serviceCharges += 0.1 * numWithdrawal;

        //add the service charges to monthly charges
        mnCharges += serviceCharges;

        //structure to return at the end, the service
        //charges and total owed to bank, because
        // they will be reset upon execution of
        //BankAccount::monthlyProc()
        ServAndOwed temp;
        temp.servCharges = serviceCharges;

        //perform monthly processing
        //this will reset the serviceCharges variable
        BankAccount::monthlyProc();

        //after processing,
        //check if balance is negative
        if(balance < 0){
            //update owed member variable
            //to amount owed to bank by user
            owed = 0 - balance;
        }

        //store it in the structure
        temp.totalOwed = owed;

        //reset owed to 0
        owed = 0;

        //return the structure, from which can be
        //retrieved the service charges of this month
        return temp;
    }

};

#endif
