#include "../include/manager.h"


// Helper function to parse a CSV line into an Expense
Manager::Expense Manager::parseExpense(const std::string& line) {
    std::istringstream stream(line);
    Expense expense;
    std::string token;

    // Parse each field from the CSV line
    std::getline(stream, expense.description, ',');
    std::getline(stream, token, ',');
    expense.amount = std::stod(token);
    std::getline(stream, token, ',');
    expense.date = std::stol(token);
    std::getline(stream, expense.category, ',');
    std::getline(stream, token, ',');
    expense.isPaid = (token == "1");
    std::getline(stream, token, ',');
    expense.isProfit = (token == "1");
    std::getline(stream, token, ',');
    expense.isRecurring = (token == "1");

    return expense;
}

// Load expenses from a CSV file
void Manager::loadExpensesFromCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        expenses.push_back(parseExpense(line));
    }

    file.close();
}

// Save expenses to a CSV file
void Manager::saveExpensesToCSV(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    for (const auto& expense : expenses) {
        file << expense.description << ","
             << expense.amount << ","
             << expense.date << ","
             << expense.category << ","
             << (expense.isPaid ? "1" : "0") << ","
             << (expense.isProfit ? "1" : "0") << ","
             << (expense.isRecurring ? "1" : "0") << "\n";
    }

    file.close();
}

// Add a new expense
void Manager::addExpense(const Expense& expense) {
    expenses.push_back(expense);
}

// Sort expenses by category
void Manager::sortByCategory() {
    std::sort(expenses.begin(), expenses.end(), [](const Expense& a, const Expense& b) {
        return a.category < b.category;
    });
}

// Mark an expense as paid by index
void Manager::markExpenseAsPaid(size_t index) {
    if (index < expenses.size()) {
        expenses[index].isPaid = true;
    } else {
        std::cerr << "Error: Index out of range" << std::endl;
    }
}

// Mark an expense as paid by name
void Manager::markExpenseAsPaid(const std::string& description) {
    auto it = std::find_if(expenses.begin(), expenses.end(), [&description](const Expense& expense) {
        return expense.description == description;
    });

    if (it != expenses.end()) {
        it->isPaid = true;
    } else {
        std::cerr << "Error: Expense with description \"" << description << "\" not found" << std::endl;
    }
}

// Display all expenses
void Manager::showExpenses() const {
    for (const auto& expense : expenses) {
        std::cout << "Description: " << expense.description << "\n"
                  << "Amount: " << expense.amount << "\n"
                  << "Date: " << std::put_time(std::localtime(&expense.date), "%Y-%m-%d") << "\n"
                  << "Category: " << expense.category << "\n"
                  << "Paid: " << (expense.isPaid ? "Yes" : "No") << "\n"
                  << "Profit: " << (expense.isProfit ? "Yes" : "No") << "\n"
                  << "Recurring: " << (expense.isRecurring ? "Yes" : "No") << "\n"
                  << "--------------------------\n";
    }
}

// Estimate the total amount (profit and loss)
void Manager::estimateTotal() const {
    double totalProfit = 0.0;
    double totalLoss = 0.0;

    for (const auto& expense : expenses) {
        if (expense.isProfit) {
            totalProfit += expense.amount;
        } else {
            totalLoss += expense.amount;
        }
    }

    std::cout << "Total Profit: " << totalProfit << "\n";
    std::cout << "Total Loss: " << totalLoss << "\n";
    std::cout << "Net Total: " << (totalProfit - totalLoss) << "\n";
}