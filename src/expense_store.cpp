// cpp/src/expense_store.cpp
#include "../include/expense.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

class ExpenseStore {
private:
    std::vector<Expense> expenses;
    std::string filepath;

public:
    ExpenseStore(const std::string &path) : filepath(path) {
        load();
    }

    // Load expenses from CSV file
    void load() {
        expenses.clear();
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "No existing data file found. Starting fresh.\n";
            return;
        }

        std::string line;
        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            if (line.empty()) continue; // Skip empty lines
            
            std::stringstream ss(line);
            Expense e;
            std::string amountStr;
            
            // Parse CSV fields properly
            std::getline(ss, e.id, ',');
            std::getline(ss, e.date, ',');
            std::getline(ss, amountStr, ',');
            std::getline(ss, e.category, ',');
            std::getline(ss, e.description); // Get rest of line for description (may contain commas)
            
            // Convert amount string to double
            try {
                e.amount = std::stod(amountStr);
            } catch (const std::exception&) {
                e.amount = 0.0; // Default to 0 if conversion fails
            }
            
            expenses.push_back(e);
        }
        file.close();
    }

    // Save expenses to CSV file
    void save() const {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not save to file " << filepath << std::endl;
            return;
        }
        
        file << "id,date,amount,category,description\n";
        for (const auto &e : expenses) {
            file << e.id << "," << e.date << ","
                 << std::fixed << std::setprecision(2) << e.amount << ","
                 << e.category << "," << e.description << "\n";
        }
        file.close();
    }

    // Add new expense
    void addExpense(const Expense &e) {
        expenses.push_back(e);
        save();
    }

    // List all expenses
    void listExpenses() const {
        std::cout << "\n--- All Expenses ---\n";
        if (expenses.empty()) {
            std::cout << "No expenses found.\n";
            return;
        }
        
        // Print header
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(12) << "Date" 
                  << std::setw(10) << "Amount"
                  << std::setw(15) << "Category" 
                  << "Description" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (const auto &e : expenses) e.display();
    }

    // Filter by date range
    void filterByDate(const std::string &start, const std::string &end) const {
        std::cout << "\n--- Filtered Expenses (" << start << " to " << end << ") ---\n";
        for (const auto &e : expenses) {
            if (e.date >= start && e.date <= end)
                e.display();
        }
    }

    // Filter by category
    void filterByCategory(const std::string &cat) const {
        std::cout << "\n--- Category: " << cat << " ---\n";
        for (const auto &e : expenses) {
            if (e.category == cat)
                e.display();
        }
    }

    // Summarize by category
    void summarizeByCategory() const {
        std::map<std::string, double> totals;
        double grandTotal = 0.0;

        for (const auto &e : expenses) {
            totals[e.category] += e.amount;
            grandTotal += e.amount;
        }

        std::cout << "\n--- Summary by Category ---\n";
        for (const auto &[cat, total] : totals) {
            std::cout << std::left << std::setw(15) << cat
                      << " $" << std::fixed << std::setprecision(2)
                      << total << std::endl;
        }
        std::cout << "-----------------------------\n";
        std::cout << "Total: $" << std::fixed << std::setprecision(2)
                  << grandTotal << "\n";
    }
};
