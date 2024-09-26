//design a c++ class that simulates an ATM , managing account details balance and transactions like mini statesment  withdrawals and transfers with a public function to retrieve the user's card PIN
#include <iostream>
#include <vector>
#include <string>
#include <ctime>  
using namespace std;
struct Transaction {
    string type;
    double amount;
    string date;
    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);
        date = ctime(&now);  
        date = date.substr(0, date.length() - 1);  
    }
};

// Class for an ATM system
class ATM {
private:
    string accountHolder;
    int accountNumber;
    double balance;
    int pin;  // PIN for accessing the account
    vector<Transaction> miniStatement;  // Store the last few transactions

public:
    // Constructor to initialize account details
    ATM(string holder, int number, double initialBalance, int pinCode)
        : accountHolder(holder), accountNumber(number), balance(initialBalance), pin(pinCode) {}

    // Public method to retrieve user's PIN
    int getPin() const {
        return pin;
    }

    // Function to display balance
    void displayBalance() const {
        cout << "Current balance: $" << balance << endl;
    }

    // Function to perform a withdrawal
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else if (amount <= 0) {
            cout << "Invalid withdrawal amount!" << endl;
        } else {
            balance -= amount;
            miniStatement.push_back(Transaction("Withdrawal", amount));
            cout << "$" << amount << " withdrawn successfully." << endl;
            displayBalance();
        }
    }

    // Function to perform a deposit (not mentioned, but useful for replenishing account)
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!" << endl;
        } else {
            balance += amount;
            miniStatement.push_back(Transaction("Deposit", amount));
            cout << "$" << amount << " deposited successfully." << endl;
            displayBalance();
        }
    }

    // Function to transfer money to another account
    void transfer(double amount, ATM &otherAccount) {
        if (amount > balance) {
            cout << "Insufficient funds for transfer!" << endl;
        } else if (amount <= 0) {
            cout << "Invalid transfer amount!" << endl;
        } else {
            balance -= amount;
            otherAccount.balance += amount;
            miniStatement.push_back(Transaction("Transfer", amount));
            cout << "$" << amount << " transferred successfully to Account #" << otherAccount.accountNumber << "." << endl;
            displayBalance();
        }
    }

    // Function to display the mini statement (last few transactions)
    void displayMiniStatement() const {
        if (miniStatement.empty()) {
            cout << "No transactions to display." << endl;
            return;
        }

        cout << "\n--- Mini Statement ---" << endl;
        for (const auto &transaction : miniStatement) {
            cout << transaction.type << ": $" << transaction.amount << " on " << transaction.date << endl;
        }
        cout << "----------------------" << endl;
    }
};

// Test the ATM class
int main() {
    // Create two accounts for demonstration
    ATM account1("John Doe", 123456, 500.0, 1234);
    ATM account2("Jane Smith", 654321, 1000.0, 4321);

    // Simulate a few ATM transactions
    account1.displayBalance();
    account1.withdraw(100.0);
    account1.deposit(50.0);
    account1.transfer(200.0, account2);

    account1.displayMiniStatement();

    cout << "\nRetrieving PIN for account1: " << account1.getPin() << endl;

    return 0;
}
