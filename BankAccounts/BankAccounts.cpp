// BankAccounts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Customers.h"

using namespace std;

const int STARING_ACCOUNT_NUM = 10000;

void displaySavingAccounts(BankCustomer*);
void displayCheckingAccounts(BankCustomer*);
void displayAccountData(BankAccount*);

int main()
{
    // Run the application
    Customers customers;
    customers.runApplication();
}

