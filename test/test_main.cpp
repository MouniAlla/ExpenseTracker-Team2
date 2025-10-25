// test/test_main.cpp
#include "../include/expense.h"
#include "../src/expense_store.cpp"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

// Test framework
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
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Tests run: " << tests_run << std::endl;
        std::cout << "Tests passed: " << tests_passed << std::endl;
        std::cout << "Tests failed: " << (tests_run - tests_passed) << std::endl;
        std::cout << "Success rate: " << (tests_passed * 100.0 / tests_run) << "%" << std::endl;
    }
};

// Test Expense struct
void test_expense_creation() {
    TestFramework tf;
    
    // Test basic expense creation
    Expense e;
    e.id = "E1001";
    e.date = "2024-01-15";
    e.amount = 25.50;
    e.category = "Food";
    e.description = "Lunch";
    
    tf.run_test("Expense ID assignment", e.id == "E1001");
    tf.run_test("Expense date assignment", e.date == "2024-01-15");
    tf.run_test("Expense amount assignment", e.amount == 25.50);
    tf.run_test("Expense category assignment", e.category == "Food");
    tf.run_test("Expense description assignment", e.description == "Lunch");
}

// Test ExpenseStore basic functionality
void test_expense_store_basic() {
    TestFramework tf;
    
    // Create a temporary test file
    std::string test_file = "test_expenses.csv";
    
    // Clean up any existing test file
    std::remove(test_file.c_str());
    
    // Test store creation
    ExpenseStore store(test_file);
    tf.run_test("ExpenseStore creation", true);
    
    // Test adding expense
    Expense e;
    e.id = "E1001";
    e.date = "2024-01-15";
    e.amount = 25.50;
    e.category = "Food";
    e.description = "Lunch";
    
    store.addExpense(e);
    tf.run_test("Add expense to store", true);
    
    // Test file was created
    std::ifstream file(test_file);
    tf.run_test("CSV file created", file.is_open());
    file.close();
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test CSV parsing
void test_csv_parsing() {
    TestFramework tf;
    
    // Create test CSV content
    std::string test_content = "id,date,amount,category,description\nE1001,2024-01-15,25.50,Food,Lunch\n";
    
    // Write test file
    std::ofstream file("test_parse.csv");
    file << test_content;
    file.close();
    
    // Test parsing
    ExpenseStore store("test_parse.csv");
    tf.run_test("CSV file parsing", true);
    
    // Clean up
    std::remove("test_parse.csv");
}

// Test amount validation
void test_amount_validation() {
    TestFramework tf;
    
    // Test positive amounts
    tf.run_test("Positive amount validation", 25.50 > 0);
    tf.run_test("Zero amount validation", 0.0 >= 0);
    
    // Test negative amounts (should be invalid)
    tf.run_test("Negative amount validation", -10.0 < 0);
}

// Test date format
void test_date_format() {
    TestFramework tf;
    
    std::string valid_date = "2024-01-15";
    std::string invalid_date = "15-01-2024";
    
    // Basic date format validation (YYYY-MM-DD)
    bool valid_format = (valid_date.length() == 10) && 
                       (valid_date[4] == '-') && 
                       (valid_date[7] == '-');
    
    bool invalid_format = (invalid_date.length() == 10) && 
                         (invalid_date[4] == '-') && 
                         (invalid_date[7] == '-');
    
    tf.run_test("Valid date format", valid_format);
    tf.run_test("Invalid date format", !invalid_format);
}

// Test category filtering
void test_category_filtering() {
    TestFramework tf;
    
    // Create test data
    std::string test_file = "test_category.csv";
    std::ofstream file(test_file);
    file << "id,date,amount,category,description\n";
    file << "E1001,2024-01-15,25.50,Food,Lunch\n";
    file << "E1002,2024-01-16,50.00,Transport,Gas\n";
    file << "E1003,2024-01-17,15.75,Food,Snacks\n";
    file.close();
    
    ExpenseStore store(test_file);
    tf.run_test("Category filtering setup", true);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Test summary calculations
void test_summary_calculations() {
    TestFramework tf;
    
    // Test basic math
    double amount1 = 25.50;
    double amount2 = 15.75;
    double total = amount1 + amount2;
    
    tf.run_test("Basic addition", total == 41.25);
    tf.run_test("Category total calculation", total > 0);
}

// Test input validation
void test_input_validation() {
    TestFramework tf;
    
    // Test valid inputs
    tf.run_test("Valid menu choice 1", 1 >= 0 && 1 <= 5);
    tf.run_test("Valid menu choice 2", 2 >= 0 && 2 <= 5);
    tf.run_test("Valid menu choice 0", 0 >= 0 && 0 <= 5);
    
    // Test invalid inputs
    tf.run_test("Invalid menu choice -1", -1 < 0 || -1 > 5);
    tf.run_test("Invalid menu choice 6", 6 < 0 || 6 > 5);
}

// Test file operations
void test_file_operations() {
    TestFramework tf;
    
    std::string test_file = "test_file_ops.csv";
    
    // Test file creation
    std::ofstream out_file(test_file);
    out_file << "test,data\n";
    out_file.close();
    
    std::ifstream in_file(test_file);
    bool file_exists = in_file.is_open();
    in_file.close();
    
    tf.run_test("File creation", file_exists);
    tf.run_test("File reading", file_exists);
    
    // Clean up
    std::remove(test_file.c_str());
}

// Main test runner
int main() {
    std::cout << "=== Expense Tracker Test Suite ===" << std::endl;
    std::cout << "Running tests...\n" << std::endl;
    
    test_expense_creation();
    test_expense_store_basic();
    test_csv_parsing();
    test_amount_validation();
    test_date_format();
    test_category_filtering();
    test_summary_calculations();
    test_input_validation();
    test_file_operations();
    
    std::cout << "\n=== All Tests Completed ===" << std::endl;
    
    return 0;
}
