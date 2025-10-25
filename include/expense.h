// cpp/include/expense.h
#pragma once
#include <string>
#include <iostream>
#include <iomanip>

// Expense struct definition
struct Expense {
    std::string id;          // unique identifier
    std::string date;        // format: YYYY-MM-DD
    double amount;           // expense amount
    std::string category;    // e.g., Food, Travel, Rent
    std::string description; // short text

    // Display function
    void display() const {
        std::cout << std::left << std::setw(8) << id 
                  << std::setw(12) << date 
                  << std::setw(10) << std::fixed << std::setprecision(2) << "$" << amount
                  << std::setw(15) << category 
                  << description << std::endl;
    }
};
