#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include "../include/manager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void loadExpenses();
    void saveExpenses();
    void addExpense();

private:
    Manager manager; // Instance of your Manager class
    QTableWidget *tableWidget;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *addButton;

    void populateTable();
};

#endif // MAINWINDOW_H