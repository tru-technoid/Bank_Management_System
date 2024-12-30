# Banking Management System - TRU's

This project demonstrate a user-friendly banking application that allows users to create an account, log in, and perform various banking operations such as checking balances, depositing, withdrawing, and viewing recent transactions. The system uses a JSON file to store user account data and transaction records.

## Features

- **Account Registration** : Create a new account by providing personal information such as name, address, date of birth, phone number, and account type.
- **Login** : Log in using a registered phone number, date of birth, and password.
- **User Dashboard** : After logging in, users can :
  - View account details
  - Check account balance
  - Deposit funds
  - Withdraw funds
  - View recent transactions
- **Transaction Logging** : Every deposit and withdrawal is logged with transaction details such as date, type, amount, and updated balance.
- **Data Storage** : All user information and transactions are stored in a JSON file (`tru_bank_data.json`).

## Getting Started

To run the Banking Management System locally, follow the steps below :

### Prerequisites

- A C compiler (e.g., GCC)
- `cJSON` library for handling JSON data (included as a header file in the project)

### Installation

1. Clone the repository :
   ```bash
   https://github.com/tru-technoid/Bank_Management_System.git
   ```
2. Navigate into the project directory :
   ```bash
   cd Bank_Management_System
   ```
3. Make sure you have the `cJSON` library available. If not, you can download it from [cJSON GitHub Repository](https://github.com/DaveGamble/cJSON) and place the `cJSON.h` file in the project directory.

### Compiling the Code

To compile the code, run the following command :
```bash
gcc -o Management_System_TRU Management_System.c cJSON.c
```

### Running the Program

Once the code is compiled, run the program using :
```bash
./Management_System_TRU
```

## How To Use

1. **Create a New Account** : Select option `1` from the main menu to create a new account. You'll be prompted to enter personal details and an initial deposit.
2. **Log In** : Select option `2` to log into your account by providing your phone number, date of birth, and password given in registration.
3. **User Dashboard** : After logging in, you can choose from various options to manage your account, such as get account details, checking your balance, depositing or withdrawing funds, and viewing recent transactions and logout.
4. **Exit** : Choose option `3` to exit the system.

## System Work Flow 

- **Data Storage**: The user data and transactions are stored in a JSON file (`tru_bank_data.json`). Each user account is identified by a unique account number, and transactions are logged with a timestamp.
- **Transaction Types**: The system supports two types of transactions:
  - **Deposit**: Adding funds to the account.
  - **Withdrawal**: Removing funds from the account.

## Example

### Main Banking System Menu

```
Welcome to TRU Banking System
Please choose from the options below:
1. Create a New Account
2. Log In to an Existing Account
3. Exit
Enter your choice : 1
```

### Account Registration

```
!!___Register New Account___!!
Enter First Name : Trushar
Enter Last Name : Patel
Enter Address : 1234, Old Street, India
Enter Date of Birth (dd-mm-yyyy): 01-01-2003
Enter Nationality: Indian
Select Account Type As
(SA = Savings | CA = Current | FD = Fixed Deposit)
Your Acc Type: SA
Enter Mobile Number (10 digits): 1234567890
Enter Initial Deposit Amount: 5500.00
Set Your Password: password123
Confirm Your Password: password123

Account successfully created !!
Your Account Number is: 10234567
```

### Account Login

```
!!___Log In to Your Account___!!
Enter Mobile Number : 1234567890
Enter Date of Birth (dd-mm-yyyy) : 01-01-2003
Enter Password : password123

Login successful !!
Welcome back.
```

### User Dashboard After Login

```
!!__ User Dashboard __!!
1. View Account Details
2. Check Balance
3. Deposit Funds
4. Withdraw Funds
5. View Recent Transactions
6. Log Out
Enter your choice : 2

---- Balance Inquiry ----
Current Balance : 5500.00
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

## Contributing

We welcome contributions! To get started:
1. Fork the repository.
2. Create a new branch for your feature (`feature/YourFeature`).
3. Commit your changes.
4. Push to your branch.
5. Open a Pull Request for review.

---

### Contact

For any **questions** or support, reach out to [trushadowspecter261@gmail.com](mailto:trushadowspecter261@gmail.com).

---

### Acknowledgments

This project use cJSON.c and cJSON.h [Open Source Files](https://github.com/DaveGamble/cJSON) . Special thanks to the open-source community for it that made this project possible.
