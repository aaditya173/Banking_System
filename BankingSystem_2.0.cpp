// Basic Banking Console System using Oops Concept with Data Structure Vector.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
};
double Account::accountNo = -1;

class Bank
{
private:
    vector<Account> accounts;

public:
    Bank() {}
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

Account::Account(string firstName, string lastName, string mobileNumber, double initialBalance)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->mobileNumber = mobileNumber;
    this->balance = initialBalance;
    this->accountNumber = ++accountNo;
}

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
        cout << "Invalid Details" << endl;
        return;
    }
    else
    {
        accounts.push_back(Account(firstName, lastName, mobileNumber, initialBalance));
        cout << "Account Created Successfully" << endl;
        vector<Account>::iterator iter = accounts.end()-1;
        cout << "---------------------------------------------" << endl;
        cout << "Account Number is : " << (*iter).getAccountNumber() << endl;
        cout << "Name is : " << (*iter).getFirstName() << " " << (*iter).getLastName() << endl;
        cout << "Mobile Number is : " << (*iter).getMobileNumber() << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void Bank::balanceEnquiry()
{
    bool found = false;
    double accountNumber;
    cout << "Enter Account Number to check : ";
    cin >> accountNumber;
    for (auto i : accounts)
    {
        if (i.getAccountNumber() == accountNumber)
        {
            cout << "Balance is : " << i.getBalance() << endl;
            return;
        }
    }
    if (!found)
        cout << "Invalid Account Number" << endl;
}
void Bank::deposit()
{
    bool found = false;
    double accountNumber, deposit;
    cout << "Enter the Account Number to deposit : ";
    cin >> accountNumber;
    for (auto i : accounts)
    {
        if (i.getAccountNumber() == accountNumber)
        {
            cout << "Enter the amount to deposit : ";
            cin >> deposit;
            if (deposit <= 0)
            {
                cout << "Entered invalid amount" << endl;
                return;
            }
            else
            {
                accounts[accountNumber].deposit(deposit);
                cout << "Deposit of " << deposit << " is successfull" << endl;
                return;
            }
        }
    }
    if (!found)
        cout << "Invalid Account Number" << endl;
}
void Bank::withdrawal()
{
    bool found = false;
    double accountNumber, withdrawal;
    cout << "Enter the Account Number to withdrawal : ";
    cin >> accountNumber;
    for (auto i : accounts)
    {
        if (i.getAccountNumber() == accountNumber)
        {
            cout << "Enter the amount to withdrawal : ";
            cin >> withdrawal;
            if (withdrawal <= 0)
            {
                cout << "Entered invalid amount" << endl;
                return;
            }
            else if (withdrawal > accounts[accountNumber].getBalance())
            {
                cout << "Insufficent Funds" << endl;
                return;
            }
            else
            {
                accounts[accountNumber].withdrawal(withdrawal);
                cout << "Withdrawal of " << withdrawal << " is successfull" << endl;
                return;
            }
        }
    }
    if (!found)
        cout << "Invalid Account Number" << endl;
}
void Bank::closeAccount()
{
    bool found = false;
    int accountNumber;
    cout << "Enter the Account Number to close : ";
    cin >> accountNumber;
    for (auto i : accounts)
    {
        if (i.getAccountNumber() == accountNumber)
        {
            accounts[accountNumber].setFristName("null");
            accounts[accountNumber].setLastName("null");
            accounts[accountNumber].setMobileNumber("null");
            accounts[accountNumber].setBalance(0);
            cout << "Account closed successfull" << endl;
            return;
        }
    }
    if (!found)
        cout << "Invalid Account Number" << endl;
}
void Bank::showAllAccount()
{
    if (accounts.empty())
    {
        cout << "No Record Found" << endl;
        return;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        vector<Account>::iterator iter = accounts.begin();
        while (iter != accounts.end())
        {
            cout << "Account Number is : " << (*iter).getAccountNumber() << endl;
            cout << "Name is : " << (*iter).getFirstName() << " " << (*iter).getLastName() << endl;
            cout << "Mobile Number is : " << (*iter).getMobileNumber() << endl;
            cout << "---------------------------------------------" << endl;
            iter++;
        }
    }
}
