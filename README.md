# **Banking System**

**Overview**

This project is a simple implementation of a banking system in C++ that supports various features such as account management, transactions, loans, and VIP account handling. The system uses several data structures such as Binary Search Trees (BST), AVL Trees, Linked Lists, and Graphs for efficient data storage and management.

**Features**

- **Account Management**: Supports the creation of accounts and provides features to search, add, and remove accounts.
- **Transaction History**: Tracks all transactions made by users, allowing for deposit transactions and displaying transaction history.
- **VIP Account Handling**: Accounts with balance above a certain threshold are considered VIP accounts and are stored in an AVL Tree for efficient management.
- **Loan Management**: Allows users to apply for loans, view loan details, and approve/reject loans.
- **Sorting Transactions**: Supports sorting of transaction history by transaction amount using QuickSort.
- **Graph Representation**: Uses a graph to represent relationships between different accounts.

**Classes and Data Structures**

1. **Transaction**: A structure representing a transaction with details such as amount, date, and associated account number.
   
2. **Account**: A structure representing a bank account with account number, name, balance, and pointers for left and right children in the tree (used in BST and AVL).

3. **LinkedList**: A class to store and manage transaction history using a singly linked list.

4. **BST (Binary Search Tree)**: A class for managing and searching bank accounts using a binary search tree.

5. **AVL Tree**: An extension of BST for managing VIP accounts, providing efficient insertions and deletions with balanced trees.

6. **Graph**: A class for representing account relationships using an adjacency list.

7. **Loan**: A structure representing loan details with loan ID, account number, amount, interest rate, and tenure.

8. **LoanManagement**: A class to handle loan applications, approval, rejection, and EMI calculation.

9. **Bank**: The main class combining all the above features to provide a full banking system.

**Usage**

1. **Creating an Account**:  
   The system allows the creation of new accounts by entering the account number, name, and initial balance.

2. **Depositing Money**:  
   Users can deposit money into their accounts, and the transaction is recorded.

3. **Sorting Transactions**:  
   The system allows sorting transactions by amount using QuickSort.

4. **Viewing Transaction History**:  
   Users can view their transaction history.

5. **Managing Loans**:  
   Users can apply for loans, and loan applications can be approved or rejected by the system.

6. **Displaying VIP Accounts**:  
   The system can display accounts classified as VIP (with a balance greater than a threshold).

