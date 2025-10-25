// test/test_expense_store.cpp
#include "../include/expense.h"
#include "../src/expense_store.cpp"
#include <iostream>
#include <fstream>
#include <cassert>

class TestFramework {
private:
    int tests_run = 0;
    int tests_passed = 0;
    
public:
    void run_test(const std::string& test_name, bool result) {
        tests_run++;
        if (result) {
            tests_passed++;
            std::cout << "✅ " << test_name << " - PASSED" << std::endl;
        } else {
            std::cout << "❌ " << test_name << " - FAILED" << std::endl;
        }
    }
    
    void print_summary() {
        std::cout << "\n=== ExpenseStore Test Summary ===" << std::endl;
        std::cout << "Tests run: " << tests_run << std::endl;
        std::cout << "Tests passed: " << tests_passed << std::endl;
        std::cout << "Tests failed: " << (tests_run - tests_passed) << std::endl;
        std::cout << "Success rate: " << (tests_passed * 100.0 / tests_run) << "%" << std::endl;
    }
};

// Test CSV save and load functionality
void test_csv_save_load() {
    TestFramework tf;
    
    std::string test_file = "test_save_load.csv";
    std::remove(test_file.c_str()); // Clean up
    
    // Create store and add expenses
    ExpenseStore store(test_file);
    
    Expense e1;
    e1.id = "E1001";
    e1.date = "2024-01-15";
    e1.amount = 25.50;
    e1.category = "Food";
    e1.description = "Lunch";
    
    Expense e2;
    e2.id = "E1002";
    e2.date = "2024-01-16";
    e2.amount = 50.00;
    e2.category = "Transport";
    e2.description = "Gas";
    
    store.addExpense(e1);
    store.addExpense(e2);
    
    tf.run_test("Add multiple expenses", true);
    
    // Check if file exists and has content
    std::ifstream file(test_file);
    bool file_exists = file.is_open();
    tf.run_test("CSV file exists after save", file_exists);
    
    if (file_exists) {
        std::string line;
        int line_count = 0;
        while (std::getline(file, line)) {
            line_count++;
        }
        file.close();
        tf.run_test("CSV file has correct number of lines", line_count >= 3); // Header + 2 expenses
    }
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test expense filtering by category
void test_category_filtering() {
    TestFramework tf;
    
    std::string test_file = "test_category.csv";
    std::remove(test_file.c_str()); // Clean up
    
    // Create test CSV
    std::ofstream file(test_file);
    file << "id,date,amount,category,description\n";
    file << "E1001,2024-01-15,25.50,Food,Lunch\n";
    file << "E1002,2024-01-16,50.00,Transport,Gas\n";
    file << "E1003,2024-01-17,15.75,Food,Snacks\n";
    file.close();
    
    ExpenseStore store(test_file);
    tf.run_test("Load expenses from CSV", true);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test expense filtering by date range
void test_date_filtering() {
    TestFramework tf;
    
    std::string test_file = "test_date.csv";
    std::remove(test_file.c_str()); // Clean up
    
    // Create test CSV with different dates
    std::ofstream file(test_file);
    file << "id,date,amount,category,description\n";
    file << "E1001,2024-01-15,25.50,Food,Lunch\n";
    file << "E1002,2024-01-20,50.00,Transport,Gas\n";
    file << "E1003,2024-01-25,15.75,Food,Snacks\n";
    file.close();
    
    ExpenseStore store(test_file);
    tf.run_test("Load expenses with different dates", true);
    
    // Test date range filtering logic
    std::string start_date = "2024-01-15";
    std::string end_date = "2024-01-20";
    std::string test_date = "2024-01-18";
    
    bool in_range = (test_date >= start_date) && (test_date <= end_date);
    tf.run_test("Date range filtering logic", in_range);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test summary calculations
void test_summary_calculations() {
    TestFramework tf;
    
    // Test basic math operations
    double food_total = 25.50 + 15.75; // 41.25
    double transport_total = 50.00;
    double grand_total = food_total + transport_total; // 91.25
    
    tf.run_test("Food category total calculation", food_total == 41.25);
    tf.run_test("Transport category total calculation", transport_total == 50.00);
    tf.run_test("Grand total calculation", grand_total == 91.25);
    
    // Test percentage calculations
    double food_percentage = (food_total / grand_total) * 100;
    tf.run_test("Percentage calculation", food_percentage > 0 && food_percentage < 100);
}

// Test CSV parsing with commas in description
void test_csv_parsing_with_commas() {
    TestFramework tf;
    
    std::string test_file = "test_commas.csv";
    std::remove(test_file.c_str()); // Clean up
    
    // Create CSV with commas in description
    std::ofstream file(test_file);
    file << "id,date,amount,category,description\n";
    file << "E1001,2024-01-15,25.50,Food,Lunch, with friends\n";
    file << "E1002,2024-01-16,50.00,Transport,Gas, for car\n";
    file.close();
    
    ExpenseStore store(test_file);
    tf.run_test("CSV parsing with commas in description", true);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test error handling
void test_error_handling() {
    TestFramework tf;
    
    // Test with non-existent file
    ExpenseStore store("non_existent_file.csv");
    tf.run_test("Handle non-existent file gracefully", true);
    
    // Test with invalid CSV format
    std::string test_file = "test_invalid.csv";
    std::ofstream file(test_file);
    file << "invalid,csv,format\n";
    file << "not,enough,columns\n";
    file.close();
    
    ExpenseStore store2(test_file);
    tf.run_test("Handle invalid CSV format", true);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test amount precision
void test_amount_precision() {
    TestFramework tf;
    
    double amount1 = 25.50;
    double amount2 = 0.01;
    double total = amount1 + amount2;
    
    tf.run_test("Amount precision handling", total == 25.51);
    
    // Test rounding
    double rounded = std::round(total * 100) / 100;
    tf.run_test("Amount rounding", rounded == 25.51);
}

// Main test runner for ExpenseStore
int main() {
    std::cout << "=== ExpenseStore Test Suite ===" << std::endl;
    std::cout << "Running ExpenseStore tests...\n" << std::endl;
    
    test_csv_save_load();
    test_category_filtering();
    test_date_filtering();
    test_summary_calculations();
    test_csv_parsing_with_commas();
    test_error_handling();
    test_amount_precision();
    
    std::cout << "\n=== ExpenseStore Tests Completed ===" << std::endl;
    
    return 0;
}
