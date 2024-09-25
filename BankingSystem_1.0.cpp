// Basic Banking Console System using Array Data Structure.
#include <iostream>
using namespace std;

static int accountNo = -1;

struct Account
{
    string firstName, lastName;
    string mobileNo;
    int accountNumber, balance;
} acc[500];

void openAccount();
void balanceEnquiry();
void deposit();
void withdrawal();
void closeAccount();
void showAllAccount();

int main()
{
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
            openAccount();
            break;
        case 2:
            balanceEnquiry();
            break;
        case 3:
            deposit();
            break;
        case 4:
            withdrawal();
            break;
        case 5:
            closeAccount();
            break;
        case 6:
            showAllAccount();
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

void openAccount()
{
    string firstName, lastName, mobile;
    cout << "Enter First Name : ";
    cin >> firstName;
    cout << "Enter Last Name : ";
    cin >> lastName;
    cout << "Enter Mobile Number : ";
    cin >> mobile;
    if (mobile.length() != 10)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Envalid Mobile Number" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
    else
    {
        accountNo++;
        acc[accountNo].firstName = firstName;
        acc[accountNo].lastName = lastName;
        acc[accountNo].mobileNo = mobile;
        acc[accountNo].accountNumber = accountNo;
        acc[accountNo].balance = 0;
        cout << "Account Created Successfully" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Name is : " << acc[accountNo].firstName << " " << acc[accountNo].lastName << endl;
        cout << "Account Number is : " << acc[accountNo].accountNumber << endl;
        cout << "Mobile Number is : " << acc[accountNo].mobileNo << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void balanceEnquiry()
{
    int ac;
    cout << "Enter Account Number to check : ";
    cin >> ac;
    if (ac >= 0 && ac <= accountNo)
    {
        cout << "---------------------------------------------" << endl;
        cout << "Balance is : " << acc[ac].balance << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Envalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
}
void deposit()
{
    int ac, deposit;
    cout << "Enter the Account Number to deposit : ";
    cin >> ac;
    if (ac >= 0 && ac <= accountNo)
    {
        cout << "Enter the amount to deposit : ";
        cin >> deposit;
        acc[ac].balance += deposit;
        cout << "---------------------------------------------" << endl;
        cout << "Deposit of " << deposit << " is successfull" << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Envalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
}
void withdrawal()
{
    int ac, withdrawal;
    cout << "Enter the Account Number to withdrawal : ";
    cin >> ac;
    if (ac >= 0 && ac <= accountNo)
    {
        cout << "Enter the amount to withdrawal : ";
        cin >> withdrawal;
        if (acc[ac].balance >= withdrawal)
        {
            acc[ac].balance -= withdrawal;
            cout << "---------------------------------------------" << endl;
            cout << "Withdrawal of " << withdrawal << " is successfull" << endl;
            cout << "---------------------------------------------" << endl;
        }
        else
        {
            cout << "---------------------------------------------" << endl;
            cout << "Insufficient Balance" << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Envalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
}
void closeAccount()
{
    int ac;
    cout << "Enter the Account Number to close : ";
    cin >> ac;
    if (ac >= 0 && ac <= accountNo)
    {
        acc[ac].firstName = acc[ac].lastName = acc[ac].mobileNo = "null";
        acc[ac].balance = 0;
        cout << "---------------------------------------------" << endl;
        cout << "Account closed successfull" << endl;
        cout << "---------------------------------------------" << endl;
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "Envalid Account Number" << endl;
        cout << "---------------------------------------------" << endl;
        return;
    }
}
void showAllAccount()
{
    if (accountNo >= 0)
    {
        for (int i = 0; i <= accountNo; i++)
        {
            cout << "---------------------------------------------" << endl;
            cout << "Name is : " << acc[i].firstName << " " << acc[i].lastName << endl;
            cout << "Account Number is : " << acc[i].accountNumber << endl;
            cout << "Mobile Number is : " << acc[i].mobileNo << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    else
    {
        cout << "---------------------------------------------" << endl;
        cout << "No Record Found. " << endl;
        cout << "---------------------------------------------" << endl;
    }
}
