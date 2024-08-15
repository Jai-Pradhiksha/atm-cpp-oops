#include <iostream>
#include <limits> // For numeric_limits
#include <string>

// Exception classes
class InvalidAmountException : public std::exception {
public:
    explicit InvalidAmountException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

class InsufficientBalanceException : public std::exception {
public:
    explicit InsufficientBalanceException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

// Abstract ATM class
class ATM {
protected:
    int accountBalance;

    // Protected method to update balance
    void updateBalance(int amount) {
        accountBalance += amount;
    }

public:
    ATM() : accountBalance(0) {}

    int getAccountBalance() const {
        return accountBalance;
    }

    // Abstract methods
    virtual void depositAmount(int amountToBeDeposited) = 0;
    virtual void withdrawAmount(int amountToBeWithdrawn) = 0;
    virtual void checkBalance() const = 0;
    virtual void addMoney(int amountToBeDeposited) = 0;
    virtual void takeMoney(int amountToBeWithdrawn) = 0;
};

// Concrete IndianBankATM class
class IndianBankATM : public ATM {
public:
    void initialize() {
        int userChoice;
        int inputAmount;

        do {
            printLine();
            std::cout << "1 - Deposit Amount\n";
            std::cout << "2 - Withdraw Amount\n";
            std::cout << "3 - Check Balance\n";
            std::cout << "4 - Exit\n";
            printLine();
            std::cout << "Enter your preferred option ... ";

            std::cin >> userChoice;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input, please enter a valid number.\n";
                continue;
            }

            switch (userChoice) {
                case 1:
                    std::cout << "Enter the amount to be deposited ... Rs.";
                    std::cin >> inputAmount;
                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                        std::cout << "Invalid amount, please enter a valid number.\n";
                        continue;
                    }
                    try {
                        if (isValidAmount(inputAmount)) {
                            depositAmount(inputAmount);
                        }
                    } catch (const InvalidAmountException& e) {
                        std::cout << e.what() << '\n';
                    }
                    break;

                case 2:
                    std::cout << "Enter the amount to be withdrawn ... Rs.";
                    std::cin >> inputAmount;
                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                        std::cout << "Invalid amount, please enter a valid number.\n";
                        continue;
                    }
                    try {
                        if (getAccountBalance() < inputAmount) {
                            throw InsufficientBalanceException("Insufficient account balance in your account.");
                        }
                        withdrawAmount(inputAmount);
                    } catch (const InsufficientBalanceException& e) {
                        std::cout << e.what() << '\n';
                    }
                    break;

                case 3:
                    checkBalance();
                    break;

                case 4:
                    std::cout << "Thank you, Have a nice day :)\n";
                    return;

                default:
                    std::cout << "Invalid option, please retry with a valid option\n";
            }
        } while (true);
    }

    // Implementations of abstract methods
    void addMoney(int amountToBeDeposited) override {
        updateBalance(amountToBeDeposited);
        std::cout << "Deposited Rs. " << amountToBeDeposited << '\n';
        checkBalance();
    }

    void takeMoney(int amountToBeWithdrawn) override {
        updateBalance(-amountToBeWithdrawn);
        std::cout << "Withdrew Rs. " << amountToBeWithdrawn << '\n';
        checkBalance();
    }

    void depositAmount(int amountToBeDeposited) override {
        addMoney(amountToBeDeposited);
    }

    void withdrawAmount(int amountToBeWithdrawn) override {
        takeMoney(amountToBeWithdrawn);
    }

    void checkBalance() const override {
        printLine();
        std::cout << "Your balance is Rs. " << getAccountBalance() << '\n';
    }

private:
    void printLine() const {
        std::cout << "________________________________\n";
    }

    bool isValidAmount(int amount) const {
        if (amount > 0) {
            return true;
        }
        throw InvalidAmountException("Amount must be greater than 0.");
    }
};

int main() {
    IndianBankATM guindyATM;
    guindyATM.initialize();
    return 0;
}
