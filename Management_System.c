#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "cJSON.h" //JSON helper

#define DATA_FILE "tru_bank_data.json"
#define MAX_LENGTH 256

// Main Functionality
void displayMainMenu();
void registerAccount();
void loginToAccount();
void userDashboard(cJSON *userNode);
void viewBalance(cJSON *userNode);
void depositFunds(cJSON *userNode);
void withdrawFunds(cJSON *userNode);
void displayRecentTransactions(cJSON *userNode);
void viewAccountDetails(cJSON *userNode);

void saveToDatabase(cJSON *database);
cJSON *loadFromDatabase();
int createUniqueAccountNumber(cJSON *database);
void logTransaction(cJSON *transactionList, const char *transactionType, double amount, double updatedBalance);

// Helper functions for main functions
int validatePhoneNumber(const char *phone);
int validatePassword(const char *password, const char *confirmation);

int main()
{
    displayMainMenu();
    return 0;
}

void displayMainMenu()
{
    int option;
    
    do
    {
        printf("\nWelcome to TRU Banking System\n");
        printf("Please choose from the options below:\n");
        printf("1. Create a New Account\n");
        printf("2. Log In to an Existing Account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
            registerAccount();
            break;
        case 2:
            loginToAccount();
            break;
        case 3:
            printf("Thank you for using TRU Banking. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);
}

void registerAccount()
{
    char firstName[MAX_LENGTH], lastName[MAX_LENGTH], address[MAX_LENGTH], dateOfBirth[MAX_LENGTH];
    char nationality[MAX_LENGTH], accountType[MAX_LENGTH], phoneNumber[MAX_LENGTH];
    char password[MAX_LENGTH], confirmPassword[MAX_LENGTH];
    double initialDeposit;

    printf("\n!!___Register New Account___!!\n");
    printf("Enter First Name : ");
    fgets(firstName, MAX_LENGTH, stdin);
    strtok(firstName, "\n"); // For Remove newline char

    printf("Enter Last Name : ");
    fgets(lastName, MAX_LENGTH, stdin);
    strtok(lastName, "\n");

    printf("Enter Address : ");
    fgets(address, MAX_LENGTH, stdin);
    strtok(address, "\n");

    printf("Enter Date of Birth (dd-mm-yyyy) : ");
    fgets(dateOfBirth, MAX_LENGTH, stdin);
    strtok(dateOfBirth, "\n");

    printf("Enter Nationality : ");
    fgets(nationality, MAX_LENGTH, stdin);
    strtok(nationality, "\n");

    printf("Select Account Type As\n(SA = Savings | CA = Current | FD = Fixed Deposit )\n Your Acc Type : ");
    fgets(accountType, MAX_LENGTH, stdin);
    strtok(accountType, "\n");

    do
    {
        printf("Enter Mobile Number (10 digits) : ");
        fgets(phoneNumber, MAX_LENGTH, stdin);
        strtok(phoneNumber, "\n");
    } while (!validatePhoneNumber(phoneNumber));

    printf("Enter Initial Deposit Amount : ");
    scanf("%lf", &initialDeposit);
    getchar();

    do
    {
        printf("Set Your Password : ");
        fgets(password, MAX_LENGTH, stdin);
        strtok(password, "\n");

        printf("Confirm Your Password : ");
        fgets(confirmPassword, MAX_LENGTH, stdin);
        strtok(confirmPassword, "\n");
    } while (!validatePassword(password, confirmPassword));

    cJSON *database = loadFromDatabase();
    int accountNumber = createUniqueAccountNumber(database);

    // Create new user object for json
    cJSON *newUser = cJSON_CreateObject();
    cJSON_AddNumberToObject(newUser, "account_number", accountNumber);
    cJSON_AddStringToObject(newUser, "first_name", firstName);
    cJSON_AddStringToObject(newUser, "last_name", lastName);
    cJSON_AddStringToObject(newUser, "address", address);
    cJSON_AddStringToObject(newUser, "dob", dateOfBirth);
    cJSON_AddStringToObject(newUser, "nationality", nationality);
    cJSON_AddStringToObject(newUser, "account_type", accountType);
    cJSON_AddStringToObject(newUser, "phone", phoneNumber);
    cJSON_AddNumberToObject(newUser, "balance", initialDeposit);
    cJSON_AddStringToObject(newUser, "password", password);

    // Add initial balance to account
    cJSON *transactions = cJSON_CreateArray();
    logTransaction(transactions, "Deposit", initialDeposit, initialDeposit);
    cJSON_AddItemToObject(newUser, "transactions", transactions);

    // Add user into json file
    cJSON_AddItemToArray(cJSON_GetObjectItem(database, "users"), newUser);
    saveToDatabase(database);
    cJSON_Delete(database);

    printf("\nAccount successfully created !! \nYour Account Number is: %08d\n", accountNumber);
}

void loginToAccount()
{
    char phoneNumber[MAX_LENGTH], dateOfBirth[MAX_LENGTH], password[MAX_LENGTH];

    printf("\n!!___Log In to Your Account___!!\n");
    printf("Enter Mobile Number : ");
    fgets(phoneNumber, MAX_LENGTH, stdin);
    strtok(phoneNumber, "\n");

    printf("Enter Date of Birth (dd-mm-yyyy) : ");
    fgets(dateOfBirth, MAX_LENGTH, stdin);
    strtok(dateOfBirth, "\n");

    printf("Enter Password : ");
    fgets(password, MAX_LENGTH, stdin);
    strtok(password, "\n");

    cJSON *database = loadFromDatabase();
    cJSON *users = cJSON_GetObjectItem(database, "users");

    cJSON *currentUser = NULL;
    cJSON_ArrayForEach(currentUser, users)
    {
        if (strcmp(cJSON_GetObjectItem(currentUser, "phone")->valuestring, phoneNumber) == 0 &&
            strcmp(cJSON_GetObjectItem(currentUser, "dob")->valuestring, dateOfBirth) == 0 &&
            strcmp(cJSON_GetObjectItem(currentUser, "password")->valuestring, password) == 0)
        {
            printf("Login successful !!\n Welcome back.\n");
            userDashboard(currentUser);
            cJSON_Delete(database);
            return;
        }
    }

    printf("Invalid Credentials. Please try again.\n");
    cJSON_Delete(database);
}

void userDashboard(cJSON *userNode)
{
    int choice;
    do
    {
        printf("\n!!__ User Dashboard __!!\n");
        printf("1. View Account Details\n");
        printf("2. Check Balance\n");
        printf("3. Deposit Funds\n");
        printf("4. Withdraw Funds\n");
        printf("5. View Recent Transactions\n");
        printf("6. Log Out\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            viewAccountDetails(userNode);
            break;
        case 2:
            viewBalance(userNode);
            break;
        case 3:
            depositFunds(userNode);
            break;
        case 4:
            withdrawFunds(userNode);
            break;
        case 5:
            displayRecentTransactions(userNode);
            break;
        case 6:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid Choice. Please try again.\n");
        }
    } while (choice != 6);
}

void viewAccountDetails(cJSON *userNode)
{
    printf("\n---- Account Details ----\n");
    printf("Account Number : %08d\n", cJSON_GetObjectItem(userNode, "account_number")->valueint);
    printf("Name : %s %s\n",
           cJSON_GetObjectItem(userNode, "first_name")->valuestring,
           cJSON_GetObjectItem(userNode, "last_name")->valuestring);
    printf("Address : %s\n", cJSON_GetObjectItem(userNode, "address")->valuestring);
    printf("Date of Birth : %s\n", cJSON_GetObjectItem(userNode, "dob")->valuestring);
    printf("Nationality : %s\n", cJSON_GetObjectItem(userNode, "nationality")->valuestring);
    printf("Account Type : %s\n", cJSON_GetObjectItem(userNode, "account_type")->valuestring);
    printf("Mobile : %s\n", cJSON_GetObjectItem(userNode, "phone")->valuestring);
    printf("Balance : %.2f\n", cJSON_GetObjectItem(userNode, "balance")->valuedouble);
}

void viewBalance(cJSON *userNode)
{
    printf("\n---- Balance Inquiry ----\n");
    printf("Current Balance : %.2f\n", cJSON_GetObjectItem(userNode, "balance")->valuedouble);
}

void depositFunds(cJSON *userNode)
{
    double depositAmount;
    printf("\n---- Deposit Funds ----\n");
    printf("Enter the amount to deposit : ");
    scanf("%lf", &depositAmount);
    getchar();

    if (depositAmount <= 0)
    {
        printf("Invalid Amount. Please try again.\n");
        return;
    }

    double currentBalance = cJSON_GetObjectItem(userNode, "balance")->valuedouble;
    double updatedBalance = currentBalance + depositAmount;
    cJSON_ReplaceItemInObject(userNode, "balance", cJSON_CreateNumber(updatedBalance));

    cJSON *transactions = cJSON_GetObjectItem(userNode, "transactions");
    logTransaction(transactions, "Credit", depositAmount, updatedBalance);

    // Update database with modified user data
    cJSON *database = loadFromDatabase();
    cJSON *users = cJSON_GetObjectItem(database, "users");
    cJSON *currentUser;

    cJSON_ArrayForEach(currentUser, users)
    {
        if (cJSON_GetObjectItem(currentUser, "account_number")->valueint ==
            cJSON_GetObjectItem(userNode, "account_number")->valueint)
        {
            cJSON_ReplaceItemInObject(currentUser, "transactions", cJSON_Duplicate(transactions, 1));
            cJSON_ReplaceItemInObject(currentUser, "balance", cJSON_CreateNumber(updatedBalance));
            break;
        }
    }

    saveToDatabase(database);
    cJSON_Delete(database);

    printf("Deposit successful !! \nUpdated Balance : %.2f\n", updatedBalance);
}

void withdrawFunds(cJSON *userNode)
{
    double withdrawalAmount;
    printf("\n---- Withdraw Funds ----\n");
    printf("Enter the amount to withdraw : ");
    scanf("%lf", &withdrawalAmount);
    getchar();

    double currentBalance = cJSON_GetObjectItem(userNode, "balance")->valuedouble;
    if (withdrawalAmount <= 0 || withdrawalAmount > currentBalance)
    {
        printf("Insufficient Amount. Please check your balance and try again.\n");
        return;
    }

    double updatedBalance = currentBalance - withdrawalAmount;
    cJSON_ReplaceItemInObject(userNode, "balance", cJSON_CreateNumber(updatedBalance));

    cJSON *transactions = cJSON_GetObjectItem(userNode, "transactions");
    logTransaction(transactions, "Debit", withdrawalAmount, updatedBalance);

    // Update database with modified user data
    cJSON *database = loadFromDatabase();
    cJSON *users = cJSON_GetObjectItem(database, "users");
    cJSON *currentUser;

    cJSON_ArrayForEach(currentUser, users)
    {
        if (cJSON_GetObjectItem(currentUser, "account_number")->valueint ==
            cJSON_GetObjectItem(userNode, "account_number")->valueint)
        {
            cJSON_ReplaceItemInObject(currentUser, "transactions", cJSON_Duplicate(transactions, 1));
            cJSON_ReplaceItemInObject(currentUser, "balance", cJSON_CreateNumber(updatedBalance));
            break;
        }
    }

    saveToDatabase(database);
    cJSON_Delete(database);

    printf("Withdrawal successful !! \nUpdated Balance : %.2f\n", updatedBalance);
}

void displayRecentTransactions(cJSON *userNode)
{
    printf("\n---- Recent Transactions ----\n");
    cJSON *transactions = cJSON_GetObjectItem(userNode, "transactions");
    int transactionCount = cJSON_GetArraySize(transactions);

    if (transactionCount == 0)
    {
        printf("No transactions available.\n");
        return;
    }

    int start = transactionCount > 5 ? transactionCount - 5 : 0;
    for (int i = start; i < transactionCount; i++)
    {
        cJSON *transaction = cJSON_GetArrayItem(transactions, i);
        printf("Transaction #%d on %s:\n",
               cJSON_GetObjectItem(transaction, "sr_no")->valueint,
               cJSON_GetObjectItem(transaction, "date")->valuestring);
        printf("  Type: %s\n", cJSON_GetObjectItem(transaction, "type")->valuestring);
        printf("  Amount: %.2f\n", cJSON_GetObjectItem(transaction, "amount")->valuedouble);
        printf("  Balance After: %.2f\n", cJSON_GetObjectItem(transaction, "balance")->valuedouble);
    }
}

cJSON *loadFromDatabase()
{
    FILE *file = fopen(DATA_FILE, "r");
    if (!file)
    {
        cJSON *newDatabase = cJSON_CreateObject();
        cJSON_AddItemToObject(newDatabase, "users", cJSON_CreateArray());
        return newDatabase;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(fileSize + 1);
    fread(content, 1, fileSize, file);
    fclose(file);

    cJSON *database = cJSON_Parse(content);
    free(content);

    if (!database)
    {
        printf("Error While Loading Database File.\n");
        exit(EXIT_FAILURE);
    }
    return database;
}

void saveToDatabase(cJSON *database)
{
    FILE *file = fopen(DATA_FILE, "w");
    if (!file)
    {
        printf("Error To Saving Data.\n");
        return;
    }

    char *data = cJSON_Print(database);
    fprintf(file, "%s", data);
    free(data);
    fclose(file);
}

int createUniqueAccountNumber(cJSON *database)
{
    srand(time(NULL));
    int accountNumber;
    cJSON *users = cJSON_GetObjectItem(database, "users");

    do
    {
        int firstDigit = rand() % 9 + 1;
        int remainingDigits = rand() % 10000000; // 0 to 9999999
        accountNumber = firstDigit * 10000000 + remainingDigits;

        int isUnique = 1;

        cJSON *user;
        cJSON_ArrayForEach(user, users)
        {
            if (cJSON_GetObjectItem(user, "account_no")->valueint == accountNumber)
            {
                isUnique = 0;
                break;
            }
        }

        if (isUnique)
            break;
    } while (1);

    return accountNumber;
}

void logTransaction(cJSON *transactionList, const char *transactionType, double amount, double updatedBalance)
{
    time_t now = time(NULL);
    struct tm *timeInfo = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%d-%m-%Y", timeInfo);

    cJSON *newTransaction = cJSON_CreateObject();
    cJSON_AddNumberToObject(newTransaction, "sr_no", cJSON_GetArraySize(transactionList) + 1);
    cJSON_AddStringToObject(newTransaction, "date", date);
    cJSON_AddStringToObject(newTransaction, "type", transactionType);
    cJSON_AddNumberToObject(newTransaction, "amount", amount);
    cJSON_AddNumberToObject(newTransaction, "balance", updatedBalance);

    cJSON_AddItemToArray(transactionList, newTransaction);
}

int validatePhoneNumber(const char *phone)
{
    if (strlen(phone) != 10)
    {
        printf("Invalid phone number. Must be 10 digits.\n");
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf("Invalid phone number. Only digits are allowed.\n");
            return 0;
        }
    }
    return 1;
}

int validatePassword(const char *password, const char *confirmation)
{
    if (strcmp(password, confirmation) != 0)
    {
        printf("Passwords do not match. Please try again.\n");
        return 0;
    }
    return 1;
}