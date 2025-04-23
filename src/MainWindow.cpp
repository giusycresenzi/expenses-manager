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