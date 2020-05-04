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
    Customers customers;
    customers.runApplication();
    /*
    int currAccount = STARING_ACCOUNT_NUM;
    int accountSuffix;
    BankCustomer customer = BankCustomer(++currAccount, "Scott", "Mulcahy");
    accountSuffix = customer.createSubAccount(AccountType::Savings, 500.00, 3.50);
    customer.getAccount(accountSuffix)->setDescription("Savings");

    accountSuffix = customer.createSubAccount(AccountType::Savings, 250.25, 3.75);
    customer.getAccount(accountSuffix)->setDescription("Christmas CD");

    accountSuffix = customer.createSubAccount(AccountType::Checkings, 615.00, .25);
    customer.getAccount(accountSuffix)->setDescription("Bills");

    accountSuffix = customer.createSubAccount(AccountType::Checkings, 200.00, .30);
    customer.getAccount(accountSuffix)->setDescription("Entertainment");
    
    accountSuffix = customer.createSubAccount(AccountType::Checkings, 5000.00, 1.00);
    customer.getAccount(accountSuffix)->setDescription("Payroll");

    customer.displayCustomerInfo();
    customer.displaySavingsAccounts();
    customer.displayCheckingsAccounts();
    */
}

