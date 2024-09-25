// Basic Banking Console System using File Handling and Error Handling.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function to validate Name
bool validName(string str)
{
    if (str.empty())
        return false;
    else
    {
        for (auto i : str)
        {
            if (!isalpha(i))
                return false;
        }
        return true;
    }
}
// Function to validate Phone Number
bool validNumber(string str)
{
    if (str.length() != 10)
        return false;
    else
    {
        for (auto i : str)
        {
            if (!isdigit(i))
                return false;
        }
        return true;
    }
}

// Function to get the last account number from file
double getLastAccountNumber()
{
    ifstream ifs("LastAccountNumber.txt");
    double lastAccountNumber = 1000;
    if (ifs)
    {
        ifs >> lastAccountNumber;
    }
    return lastAccountNumber;
}
// Function to update the last account number in file
void updateLastAccountNumber(double newAccountNumber)
{
    ofstream ofs("LastAccountNumber.txt");
    ofs << newAccountNumber;
}

// Account Class
class Account
{
private:
    string firstName, lastName, mobileNumber;
    double accountNumber, balance;
    static double accountNo;

public:
    Account() {}
    Account(string firstName, string lastName, string mobileNumber, double initialBalance);
    void setFristName(string str) { firstName = str; }
    void setLastName(string str) { lastName = str; }
    void setMobileNumber(string str) { mobileNumber = str; }
    void setBalance(double amount) { balance = amount; }
    void deposit(double deposit) { balance += deposit; }
    void withdrawal(double withdrawal) { balance -= withdrawal; }

    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    string getMobileNumber() { return mobileNumber; }
    double getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend fstream &operator<<(fstream &fs, Account &acc);
    friend fstream &operator>>(fstream &fs, Account &acc);
};
double Account::accountNo = getLastAccountNumber();

// Bank Class
class Bank
{
private:
public:
    Bank() {}
    void openAccount();
    void balanceEnquiry();
    void deposit();
    void withdrawal();
    void closeAccount();
    void showAllAccount();
};

//Main Method
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

// Account Class Constructor
Account::Account(string firstName, string lastName, string mobileNumber, double initialBalance)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->mobileNumber = mobileNumber;
    this->balance = initialBalance;
    this->accountNumber = ++accountNo;
    updateLastAccountNumber(accountNo);
}

// Function Overloading
ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.firstName << endl
        << acc.lastName << endl
        << acc.mobileNumber << endl
        << acc.accountNumber << endl
        << acc.balance << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.firstName >> acc.lastName >> acc.mobileNumber >> acc.accountNumber >> acc.balance;
    return ifs;
}
fstream &operator<<(fstream &fs, Account &acc)
{
    fs << acc.firstName << endl
       << acc.lastName << endl
       << acc.mobileNumber << endl
       << acc.accountNumber << endl
       << acc.balance << endl;
    return fs;
}
fstream &operator>>(fstream &fs, Account &acc)
{
    fs >> acc.firstName >> acc.lastName >> acc.mobileNumber >> acc.accountNumber >> acc.balance;
    return fs;
}

// Methods of Bank Class
void Bank::openAccount()
{
    string firstName, lastName, mobileNumber;
    double initialBalance;
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
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Details" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    else
    {
        ofstream ofs("Banking.txt", ios::app);
        if (!ofs)
        {
            cout << "---------------------------------------------" << endl;
            cerr << "Failed to open file." << endl;
            cout << "---------------------------------------------" << endl;
            ofs.close();
            return;
        }
        Account acc(firstName, lastName, mobileNumber, initialBalance);
        ofs << acc;
        cout << "Account Created Successfully" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Account Number is : " << acc.getAccountNumber() << endl;
        cout << "Name is : " << acc.getFirstName() << " " << acc.getLastName() << endl;
        cout << "Mobile Number is : " << acc.getMobileNumber() << endl;
        cout << "---------------------------------------------" << endl;
        ofs.close();
    }
}
void Bank::balanceEnquiry()
{
    bool found = false;
    double accountNumber;
    cout << "Enter Account Number to check : ";
    cin >> accountNumber;
    Account acc;
    ifstream ifs("Banking.txt");
    if (!ifs)
    {
        cout << "---------------------------------------------" << endl;
        cerr << "Failed to open file." << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    while (ifs >> acc)
    {
        if (acc.getAccountNumber() == accountNumber)
        {
            cout << "---------------------------------------------" << endl;
            cout << "Balance is : " << acc.getBalance() << endl;
            cout << "---------------------------------------------" << endl;
            return;
        }
    }
    if (!found)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number : " << accountNumber << endl;
        cout << "---------------------------------------------" << endl;
    }
    ifs.close();
}
void Bank::deposit()
{
    bool found = false;
    double accountNumber, deposit;
    cout << "Enter the Account Number to deposit in : ";
    cin >> accountNumber;
    if (accountNumber < 1000)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
    cout << "Enter the amount to deposit : ";
    cin >> deposit;
    if (deposit <= 0)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Entered invalid amount" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    fstream file("Banking.txt", ios::in | ios::out);
    ofstream temp("temp.txt");
    if (!file || !temp)
    {
        cout << "---------------------------------------------" << endl;
        cerr << "Failed to open file." << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    Account acc;
    while (file >> acc)
    {
        if (acc.getAccountNumber() == accountNumber)
        {
            acc.deposit(deposit);
            found = true;
        }
        temp << acc;
    }
    file.close();
    temp.close();
    remove("Banking.txt");
    rename("temp.txt", "Banking.txt");
    if (found)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Deposit of " << deposit << " is successfull" << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void Bank::withdrawal()
{
    bool found = false;
    double accountNumber, withdrawal;
    cout << "Enter the Account Number to withdrawal from: ";
    cin >> accountNumber;
    if (accountNumber < 1000)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
    cout << "Enter the amount to withdrawal : ";
    cin >> withdrawal;
    if (withdrawal <= 0)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Entered invalid amount" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    fstream file("Banking.txt", ios::in | ios::out);
    ofstream temp("temp.txt");
    if (!file || !temp)
    {
        cout << "---------------------------------------------" << endl;
        cerr << "Failed to open file." << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    Account acc;
    while (file >> acc)
    {
        if (acc.getAccountNumber() == accountNumber)
        {
            acc.withdrawal(withdrawal);
            found = true;
        }
        temp << acc;
    }
    file.close();
    temp.close();
    remove("Banking.txt");
    rename("temp.txt", "Banking.txt");
    if (found)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Withdrawal of " << withdrawal << " is successfull" << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void Bank::closeAccount()
{
    bool found = false;
    double accountNumber;
    cout << "Enter the Account Number to withdrawal from: ";
    cin >> accountNumber;
    if (accountNumber < 0)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
    fstream file("Banking.txt", ios::in | ios::out);
    ofstream temp("temp.txt");
    if (!file || !temp)
    {
        cout << "---------------------------------------------" << endl;
        cerr << "Failed to open file." << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    Account acc;
    while (file >> acc)
    {
        if (acc.getAccountNumber() == accountNumber)
        {
            acc.setFristName("null");
            acc.setLastName("null");
            acc.setMobileNumber("null");
            acc.setBalance(0);
            found = true;
        }
        temp << acc;
    }
    file.close();
    temp.close();
    remove("Banking.txt");
    rename("temp.txt", "Banking.txt");
    if (found)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Account closed successfully." << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Invalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void Bank::showAllAccount()
{
    Account acc;
    ifstream ifs("Banking.txt");
    if (!ifs)
    {
        cout << "---------------------------------------------" << endl;
        cerr << "Failed to open file." << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    while (ifs >> acc)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Account Number is : " << acc.getAccountNumber() << endl;
        cout << "Name is : " << acc.getFirstName() << " " << acc.getLastName() << endl;
        cout << "Mobile Number is : " << acc.getMobileNumber() << endl;
        cout << "---------------------------------------------" << endl;
    }
    ifs.close();
}