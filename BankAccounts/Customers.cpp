#include "Customers.h"
#include "BankCustomer.h"
#include <vector>


Customers::~Customers()
{
	// Delete customer data
	map<int, BankCustomer*>::iterator cIter;

	for (cIter = _customers.begin(); cIter != _customers.end(); cIter++)
	{
		delete (cIter->second);
	}
}

string Customers::requestUserInputString(string question, int minLength = 1, int maxLength = 255)
{
	string response;

	cout << question;
	do
	{
		getline(cin, response);
	} while (response.length() < minLength || response.length() > maxLength);

	return response;
}

bool Customers::askYesNo(string question)
{
	char response;
	bool invalidResponse = true;
	bool isYes;

	// Ask a Y/N question. Repeat the question until the user answers either Y or N
	do
	{
		// Ask the question and get the user response
		cout << question << "(Y/N): ";
		cin >> response;

		cin.ignore(); // Ignore enter at the end;

		// convert the response to uppercase because answer is case-insensitive and determine if valid response
		switch (_toupper(response))
		{
		case 'Y':
			isYes = true;
			invalidResponse = false;
			break;
		case 'N':
			isYes = false;
			invalidResponse = false;
			break;
		}
	} while (invalidResponse);

	// Return true if the user answered yes, otherwise false
	return isYes;
}

int Customers::requestUserInput(string question, int minNumber, int maxNumber)
{
	int response;

	cout << question;
	do
	{
		cin >> response;
		cin.ignore();
	} while (response < minNumber || response > maxNumber);
	cout << endl;

	return response;
}

double Customers::requestUserInput(string question, double minAmount, double maxAmount)
{
	double response;
	
	cout << question;
	do
	{
		cin >> response;
		cin.ignore();
	} while (response < minAmount || response > maxAmount);
	cout << endl;

	return response;
}

int Customers::makeSelection(string prompt, const string selections[], int selectionSize)
{
	int userSelection = EXIT_RESPONSE;

	cout << prompt << endl;
	// Display selections
	for (int i = 0; i < selectionSize; i++)
	{
		cout << (i + 1) << ") " << selections[i] << endl;
	}

	// Get user response
	do
	{
		cout << "\nSelection (" << EXIT_RESPONSE << " to Exit): ";
		cin >> userSelection;
		cin.ignore();
	} while (userSelection != EXIT_RESPONSE && (userSelection < 1 || userSelection > selectionSize));

	cout << endl;
	// Return user response
	if (userSelection != EXIT_RESPONSE)
	{
		userSelection -= 1;
	}
	return userSelection;
}

void Customers::updateCustomerAddress(BankCustomer* customer)
{
	cout << "\nSet Address Info...\n";
	string address1 = requestUserInputString("Address 1: ", BankCustomer::MIN_ADDR_LENGTH, BankCustomer::MAX_ADDR_LENGTH);
	string address2 = requestUserInputString("Address 2: ", 0, BankCustomer::MAX_ADDR_LENGTH);
	string city = requestUserInputString("City: ", BankCustomer::MIN_CITY_LENGTH, BankCustomer::MAX_CITY_LENGTH);
	string state = requestUserInputString("State: ", BankCustomer::MIN_STATE_LENGTH, BankCustomer::MAX_STATE_LENGTH);
	string zip = requestUserInputString("Zip Code: ", BankCustomer::MIN_ZIP_LENGTH, BankCustomer::MAX_ZIP_LENGTH);

	customer->setAddress1(address1);
	customer->setAddress2(address2);
	customer->setCity(city);
	customer->setState(state);
	customer->setZipCode(zip);

	cout << endl << endl;
}

BankCustomer* Customers::createNewCustomer()
{
	string firstName, lastName;
	string address1, address2;
	string city, state, zip;

	// get customer info VERIFY \n ISN'T COUNTED!!!
	firstName = requestUserInputString("First Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);
	lastName = requestUserInputString("Last Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);

	BankCustomer* customer = nullptr;
	if (askYesNo("Proceed with save?"))
	{
		// create account
		customer = new BankCustomer(getNextCustomerId(), firstName, lastName);
		updateCustomerAddress(customer);
	}

	return customer;
}

int Customers::retrieveCustomerId()
{
	int accountNum;
	do
	{
		// Get customer number
		accountNum = requestUserInput(ENTER_CUST_ID, STARTING_CUSTOMER_ID, INT_MAX);

		if (accountNum != STARTING_CUSTOMER_ID)
		{
			// Retrieve customer
			if (!customerExists(accountNum))
			{
				cout << "Unable to find your account.\n";
			}
		}
	} while (accountNum != STARTING_CUSTOMER_ID);

	return accountNum;
}
BankCustomer* Customers::requestCustomer(int customerId)
{
	BankCustomer* customer = nullptr;

	do
	{
		// Get customer number
		customerId = requestUserInput(ENTER_CUST_ID, STARTING_CUSTOMER_ID, INT_MAX);

		if (customerId != STARTING_CUSTOMER_ID)
		{
			// Retrieve customer
			if (customerExists(customerId))
			{
				customer = _customers[customerId];
			}
			else
			{
				cout << "Unable to find your account.\n";
			}
		}
	} while (customerId != STARTING_CUSTOMER_ID && customer == nullptr);

	return customer;
}

// Create a new customer account
int Customers::createCustomer()
{
	int customerId = STARTING_CUSTOMER_ID;

	BankCustomer* customer = createNewCustomer();
	if (customer != nullptr)
	{
		customerId = customer->getAccountNum();
		_customers[customerId] = customer;

		cout << "\nYour new account ID is " << customerId << endl << endl;
	}

	return customerId;
}

void Customers::deleteCustomer(int customerId)
{
	if (customerExists(customerId))
	{
		delete _customers[customerId];
		_customers.erase(customerId);
	}
}

void Customers::closeSubAccount(int customerId, AccountType accountType)
{
	displayMenuHeader("Close Account");
	BankCustomer* customer = getCustomer(customerId);

	if (customer == nullptr)
	{
		cout << "Your account no longer exists!\n";
	}

	int suffix = selectSubAccount(customer, accountType);
	if (EXIT_RESPONSE == EXIT_RESPONSE) { return; }

	cout << "Deleting account: " << suffix << endl;
	customer->displayAccountInfo(suffix);

	if (askYesNo("Are you SURE you want to delete this account?"))
	{
		customer->deleteSubAccount(suffix);
	}
}

void Customers::openSubAccount(int customerId, AccountType accountType)
{
	displayMenuHeader("Account Creation");
	BankCustomer* customer = getCustomer(customerId);

	if (customer == nullptr)
	{
		cout << "Your account no longer exists!\n";
		return;
	}

	// Limit opening balance to $100,000
	double openingBalance = requestUserInput("Opening Balance: $", 0, 100000);
	double apr = requestUserInput("Annual Percentage Rate: ", 0.00, 100.00);
	int suffix = customer->createSubAccount(accountType, openingBalance, apr);
	string acctDescription = requestUserInputString("Account Description (25 chars or less): ", 0, 25);
	BankAccount* account = customer->getAccount(suffix);
	if (account == nullptr)
	{
		cout << "There was a problem creating your account.\nTry again later.\n";
		return;
	}
	account->setDescription(acctDescription);
}

void Customers::makeDeposit(int customerId, AccountType accountType)
{
	displayMenuHeader("ACCOUNT DEPOSIT");
	BankCustomer* customer = getCustomer(customerId);
	if (customer == nullptr)
	{
		cout << "Your account no longer exists!\n";
		return;
	}

	int suffix = selectSubAccount(customer, accountType);
	if (EXIT_RESPONSE == EXIT_RESPONSE) { return; }

	customer->displayAccountInfo(suffix);
	cout << endl;
	double amount = requestUserInput("Deposit Amount ($100,000 max): $", 0, 100000);
	if (accountType == AccountType::Savings)
	{
		SavingAccount* saving = (SavingAccount*)customer->getAccount(suffix);
		saving->deposit(amount);
	}
	else if (accountType == AccountType::Checkings)
	{
		CheckingAccount* checking = (CheckingAccount*)customer->getAccount(suffix);
		checking->deposit(amount);
	}
	else
	{
		cout << "Unable to make deposit: unknown account type\n";
	}
	
	cout << endl;
	customer->displayAccountInfo(suffix);
}

void Customers::makeWithdrawal(int customerId, AccountType accountType)
{
	displayMenuHeader("ACCOUNT WITHDRAWAL");

	BankCustomer* customer = getCustomer(customerId);
	if (customer == nullptr)
	{
		cout << "Your account no longer exists!\n";
		return;
	}

	int suffix = selectSubAccount(customer, accountType);
	if (EXIT_RESPONSE == EXIT_RESPONSE) { return; }

	customer->displayAccountInfo(suffix);
	cout << endl;
	double amount = requestUserInput("Deposit Amount ($100,000 max): $", 0, 100000);
	if (accountType == AccountType::Savings)
	{
		SavingAccount* saving = (SavingAccount*)customer->getAccount(suffix);
		saving->deposit(amount);
	}
	else if (accountType == AccountType::Checkings)
	{
		CheckingAccount* checking = (CheckingAccount*)customer->getAccount(suffix);
		checking->deposit(amount);
	}
	else
	{
		cout << "Unable to make withdrawal: unknown account type\n";
	}

	cout << endl;
	customer->displayAccountInfo(suffix);
}

void Customers::useAccount(int customerId)
{
	displayMenuHeader("Customer Account Menu");

	AccountType acctType = selectAccountType();
	if (acctType == AccountType::Invalid) { return; }

	//SUBACCT_ACTIONS
	switch (makeSelection("What action do you want to do?", SUBACCT_ACTIONS, SUBACCT_ACTION_SIZE))
	{
	case DEPOSIT:
		makeDeposit(customerId, acctType);
		break;
	case WITHDRAW:
		makeWithdrawal(customerId, acctType);
		break;
	case CREATE:
		openSubAccount(customerId, acctType);
		break;
	case DELETE:
		closeSubAccount(customerId, acctType);
		break;
	default:	// Only thing left is to exit
		return;
	}
}

AccountType Customers::selectAccountType()
{
	const int savings = (static_cast<int>(AccountType::Savings) / 100) - 1;
	const int checking = (static_cast<int>(AccountType::Checkings) / 100) - 1;

	AccountType userResponse = AccountType::Invalid;

	switch (makeSelection("Select an account type", SUBACCT_TYPES, SUBACCT_SIZE))
	{
	case savings:
		userResponse = AccountType::Savings;
		break;
	case checking:
		userResponse = AccountType::Checkings;
		break;
	default:
		userResponse = AccountType::Invalid;
		break;
	}

	return userResponse;
}
int Customers::selectSubAccount(BankCustomer* customer, AccountType accountType)
{
	int suffix = EXIT_RESPONSE;	// Exit code

	BankAccount* subAcct = customer->findNextAccountOfType(accountType, -1);
	if (subAcct == nullptr)
	{
		cout << "You don't have any accounts of that type\n";
		return suffix;
	}

	cout << setw(10) << left << "Suffix";
	cout << setw(10) << left << "Balance";
	cout << setw(25) << left << "Description" << endl;
	cout << string(45, '-') << endl;

	// Display the sub-accounts to select from
	while (subAcct != nullptr)
	{
		cout << setw(10) << left << subAcct->getAccountSuffix();
		cout << "$" << setw(10) << left << subAcct->getBalance();
		cout << setw(25) << left << subAcct->getDescription().substr(0, 25) << endl;

		// Get the next sub-account
		subAcct = customer->findNextAccountOfType(accountType, subAcct->getAccountOffset());
	}
	cout << endl;

	// Select a sub-account
	do
	{
		cout << "Select a suffix (-1 to Exit): ";
		cin >> suffix;
		cin.ignore();
		cout << endl;
	} while (suffix != EXIT_RESPONSE && customer->suffixExists(suffix));

	return suffix;
}

void Customers::updateCustomerInfo(int customerId)
{
	BankCustomer* customer;
	displayMenuHeader("Update Customer Information Screen");

	customer = getCustomer(customerId);
	if (customer == nullptr)
	{
		cout << "You account no longer exists!\n";
		return;
	}

	customer->displayCustomerInfo();
	cout << endl;

	if (askYesNo("Update your name?"))
	{
		string firstName = requestUserInputString("New First Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);
		string lastName = requestUserInputString("New Last Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);
		
		customer->setFirstName(firstName);
		customer->setLastName(lastName);
	}
	if (askYesNo("Update your address?"))
	{
		updateCustomerAddress(customer);
	}

	customer->displayCustomerInfo();
	cout << endl << endl;
}

void Customers::displayMenuHeader(string header)
{
	cout << endl << endl << "***** " << header << " *****" << endl << endl;
}

int Customers::selectCustomerAction(int id)
{
	int customerId = id;
	cout << "\n\nCurrent Customer ID: ";
	if (customerId == STARTING_CUSTOMER_ID)
	{
		cout << "NONE";
	}
	else
	{
		cout << customerId;
	}
	cout << endl << endl;

	switch (makeSelection("Choose an action", ACCT_ACTIONS, ACCT_ACTION_SIZE))
	{
	case MANAGE_ACCT:
		if (customerId == STARTING_CUSTOMER_ID || askYesNo("\nSelect a new customer ID?"))
		{
			customerId = retrieveCustomerId();
		}

		if (customerId != STARTING_CUSTOMER_ID)
		{
			useAccount(customerId);
		}
		break;
	case UPDATE_ACCT:
		if (customerId == STARTING_CUSTOMER_ID || askYesNo("\nSelect a new customer ID?"))
		{
			customerId = retrieveCustomerId();
		}
		if (customerId != STARTING_CUSTOMER_ID)
		{
			updateCustomerInfo(customerId);
		}
		break;
	case CREATE:
		customerId = createCustomer();
		break;
	case DELETE:
		customerId = retrieveCustomerId();
		deleteCustomer(customerId);
		customerId = STARTING_CUSTOMER_ID;	// Account was just deleted
		break;
	case EXIT_RESPONSE:
		customerId = EXIT_RESPONSE;
		break;
	}

	return customerId;
}

void Customers::runApplication()
{
	cout << "Welcome to PFM - the GREATEST bank in the world!\n";
	cout << "As part of our goal to serve our stock holders\n";
	cout << "we charge excessive fees AND accept large government\n";
	cout << "bailouts!\n\n";
	
	int customerId = STARTING_CUSTOMER_ID;
	bool repeat = true;
	displayMenuHeader("Welcome to the main menu");

	while (customerId != EXIT_RESPONSE)
	{
		customerId = selectCustomerAction(customerId);
	};

	cout << endl << endl;
	cout << "Thank you for using our services!!\n";
}
