
// #include <iostream>
// #include <mysql.h>
// #include <mysqld_error.h>
// #include <windows.h>
// #include <sstream>
//
// using namespace std;
//
// const char* HOST = "localhost";
// const char* USER = "root";
// const char* PASSWORD = "aditya";
// const char* DB = "banking_system";
//
// int main() {
//	MYSQL* conn;
//	conn = mysql_init(NULL);
//
//	if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DB, 3306, NULL, 0)) {
//		cout << "Error: " << mysql_error(conn) << endl;
//	}
//	else {
//		cout << "Logged In Database!" << endl;
//	}
//
//	return 0;
// }

// Disable specific warning
/*#pragma warning(push)
#pragma warning(disable : 26495)*/

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
using namespace std;

// Database connection parameters
const string DB_URL = "tcp://127.0.0.1:3306";
const string USER = "root";				  // MySQL username
const string PASSWORD = "aditya";		  // MySQL password
const string DATABASE = "banking_system"; // database name

// Validation Functions
static bool validName(string str)
{
	if (str.empty())
		return false;
	for (auto i : str)
	{
		if (!isalpha(i))
			return false;
	}
	return true;
}
static bool validNumber(string str)
{
	if (str.length() != 10)
		return false;
	for (auto i : str)
	{
		if (!isdigit(i))
			return false;
	}
	return true;
}

class Account
{
public:
	Account();
	Account(string firstName, string lastName, string mobileNumber, double balance);
	~Account();
	int getAccountNumber() const { return accountNumber; }
	string getFirstName() { return firstName; }
	string getLastName() { return lastName; }
	string getMobileNumber() { return mobileNumber; }
	double getBalance() const { return balance; }
	void setFirstName(string fName) { firstName = fName; }
	void setLastName(string lName) { lastName = lName; }
	void setMobileNumber(string mNumber) { mobileNumber = mNumber; }
	void setBalance(double bal) { balance = bal; }

private:
	int accountNumber;
	string firstName, lastName, mobileNumber;
	double balance;
};

class Bank
{
private:
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;

public:
	Bank();
	~Bank();
	void openAccount();
	void balanceEnquiry();
	void deposit();
	void withdrawal();
	void closeAccount();
	void showAllAccount();
};

int main()
{
	Bank bank;
	int choice;
	cout << "Banking Console System" << endl;
	cout << "---------------------------------------------" << endl;
	do
	{
		cout << "Select one option below" << endl;
		cout << "1. Open Account" << endl;
		cout << "2. Balance Enquiry" << endl;
		cout << "3. Deposit" << endl;
		cout << "4. Withdrawal" << endl;
		cout << "5. Close an Account" << endl;
		cout << "6. Show all Account" << endl;
		cout << "7. Quit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			bank.openAccount();
			break;
		case 2:
			bank.balanceEnquiry();
			break;
		case 3:
			bank.deposit();
			break;
		case 4:
			bank.withdrawal();
			break;
		case 5:
			bank.closeAccount();
			break;
		case 6:
			bank.showAllAccount();
			break;
		case 7:
			cout << "Exit Successful" << endl;
			break;
		default:
			cout << "Wrong Choice" << endl;
			break;
		}
	} while (choice != 7);
	return 0;
}

Account::Account()
{
}
Account::Account(string firstName, string lastName, string mobileNumber, double balance)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->mobileNumber = mobileNumber;
	this->balance = balance;
}
Account::~Account()
{
}

Bank::Bank()
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect(DB_URL, USER, PASSWORD);
	con->setSchema(DATABASE);
}
Bank::~Bank()
{
	delete con;
}

void Bank::openAccount()
{
	// SQL for inserting a new account
	/*int accountNumber;*/
	string firstName, lastName, mobileNumber;
	double initialBalance;

	/*cout << "Enter the Account Number : ";
	cin >> accountNumber;*/
	cout << "Enter First Name : ";
	cin >> firstName;
	cout << "Enter Last Name : ";
	cin >> lastName;
	cout << "Enter Mobile Number : ";
	cin >> mobileNumber;
	cout << "Enter Initial Balance : ";
	cin >> initialBalance;

	if (!validNumber(mobileNumber) || !validName(firstName) || !validName(lastName))
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|				Invalid Details!		 	   |" << endl;
		cout << "+---------------------------------------------+" << endl;
		return;
	}

	// Prepare SQL statement
	// sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO customer (Account_Number, First_Name, Last_Name, Mobile_Number, Balance) VALUES (?, ?, ?, ?, ?)"); // for non auto-increment
	sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO customer (First_Name, Last_Name, Mobile_Number, Balance) VALUES (?, ?, ?, ?)");
	// pstmt->setInt(1, getNextAccountNumber()); // using function
	// pstmt->setInt(1, accountNumber);  // using user input
	pstmt->setString(1, firstName);		 // pstmt->setString(2, firstName);
	pstmt->setString(2, lastName);		 // pstmt->setString(3, lastName);
	pstmt->setString(3, mobileNumber);	 // pstmt->setString(4, mobileNumber);
	pstmt->setDouble(4, initialBalance); // pstmt->setDouble(5, initialBalance);
	pstmt->execute();					 // OR pstmt->executeUpdate();
	cout << "+---------------------------------------------+" << endl;
	cout << "|        Account Created Successfully!        |" << endl;
	cout << "+---------------------------------------------+" << endl;

	delete pstmt;
}
void Bank::balanceEnquiry()
{
	int accountNumber;
	cout << "Enter Account Number to check : ";
	cin >> accountNumber;

	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;
	pstmt = con->prepareStatement("SELECT * FROM customer WHERE Account_Number=?");
	pstmt->setInt(1, accountNumber);
	res = pstmt->executeQuery();
	if (res->next())
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|Balance is : " << res->getDouble("Balance") << "|" << endl;
		cout << "+---------------------------------------------+" << endl;
	}
	else
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|            Invalid Account Number!          |" << endl;
		cout << "+---------------------------------------------+" << endl;
	}

	delete res;
	delete pstmt;
}
void Bank::deposit()
{
	int accountNumber;
	double depositAmount;
	cout << "Enter the Account Number to deposit : ";
	cin >> accountNumber;
	cout << "Enter the amount to deposit : ";
	cin >> depositAmount;

	if (depositAmount <= 0)
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|           Invalid deposit amount!           |" << endl;
		cout << "+---------------------------------------------+" << endl;
		return;
	}

	sql::PreparedStatement *pstmt = con->prepareStatement("SELECT EXISTS (SELECT 1 FROM customer WHERE Account_Number = ?)");
	pstmt->setInt(1, accountNumber);
	sql::ResultSet *res = pstmt->executeQuery();

	if (res->next())
	{
		bool exists = res->getInt(1);
		if (exists)
		{
			pstmt = con->prepareStatement("UPDATE customer SET Balance = Balance + ? WHERE Account_Number = ?");
			pstmt->setDouble(1, depositAmount);
			pstmt->setInt(2, accountNumber);
			pstmt->executeUpdate();
			cout << "+---------------------------------------------+" << endl;
			cout << "|            Deposit successful!              |" << endl;
			cout << "+---------------------------------------------+" << endl;
		}
		else
		{
			cout << "+---------------------------------------------+" << endl;
			cout << "|        Invalid Account Number!              |" << endl;
			cout << "+---------------------------------------------+" << endl;
		}
	}

	delete res;
	delete pstmt;
}
void Bank::withdrawal()
{
	int accountNumber;
	double withdrawalAmount;
	cout << "Enter the Account Number to withdrawal : ";
	cin >> accountNumber;
	cout << "Enter the amount to withdrawal : ";
	cin >> withdrawalAmount;

	if (withdrawalAmount <= 0)
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|         Invalid withdrawal amount!          |" << endl;
		cout << "+---------------------------------------------+" << endl;
		return;
	}

	sql::PreparedStatement *pstmt;
	pstmt = con->prepareStatement("SELECT * FROM customer WHERE Account_Number = ?");
	pstmt->setInt(1, accountNumber);
	sql::ResultSet *res = pstmt->executeQuery();

	if (res->next())
	{
		double currentBalance = res->getDouble("Balance");
		if (currentBalance >= withdrawalAmount)
		{
			delete pstmt;
			pstmt = con->prepareStatement("UPDATE customer SET Balance = Balance - ? WHERE Account_Number = ?");
			pstmt->setDouble(1, withdrawalAmount);
			pstmt->setInt(2, accountNumber);
			pstmt->executeUpdate();
			cout << "+---------------------------------------------+" << endl;
			cout << "|           Withdrawal successful!            |" << endl;
			cout << "+---------------------------------------------+" << endl;
		}
		else
		{
			cout << "+---------------------------------------------+" << endl;
			cout << "|             Insufficient funds!             |" << endl;
			cout << "+---------------------------------------------+" << endl;
		}
	}
	else
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|            Invalid Account Number!          |" << endl;
		cout << "+---------------------------------------------+" << endl;
	}

	delete res;
	delete pstmt;
}
void Bank::closeAccount()
{
	int accountNumber;
	cout << "Enter the Account Number to close: ";
	cin >> accountNumber;

	sql::PreparedStatement *pstmt;
	pstmt = con->prepareStatement("DELETE FROM customer WHERE Account_Number = ?");
	pstmt->setInt(1, accountNumber);
	pstmt->executeUpdate();
	cout << "+---------------------------------------------+" << endl;
	cout << "|        Account closed successfully!         |" << endl;
	cout << "+---------------------------------------------+" << endl;

	delete pstmt;
}
void Bank::showAllAccount()
{
	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;
	pstmt = con->prepareStatement("SELECT * FROM customer");
	res = pstmt->executeQuery();

	if (!res->next())
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|              No Records Found!              |" << endl;
		cout << "+---------------------------------------------+" << endl;
	}
	else
	{
		do
		{
			cout << "+---------------------------------------------+" << endl;
			cout << "|Account Number: " << res->getInt("Account_Number") << endl;
			cout << "|Name: " << res->getString("First_Name") << " " << res->getString("Last_Name") << endl;
			cout << "|Mobile Number: " << res->getString("Mobile_Number") << endl;
			cout << "|Balance: " << res->getDouble("Balance") << endl;
			cout << "+---------------------------------------------+" << endl;
		} while (res->next());
	}

	delete res;
	delete pstmt;
}