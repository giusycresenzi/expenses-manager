#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), manager("data/expenses.csv") { // Initialize manager with a file path
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create table widget
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(7); // Match the number of fields in Expense
    tableWidget->setHorizontalHeaderLabels({"Description", "Amount", "Date", "Category", "Paid", "Profit", "Recurring"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(tableWidget);

    // Create buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    loadButton = new QPushButton("Load Expenses", this);
    saveButton = new QPushButton("Save Expenses", this);
    addButton = new QPushButton("Add Expense", this);

    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(addButton);
    mainLayout->addLayout(buttonLayout);

    // Set central widget
    setCentralWidget(centralWidget);

    // Connect signals to slots
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadExpenses);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveExpenses);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addExpense);
}

void MainWindow::loadExpenses() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        manager.loadExpensesFromCSV(filePath.toStdString());
        populateTable();
    }
}

void MainWindow::saveExpenses() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save CSV File", "", "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        manager.saveExpensesToCSV(filePath.toStdString());
        QMessageBox::information(this, "Save Expenses", "Expenses saved successfully!");
    }
}

void MainWindow::addExpense() {
    // For simplicity, add a dummy expense
    Manager::Expense expense = {"New Expense", 0.0, std::time(nullptr), "Category", false, false, false};
    manager.addExpense(expense);
    populateTable();
}

void MainWindow::populateTable() {
    tableWidget->setRowCount(0); // Clear the table

    const auto &expenses = manager.getExpenses(); // Add a getter for `expenses` in Manager
    for (const auto &expense : expenses) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(expense.description)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(expense.amount)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(expense.date))));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(expense.category)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(expense.isPaid ? "Yes" : "No"));
        tableWidget->setItem(row, 5, new QTableWidgetItem(expense.isProfit ? "Yes" : "No"));
        tableWidget->setItem(row, 6, new QTableWidgetItem(expense.isRecurring ? "Yes" : "No"));
    }
}