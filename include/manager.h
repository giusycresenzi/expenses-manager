#ifndef MANAGER_H
#define MANAGER_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>

class Manager {

public:

    struct Expense {
        std::string description;
        double amount;
        std::time_t date;
        std::string category;
        bool isPaid;
        bool isProfit; // true for profit, false for loss
        bool isRecurring;
    };

    Manager() = default;
    explicit Manager(const std::string& filePath); // Constructor to load expenses directly from the main
    const std::vector<Expense>& getExpenses() const { return expenses; }
    void loadExpensesFromCSV(const std::string& filePath);
    void saveExpensesToCSV(const std::string& filePath) const;
    void addExpense(const Expense& expense);
    void sortByCategory();
    void markExpenseAsPaid(size_t index);
    void markExpenseAsPaid(const std::string& description); // overloaded
    void showExpenses() const;
    void estimateTotal() const;

private:
    
    std::vector<Expense> expenses;
    Expense parseExpense(const std::string& line);
    
};

#endif // MANAGER_H
