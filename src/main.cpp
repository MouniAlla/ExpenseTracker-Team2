// cpp/src/main.cpp
#include "../include/expense.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "expense_store.cpp" // for simplicity in single build

// Generate a pseudo-random ID
std::string generateID() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return "E" + std::to_string(std::rand() % 1000000);
}

int main() {
    ExpenseStore store("../data/sample_expenses.csv");

    int choice;
    do {
        std::cout << "\n===== Expense Tracker Menu =====\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. List All Expenses\n";
        std::cout << "3. Filter by Date Range\n";
        std::cout << "4. Filter by Category\n";
        std::cout << "5. Summary by Category\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        
        // Input validation
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            Expense e;
            e.id = generateID();
            std::cout << "Enter date (YYYY-MM-DD): ";
            std::cin >> e.date;
            std::cout << "Enter amount: ";
            
            // Validate amount input
            while (!(std::cin >> e.amount) || e.amount < 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid amount! Please enter a positive number: ";
            }
            
            std::cin.ignore();
            std::cout << "Enter category: ";
            std::getline(std::cin, e.category);
            std::cout << "Enter description: ";
            std::getline(std::cin, e.description);
            store.addExpense(e);
            std::cout << "✅ Expense added successfully!\n";
        }
        else if (choice == 2) {
            store.listExpenses();
        }
        else if (choice == 3) {
            std::string start, end;
            std::cout << "Enter start date (YYYY-MM-DD): ";
            std::cin >> start;
            std::cout << "Enter end date (YYYY-MM-DD): ";
            std::cin >> end;
            store.filterByDate(start, end);
        }
        else if (choice == 4) {
            std::string cat;
            std::cout << "Enter category: ";
            std::cin >> cat;
            store.filterByCategory(cat);
        }
        else if (choice == 5) {
            store.summarizeByCategory();
        }
    } while (choice != 0);

    std::cout << "\nGoodbye!\n";
    return 0;
}
