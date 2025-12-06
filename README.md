# 🏦 Bank Management System (C++)

This is a **training and educational project** for learning purposes.  
It demonstrates object-oriented programming concepts in C++ such as classes, inheritance, encapsulation, and file handling.  

> ⚠️ **Note:** This project is **not production-ready**. It is designed purely for educational purposes. Security and best practices may not be fully implemented.

---

## 🎯 Features

- **User Management**
  - Add, update, and delete users.
  - Assign permissions for various actions (transactions, client management, login/register).
  - View users list.

- **Client Management**
  - Add, update, and delete bank clients.
  - Store client information including full name, email, phone, account number, password, and balance.

- **Transactions**
  - Deposit and withdraw money.
  - Transfer between clients.
  - View total balances.
  - Maintain transfer logs.

- **Login & Access Control**
  - User login with username and password.
  - Role-based access control using permissions.
  - Track login history with timestamps.

- **Utilities**
  - Input validation and helper functions.
  - Text encryption/decryption for passwords.
  - String manipulation utilities (uppercase, lowercase, trimming, counting letters, etc.).

---

## 📂 Project Structure

Project/
│
├── Classes/ # All C++ class headers and screens
│ ├── clsUser.h
│ ├── clsPerson.h
│ ├── clsBankClient.h
│ ├── clsScreen.h
│ ├── clsLoginScreen.h
│ ├── clsTransactionsScreen.h
│ └── ...
│
├── Data/ # Text files storing users, clients, and logs
│ ├── Users.txt
│ ├── Clients.txt
│ ├── LoginRegister.txt
│ └── TransfersLog.txt
│
├── Main.cpp # Entry point of the application
├── Global.h # Global variables (e.g., CurrentUser)
└── Utils.h # Helper functions (ReadString, ReadDblNumber, EncryptText, etc.)


> Each folder/file serves a specific purpose:  
> - **Classes/** contains all class definitions and screens for the application.  
> - **Data/** contains persistent storage in text files.  
> - **Main.cpp** is the program entry point.  
> - **Global.h** stores global variables like the currently logged-in user.  
> - **Utils.h** contains utility functions for input handling and encryption.

---

## ⚙ How to Run

1. Clone or download the project.
2. Open in your preferred C++ IDE or compiler.
3. Compile and run `Main.cpp`.
4. Use the console-based menu to navigate through users, clients, and transactions.

---

## 🧑‍🏫 About

This project is intended as a **learning exercise** for practicing:

- Object-oriented programming (OOP) in C++
- File handling using text files
- Implementing role-based permissions
- Designing a console-based banking system interface

---

## 📌 Notes

- Passwords are encrypted in a simple way for demonstration purposes only.
- No advanced security or production-grade features are implemented.
- All operations are stored in text files; there is no database integration.
- This project is meant purely for educational and practice purposes.

## 💻 Author
**Mahmoud** – *Enthusiastic Developer*

