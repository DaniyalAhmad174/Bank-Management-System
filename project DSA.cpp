#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm> 

using namespace std;

// Struct for Transactions
struct Transaction {
    int amount;
    string date;
    int accountNumber;
};

// Struct for Accounts in BST 


void quickSort(vector<Transaction>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high].amount;
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j].amount <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// Linked List for Transaction History
class LinkedList {
public:
    struct Node {
        Transaction transaction;
        Node* next;
    };

    Node* head;

    LinkedList() : head(nullptr) {}

    void addTransaction(Transaction transaction) {
        Node* newNode = new Node;
        newNode->transaction = transaction;
        newNode->next = head;
        head = newNode;
    }

    void removeLastTransaction() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void displayTransactions() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Account Number: " << temp->transaction.accountNumber
                 << ", Amount: " << temp->transaction.amount
                 << ", Date: " << temp->transaction.date << endl;
            temp = temp->next;
        }
    }
    
    vector<Transaction> toVector() {
    vector<Transaction> transactions;
    Node* temp = head;
    while (temp != nullptr) {
        transactions.push_back(temp->transaction);
        temp = temp->next;
    }
    return transactions;
}

void fromVector(const vector<Transaction>& transactions) {
    head = nullptr;
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it) {
        addTransaction(*it);
    }
}


    ~LinkedList() {
        while (head != nullptr) {
            removeLastTransaction();
        }
    }
};

// Binary Search Tree for Account Management
class BST {
    private:
    void destroyTree(Account* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
public:
    Account* root;

    BST() : root(nullptr) {}

    virtual Account* insert(Account* node, int accountNumber, string name, double balance) {
        if (node == nullptr) {
            node = new Account;
            node->accountNumber = accountNumber;
            node->name = name;
            node->balance = balance;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        if (accountNumber < node->accountNumber) {
            node->left = insert(node->left, accountNumber, name, balance);
        } else {
            node->right = insert(node->right, accountNumber, name, balance);
        }
        return node;
    }

    Account* search(Account* node, int accountNumber) {
        if (node == nullptr || node->accountNumber == accountNumber) {
            return node;
        }
        if (accountNumber < node->accountNumber) {
            return search(node->left, accountNumber);
        } else {
            return search(node->right, accountNumber);
        }
    }

    ~BST() {
        destroyTree(root);
    }


};

// AVL Tree for VIP Accounts
class AVL {
public:
    struct Account {
        int accountNumber;
        string name;
        double balance;
        int height;
        Account* left;
        Account* right;

        Account(int accNumber, string accName, double accBalance)
            : accountNumber(accNumber), name(accName), balance(accBalance),
              height(1), left(nullptr), right(nullptr) {}
    };

    Account* root;

    AVL() : root(nullptr) {}

    int height(Account* node) {
        return node == nullptr ? 0 : node->height;
    }

    int getBalanceFactor(Account* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    Account* rotateRight(Account* y) {
        Account* x = y->left;
        Account* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Account* rotateLeft(Account* x) {
        Account* y = x->right;
        Account* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Account* insert(Account* node, int accountNumber, string name, double balance) {
        if (node == nullptr) {
            return new Account(accountNumber, name, balance);
        }

        if (accountNumber < node->accountNumber) {
            node->left = insert(node->left, accountNumber, name, balance);
        } else if (accountNumber > node->accountNumber) {
            node->right = insert(node->right, accountNumber, name, balance);
        } else {
            return node; // Duplicate account numbers are not allowed
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balanceFactor = getBalanceFactor(node);

        // Left Left Case
        if (balanceFactor > 1 && accountNumber < node->left->accountNumber) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balanceFactor < -1 && accountNumber > node->right->accountNumber) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balanceFactor > 1 && accountNumber > node->left->accountNumber) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balanceFactor < -1 && accountNumber < node->right->accountNumber) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Account* minValueNode(Account* node) {
        Account* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Account* deleteNode(Account* root, int accountNumber) {
        if (root == nullptr) {
            return root;
        }

        if (accountNumber < root->accountNumber) {
            root->left = deleteNode(root->left, accountNumber);
        } else if (accountNumber > root->accountNumber) {
            root->right = deleteNode(root->right, accountNumber);
        } else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Account* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Account* temp = minValueNode(root->right);
                root->accountNumber = temp->accountNumber;
                root->name = temp->name;
                root->balance = temp->balance;
                root->right = deleteNode(root->right, temp->accountNumber);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalanceFactor(root);

        // Left Left Case
        if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0) {
            return rotateRight(root);
        }

        // Left Right Case
        if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0) {
            return rotateLeft(root);
        }

        // Right Left Case
        if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inOrder(Account* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << "Account Number: " << node->accountNumber
                 << ", Name: " << node->name
                 << ", Balance: " << node->balance << endl;
            inOrder(node->right);
        }
    }

    ~AVL() {
        destroyTree(root);
    }

private:
    void destroyTree(Account* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};


// Graph for Account Relationships
class Graph {
private:
    map<int, vector<int> > adjList;

public:
    void addEdge(int account1, int account2) {
        adjList[account1].push_back(account2);
    }

    void displayGraph() {
        for (map<int, vector<int> >::const_iterator it = adjList.begin(); it != adjList.end(); ++it) {
            cout << "Account " << it->first << ": ";
            for (size_t i = 0; i < it->second.size(); ++i) {
                cout << it->second[i] << " ";
            }
            cout << endl;
        }
    }
};
//

// Struct for Loan Details
struct Loan {
    int loanID;
    int accountNumber;
    double amount;
    double interestRate; // Annual Interest Rate in percentage
    int tenureMonths;    // Loan Tenure in months
};

// Loan Management Class
class LoanManagement {
private:
    vector<Loan> loanRecords;

    double calculateEMI(double principal, double rate, int tenure) {
        double monthlyRate = rate / (12 * 100); // Monthly Interest Rate
        return (principal * monthlyRate * pow(1 + monthlyRate, tenure)) /
               (pow(1 + monthlyRate, tenure) - 1);
    }

public:
    void applyForLoan(int accountNumber) {
        Loan loan;
        loan.loanID = loanRecords.size() + 1; // Generate Loan ID
        loan.accountNumber = accountNumber;

        cout << "Enter loan amount: ";
        cin >> loan.amount;

        cout << "Enter annual interest rate (in %): ";
        cin >> loan.interestRate;

        cout << "Enter tenure (in months): ";
        cin >> loan.tenureMonths;

        loanRecords.push_back(loan);

        cout << "Loan application submitted successfully!\n";
    }

    void displayLoanDetails(int accountNumber) {
        bool found = false;
        for (const auto& loan : loanRecords) {
            if (loan.accountNumber == accountNumber) {
                double emi = calculateEMI(loan.amount, loan.interestRate, loan.tenureMonths);
                cout << "\nLoan ID: " << loan.loanID
                     << "\nLoan Amount: " << loan.amount
                     << "\nInterest Rate: " << loan.interestRate << "%"
                     << "\nTenure: " << loan.tenureMonths << " months"
                     << "\nMonthly EMI: " << emi << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No loan found for the given account number.\n";
        }
    }

    void approveLoan(int loanID) {
        for (auto& loan : loanRecords) {
            if (loan.loanID == loanID) {
                cout << "Loan with ID " << loanID << " has been approved.\n";
                return;
            }
        }
        cout << "Loan ID not found!\n";
    }

    void rejectLoan(int loanID) {
        for (size_t i = 0; i < loanRecords.size(); ++i) {
            if (loanRecords[i].loanID == loanID) {
                loanRecords.erase(loanRecords.begin() + i);
                cout << "Loan with ID " << loanID << " has been rejected and removed from the records.\n";
                return;
            }
        }
        cout << "Loan ID not found!\n";
    }
};

// Bank Class
class Bank {
private:
    LinkedList transactionHistory;
    queue<string> customerServiceQueue;
    stack<Transaction> undoStack;
    BST accountBST;
    AVL vipAccountAVL;      // For managing high-value accounts

    LoanManagement loanManager;


public:
    void createAccount() {
    int accountNumber;
    string name;
    double balance;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter account holder's name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter initial balance: ";
    cin >> balance;

    // Insert into BST
    accountBST.root = accountBST.insert(accountBST.root, accountNumber, name, balance);

    // Insert into AVL if it qualifies as a VIP account
    if (balance > 100000) { // Threshold for VIP accounts
        vipAccountAVL.root = vipAccountAVL.insert(vipAccountAVL.root, accountNumber, name, balance);
        cout << "Account added as a VIP account.\n";
    } else {
        cout << "Account created successfully.\n";
    }
}

    void deposit() {
        int accountNumber, amount;
        string date;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter deposit amount: ";
        cin >> amount;
        cout << "Enter transaction date: ";
        cin >> date;

        Account* account = accountBST.search(accountBST.root, accountNumber);
        if (account) {
            account->balance += amount;
            Transaction transaction = {amount, date, accountNumber};
            transactionHistory.addTransaction(transaction);
            undoStack.push(transaction);
        } else {
            cout << "Account not found!" << endl;
        }
    }
    void sortTransactionsByAmount() {
    // Convert the linked list to a vector
    vector<Transaction> transactions = transactionHistory.toVector();
    
    // Sort the vector using the quickSort function
    quickSort(transactions, 0, transactions.size() - 1);
    
    // Rebuild the linked list from the sorted vector
    transactionHistory.fromVector(transactions);

    // Confirm to the user that sorting is complete
    cout << "Transactions sorted by amount successfully.\n";
}
void displaySortedTransactionAmounts() {
    vector<Transaction> transactions = transactionHistory.toVector();

    // Sort transactions by amount
    quickSort(transactions, 0, transactions.size() - 1);

    // Display sorted transaction amounts
    cout << "\n>>> Sorted Transaction Amounts <<<\n";
    for (const auto& transaction : transactions) {
        cout << "Amount: " << transaction.amount << endl;
    }
}



    void displayVIPAccounts() {
    cout << "\n>>> VIP Accounts <<<\n";
    displayAVL(vipAccountAVL.root);
}

void displayAVL(AVL::Account* node) {
    if (node == nullptr) return;

    displayAVL(node->left);
    cout << "Account Number: " << node->accountNumber
         << ", Name: " << node->name
         << ", Balance: " << node->balance << endl;
    displayAVL(node->right);
}

void applyForLoan() {
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    Account* account = accountBST.search(accountBST.root, accountNumber);
    if (account) {
        loanManager.applyForLoan(accountNumber);
    } else {
        cout << "Account not found!" << endl;
    }
}

void displayLoanDetails() {
    int accountNumber;
    cout << "Enter account number to view loan details: ";
    cin >> accountNumber;

    loanManager.displayLoanDetails(accountNumber);
}

void approveLoan() {
    int loanID;
    cout << "Enter Loan ID to approve: ";
    cin >> loanID;

    loanManager.approveLoan(loanID);
}

void rejectLoan() {
    int loanID;
    cout << "Enter Loan ID to reject: ";
    cin >> loanID;

    loanManager.rejectLoan(loanID);
}

    void withdraw() {
        int accountNumber, amount;
        string date;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        cout << "Enter transaction date: ";
        cin >> date;

        Account* account = accountBST.search(accountBST.root, accountNumber);
        if (account) {
            if (account->balance >= amount) {
                account->balance -= amount;
                Transaction transaction = {-amount, date, accountNumber};
                transactionHistory.addTransaction(transaction);
                undoStack.push(transaction);
            } else {
                cout << "Insufficient balance!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void balanceInquiry() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* account = accountBST.search(accountBST.root, accountNumber);
        if (account) {
            cout << "Balance: " << account->balance << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void processCustomerRequest() {
        if (!customerServiceQueue.empty()) {
            cout << "Processing request: " << customerServiceQueue.front() << endl;
            customerServiceQueue.pop();
        } else {
            cout << "No requests to process." << endl;
        }
    }

    void addCustomerRequest(const string& request) {
        customerServiceQueue.push(request);
        cout << "Request added: " << request << endl;
    }

    void undoTransaction() {
        if (!undoStack.empty()) {
            Transaction lastTransaction = undoStack.top();
            undoStack.pop();

            Account* account = accountBST.search(accountBST.root, lastTransaction.accountNumber);
            if (account) {
                account->balance -= lastTransaction.amount;
                transactionHistory.removeLastTransaction();
                cout << "Transaction undone. Amount: " << lastTransaction.amount
                     << ", Date: " << lastTransaction.date
                     << ", Account Number: " << lastTransaction.accountNumber << endl;
            } else {
                cout << "Account not found! Unable to undo transaction." << endl;
            }
        } else {
            cout << "No transactions to undo." << endl;
        }

   

    }
};

int main() 
{
    Bank bank;
    int choice;

    while (true) {
        cout << "\n=========================================\n";
        cout << "          Welcome to the Bank\n";
        cout << "=========================================\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Sort Transaction By Amount\n";
        cout << "4. Withdraw\n";
        cout << "5. Balance Inquiry\n";
        cout << "6. Process Customer Request\n";
        cout << "7. Add Customer Request\n";
        cout << "8. Undo Last Transaction\n";
        cout << "9. Apply for Loan\n";
        cout << "10. Display Loan Details\n";
        cout << "11. Approve Loan\n";
        cout << "12. Reject Loan\n";
        cout << "13. Display VIP Accounts\n";
        cout << "14. Display Sorted list of  Transaction Amount\n ";
        cout << "15. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice (1-15): ";
        cin  >> choice;

        switch (choice) {
            case 1:
                cout << "\n>>> Create a New Account <<<\n";
                bank.createAccount();
                cout << "Account successfully created.\n";
                break;
            case 2:
                cout << "\n>>> Deposit Money <<<\n";
                bank.deposit();
                cout << "Deposit successful.\n";
                break;

            case 3:
                bank.sortTransactionsByAmount();
                break;
    
            case 4:
                cout << "\n>>> Withdraw Money <<<\n";
                bank.withdraw();
                cout << "Withdrawal processed.\n";
                break;
            case 5:
                cout << "\n>>> Balance Inquiry <<<\n";
                bank.balanceInquiry();
                break;
            case 6:
                cout << "\n>>> Process Customer Request <<<\n";
                bank.processCustomerRequest();
                break;
            case 7: {
                cout << "\n>>> Add Customer Request <<<\n";
                string request;
                cout << "Enter the customer request: ";
                cin.ignore(); // To clear the input buffer
                getline(cin, request);
                bank.addCustomerRequest(request);
                break;
            }
            case 8:
                cout << "\n>>> Undo Last Transaction <<<\n";
                bank.undoTransaction();
                break;
            
            case 9:
                 cout << "\n>>> Apply for Loan <<<\n";
                 bank.applyForLoan();
                 break;
            case 10:
                cout << "\n>>> Display Loan Details <<<\n";
                bank.displayLoanDetails();
                break;
            case 11:
                cout << "\n>>> Approve Loan <<<\n";
                bank.approveLoan();
                break;
            case 12:
                cout << "\n>>> Reject Loan <<<\n";
                bank.rejectLoan();
                break;
            case 13:
                cout << "\n>>> Display VIP Accounts <<<\n";
                bank.displayVIPAccounts();
                break;
            case 14:
                bank.displaySortedTransactionAmounts();
                break;

            case 15:
                cout << "\nThank you for using our banking system. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 8.\n";
                break;
        }

        cout << "-----------------------------------------\n";
}
}
