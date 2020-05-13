#include "Customers.h"
#include "BankCustomer.h"


// Destructor is necessary to release the memory allocated for customer records
Customers::~Customers()
{
	// Delete customer data
	map<int, BankCustomer*>::iterator cIter;

	for (cIter = _customers.begin(); cIter != _customers.end(); cIter++)
	{
		delete (cIter->second);
	}
}

/*****************************************************************************************************/
/*                                User Input Functions                                               */

// Request user input as a string
// question: The question to ask the user.
// minLength: The minimum length of the input string. Default is 1
// maxLength: The maximum length of the input string. Default is 255
string Customers::requestUserInputString(string question, unsigned int minLength = 1, unsigned int maxLength = 255)
{
	string response;
	bool invalidLength = true;

	// Ask the question
	cout << question;

	// Get the answer. Repeat until a valid response provided
	do
	{
		getline(cin, response);

		// Verify user input is valid
		invalidLength = (minLength > response.length() || maxLength < response.length());
		if (invalidLength)
		{
			cout << "Min length: " << minLength << ", Max Length: " << maxLength << endl;
		}
	} while (invalidLength);

	return response;
}

// Ask the user a yes/no question
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

// Request a number from the user input
// question: The question to ask the user
// minNumber: The min number to accept
// maxNumber: The maximum number to accept
int Customers::requestUserInput(string question, int minNumber, int maxNumber)
{
	int response;

	cout << question;
	do
	{
		cin >> response;
		cin.ignore();
	} while (response < minNumber || response > maxNumber);

	return response;
}


// Request a decimal amount from the user.
// question: The question to ask the user
// minNumber: The min number to accept
// maxNumber: The maximum number to accept
double Customers::requestUserInput(string question, double minAmount, double maxAmount)
{
	double response;

	cout << question;
	do
	{
		cin >> response;
		cin.ignore();
	} while (response < minAmount || response > maxAmount);

	return response;
}

// Request the user make a selection from a menu. Return the menu selection
// prompt: The prompt to display before the menu selections
// selection[]: The user selections as string array
// selectionSize: The size of the selection array
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


/*****************************************************************************************************/
/*                                Customer Account Functions                                         */
/*****************************************************************************************************/
// ------------------------------- Actions On Customer Account

// Update the customer information using user input
void Customers::updateCustomerInfo(int customerId)
{
	BankCustomer* customer;
	displayMenuHeader("Update Customer Information Screen");

	// Get the customer
	customer = getCustomer(customerId, true);
	if (customer == nullptr) { return; }

	// Display current information
	customer->displayCustomerInfo();

	// Allow the user to udpate either their name or their address
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

	// Display the customer information and address after updating
	customer->displayCustomerInfo();
	customer->displayCustomerAddr();
}

// Update the customer address from user input
void Customers::updateCustomerAddress(BankCustomer* customer)
{
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

// Create a new customer account
int Customers::createCustomer()
{
	int customerId = STARTING_CUSTOMER_ID;
	string firstName, lastName;
	string address1, address2;
	string city, state, zip;


	// Get required information to create a customer account
	firstName = requestUserInputString("First Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);
	lastName = requestUserInputString("Last Name: ", BankCustomer::MIN_NAME_LENGTH, BankCustomer::MAX_NAME_LENGTH);
	// Create account
	BankCustomer* customer = new BankCustomer(getNextCustomerId(), firstName, lastName);

	// Verify the creation worked
	if (customer != nullptr)
	{
		updateCustomerAddress(customer);
		customerId = customer->getAccountNum();
		_customers[customerId] = customer;

		// Verify the new customer is in the system
		if (customerExists(customerId))
		{
			cout << "Your new account ID is " << customerId << endl;
			customer->displayCustomerInfo();
			customer->displayCustomerAddr();
		}
		else
		{
			cout << "There was a problem adding your account to the system!\n";
		}
	}
	else
	{
		cout << "There was a problem creating your account.\nTry again later.\n";
	}

	return customerId;
}

// Delete the specified customer record
void Customers::deleteCustomer(int customerId)
{
	if (customerExists(customerId))
	{
		// Delete the object from heap
		delete _customers[customerId];

		// Remove the entry from the map
		_customers.erase(customerId);
	}
}

// -------------------------------- Customer Helper Functions
// Request the customer ID from the user
int Customers::retrieveCustomerId()
{
	bool customerFound = false;
	int accountNum;

	// Keep asking for a valid customer ID until one is provided
	// or the user enters 10000
	do
	{
		// Get customer number
		accountNum = requestUserInput(ENTER_CUST_ID, STARTING_CUSTOMER_ID, INT_MAX);

		if (accountNum != STARTING_CUSTOMER_ID)
		{
			customerFound = customerExists(accountNum);
			// Retrieve customer
			if (!customerFound)
			{
				cout << "Unable to find your account.\n";
			}
		}
	} while (!customerFound);

	return accountNum;
}



/*****************************************************************************************************/
/*                                Bank Account Functions                                             */

// -------------------------------- Account Action Functions
void Customers::closeSubAccount(int customerId, AccountType accountType)
{
	displayMenuHeader("Close Account");
	BankCustomer* customer = getCustomer(customerId, true);
	if (customer == nullptr) { return; }

	// Get account suffix
	int suffix = selectSubAccount(customer, accountType);
	if (suffix == EXIT_RESPONSE) { return; }

	// Display account info before deleting
	cout << "Deleting account: " << suffix << endl;
	customer->displayAccountInfo(suffix);

	// Verify they really want to delete the account
	if (askYesNo("Are you SURE you want to delete this account?"))
	{
		customer->deleteSubAccount(suffix);
	}

	// Display remaining accounts
	if (accountType == AccountType::Savings)
	{
		customer->displaySavingsAccounts();
	}
	else if (accountType==AccountType::Checkings)
	{
		customer->displayCheckingsAccounts();
	}
}

void Customers::openSubAccount(int customerId, AccountType accountType)
{
	displayMenuHeader("Account Creation");

	// Retrieve the customer record
	BankCustomer* customer = getCustomer(customerId, true);
	if (customer == nullptr) { return; }

	// Request new account information
	// Limit opening balance to $100,000
	double openingBalance = requestUserInput("Opening Balance: $", MIN_AMOUNT, MAX_AMOUNT);
	double apr = requestUserInput("Annual Percentage Rate: ", MIN_APR, MAX_APR);
	
	// Create the account
	int suffix = customer->createSubAccount(accountType, openingBalance, apr);
	
	// Verify the account was created
	if (!customer->suffixExists(suffix))
	{
		cout << "\n\nThere was a problem creating your account.\nTry again later.\n";
		return;
	}
	
	// Retrieve the account and finish setting it up
	BankAccount* account = customer->getAccount(suffix);
	
	// Verify the account was saved to the system
	if (account == nullptr)
	{
		cout << "There was a problem saving your account.\n";
		return;
	}

	string acctDescription = requestUserInputString("Account Description (25 chars or less): ", 0, 25);
	account->setDescription(acctDescription);

	// Display the new account information
	customer->displayAccountInfo(suffix);
}

void Customers::makeDeposit(int customerId, AccountType accountType)
{
	displayMenuHeader("ACCOUNT DEPOSIT");

	// Retrieve customer account and verify it exists
	BankCustomer* customer = getCustomer(customerId, true);
	if (customer == nullptr) { return; }

	// Select from available bank accounts
	int suffix = selectSubAccount(customer, accountType);
	if (suffix == EXIT_RESPONSE) { return; }

	// Get deposit amount and make the deposit
	double amount = requestUserInput("Deposit Amount ($100,000 max): $", MIN_AMOUNT, MAX_AMOUNT);
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
	
	// Display the new account balance
	customer->displayAccountInfo(suffix);
}

void Customers::makeWithdrawal(int customerId, AccountType accountType)
{
	displayMenuHeader("ACCOUNT WITHDRAWAL");

	// Retrieve customer account and verify it exists
	BankCustomer* customer = getCustomer(customerId, true);
	if (customer == nullptr) { return; }

	// Select from available bank accounts
	int suffix = selectSubAccount(customer, accountType);
	if (suffix == EXIT_RESPONSE) { return; }

	// Display existing balance information
	customer->displayAccountInfo(suffix);

	// Get withdrawal amount and make the withdrawal
	double amount = requestUserInput("\nWithdrawal Amount ($100,000 max): $", MIN_AMOUNT, MAX_AMOUNT);
	if (accountType == AccountType::Savings)
	{
		SavingAccount* saving = (SavingAccount*)customer->getAccount(suffix);
		saving->withdrawal(amount);
	}
	else if (accountType == AccountType::Checkings)
	{
		CheckingAccount* checking = (CheckingAccount*)customer->getAccount(suffix);
		checking->withdrawal(amount);
	}
	else
	{
		cout << "Unable to make withdrawal: unknown account type\n";
	}

	// Display new balance information
	customer->displayAccountInfo(suffix);
}


// ------------------------------------ Account Helper Functions
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


// ----------------------- Bank Account Helper Functions
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
	} while (suffix != EXIT_RESPONSE && !customer->suffixExists(suffix));

	return suffix;
}


/*****************************************************************************************************/
/*                                   MAINTENANCE Functions                                           */

void Customers::performMonthlyMainenance(int customerId)
{
	displayMenuHeader("Monthly Maintenance");

	// Retrieve customer account and verify it exists
	BankCustomer* customer = getCustomer(customerId);
	if (customer == nullptr)
	{
		cout << "Your account no longer exists!\n";
		return;
	}

	// Process saving accounts
	BankAccount* account = customer->getFirstSavingAccount();
	while (account != nullptr)
	{
		account->monthlyProc();
		account = customer->getNextSavingAccount(account->getAccountOffset());
	}

	// Process checking accounts
	account = customer->getFirstCheckingAccount();
	while (account != nullptr)
	{
		account->monthlyProc();
		account = customer->getNextCheckingAccount(account->getAccountOffset());
	}
}



/*****************************************************************************************************/
/*                               Driver & Helper Functions                                           */

// Display menu header
void Customers::displayMenuHeader(string header)
{
	cout << endl << "***** " << header << " *****" << endl << endl;
}

// Get the specified bank account
BankCustomer* Customers::getCustomer(int accountNum, bool displayError)
{
	if (_customers.count(accountNum))
	{
		return _customers[accountNum];
	}

	if (displayError)
	{
		cout << "Your account no longer exists!\n";
	}

	return nullptr;
}

// Bank Account Menu: Main Menu Option 1
// Select from 4 Options:
// Option 1: Deposit - Savings or Checking
// Option 2: Withdrawal - Savings or Checking
// Option 3: Create a NEW Bank Account - Savings or Checking
// Option 4: Delete a Bank Account - Savings or Checking
void Customers::selectAccountAction(int customerId)
{
	int userResponse;
	AccountType origType, acctType;

	// Request what type of bank account to work with - Savings or Checking
	origType = acctType = selectAccountType();
	if (acctType == AccountType::Invalid) { return; }

	do
	{
		displayMenuHeader(BankAccount::accountTypeToName(acctType) + " Account Menu");
		userResponse = makeSelection("What action do you want to do?", SUBACCT_ACTIONS, SUBACCT_ACTION_SIZE);
		// Select and perform requested action
		switch (userResponse)
		{
		case DEPOSIT:
			makeDeposit(customerId, acctType);
			break;
		case WITHDRAW:
			makeWithdrawal(customerId, acctType);
			break;
		case CREATE_ACCT:
			openSubAccount(customerId, acctType);
			break;
		case DELETE_ACCT:
			closeSubAccount(customerId, acctType);
			break;
		case CHG_TYPE:
			acctType = selectAccountType();
			if (acctType == AccountType::Invalid)
			{
				acctType = origType;
			}
			else
			{
				origType = acctType;
			}
			break;
		}
		cout << endl;
	} while (userResponse != EXIT_RESPONSE);
}

// Main Menu
// Offer 4 options
// Option 1: Manage Bank Accounts - Create, Delete, Deposit, Withdrawal
// Option 2: Update Customer Record
// Option 3: Create a NEW Customer Record
// Option 4: Delete a Customer Record
int Customers::selectCustomerAction(int id)
{
	int customerId = id;
	displayMenuHeader("Welcome to the main menu");
	cout << "Current Customer ID: ";
	if (customerId == STARTING_CUSTOMER_ID)
	{
		cout << "NONE\n\n";
	}
	else
	{
		cout << customerId << endl << endl;
	}

	switch (makeSelection("Choose an action", ACCT_ACTIONS, ACCT_ACTION_SIZE))
	{
	case MANAGE_ACCT:
		if (customerId != STARTING_CUSTOMER_ID)
		{
			selectAccountAction(customerId);
		}
		break;
	case UPDATE_CUST:
		if (customerId != STARTING_CUSTOMER_ID)
		{
			updateCustomerInfo(customerId);
		}
		break;
	case CREATE_CUST:
		customerId = createCustomer();
		break;
	case DELETE_CUST:
		if (customerId != STARTING_CUSTOMER_ID)
		{
			deleteCustomer(customerId);
			customerId = STARTING_CUSTOMER_ID;	// Account was just deleted
		}
		break;
	case CHANGE_ID:
		customerId = retrieveCustomerId();
		break;
	case MNTH_PROC:
		if (customerId != STARTING_CUSTOMER_ID)
		{
			performMonthlyMainenance(customerId);
		}
		break;
	case EXIT_RESPONSE:
		customerId = EXIT_RESPONSE;
		break;
	}

	return customerId;
}

// Run the application
void Customers::runApplication()
{
	cout << "Welcome to PFM - the GREATEST bank in the world!\n";
	cout << "As part of our goal to serve our stock holders\n";
	cout << "we charge excessive fees AND accept large government\n";
	cout << "bailouts!\n\n";
	
	int customerId = STARTING_CUSTOMER_ID;
	bool repeat = true;

	while (customerId != EXIT_RESPONSE)
	{
		customerId = selectCustomerAction(customerId);
		cout << endl << string(25, '*') << endl;
	};

	cout << endl << endl;
	cout << "Thank you for using our services!!\n";
}