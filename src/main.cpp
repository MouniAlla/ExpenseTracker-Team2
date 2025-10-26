// cpp/src/main.cpp
#include "../include/expense.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <regex>
#include <chrono>
#include <fstream>
#include "expense_store.cpp" // for simplicity in single build

// Generate a pseudo-random ID
std::string generateID() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return "E" + std::to_string(std::rand() % 1000000);
}

// Date validation function
bool isValidDate(const std::string& dateStr) {
    // Check format: YYYY-MM-DD
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(dateStr, dateRegex)) {
        return false;
    }
    
    // Parse the date components
    int year, month, day;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        return false;
    }
    
    // Basic range checks
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Check for valid days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Handle leap year for February
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear) {
            daysInMonth[1] = 29;
        }
    }
    
    if (day > daysInMonth[month - 1]) {
        return false;
    }
    
    // Check if date is not in the future
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;
    
    // Allow dates up to today
    if (year > currentYear) return false;
    if (year == currentYear && month > currentMonth) return false;
    if (year == currentYear && month == currentMonth && day > currentDay) return false;
    
    return true;
}

// Get validated date input from user
std::string getValidDate() {
    std::string date;
    while (true) {
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        
        if (isValidDate(date)) {
            return date;
        } else {
            std::cout << "Invalid date! Please enter a valid date in YYYY-MM-DD format.\n";
            std::cout << "Date must be between 1900-2100 and not in the future.\n";
        }
    }
}

int main() {
    // Try different possible paths for the CSV file
    std::string csvPath = "data/sample_expenses.csv";
    std::ifstream testFile(csvPath);
    if (!testFile.is_open()) {
        csvPath = "../data/sample_expenses.csv";
        testFile.open(csvPath);
        if (!testFile.is_open()) {
            csvPath = "../../data/sample_expenses.csv";
        }
    }
    testFile.close();
    
    ExpenseStore store(csvPath);

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
        
        // Input validation with better error handling
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number (0-5).\n";
            continue;
        }
        
        // Check if choice is within valid range
        if (choice < 0 || choice > 5) {
            std::cout << "Invalid choice! Please enter a number between 0 and 5.\n";
            continue;
        }

        if (choice == 1) {
            Expense e;
            e.id = generateID();
            e.date = getValidDate();
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
            std::cout << "Expense added successfully!\n";
        }
        else if (choice == 2) {
            store.listExpenses();
        }
        else if (choice == 3) {
            std::string start, end;
            std::cout << "Enter start date (YYYY-MM-DD): ";
            std::cin >> start;
            if (!isValidDate(start)) {
                std::cout << "Invalid start date! Please use YYYY-MM-DD format.\n";
                continue;
            }
            std::cout << "Enter end date (YYYY-MM-DD): ";
            std::cin >> end;
            if (!isValidDate(end)) {
                std::cout << "Invalid end date! Please use YYYY-MM-DD format.\n";
                continue;
            }
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
