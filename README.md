# Bank ATM Management System

This project is a simple **Bank ATM Management System** written in C++. It simulates basic banking operations for both bank staff and ATM clients, including account management, authentication, and transactions.

## Features

- User and client management (add, update, delete, search)
- Secure login for bank users and ATM clients
- User permissions for different operations
- ATM operations: deposit, withdraw, check balance, quick withdrawal
- File-based data storage for persistence
- Modular code structure using namespaces and separate files

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++)
- Linux or any system with a compatible terminal

### Build Instructions

1. Clone or download this repository.
2. Open a terminal in the project directory.
3. Compile the project with:

   ```sh
   g++ ba.cpp bank_atm.cpp -o bankatm
   ```

4. Run the program:

   ```sh
   ./bankatm
   ```

## Usage

- Follow the on-screen menus to log in as a bank user or ATM client.
- Perform operations such as deposit, withdraw, check balance, and manage accounts.

## Project Structure

- `ba.cpp` — Main entry point of the program
- `bank_atm.h` — Header file with declarations and data structures
- `bank_atm.cpp` — Implementation of all banking and ATM functions

## License

This project is for educational purposes.

---

