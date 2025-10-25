# Expense Tracker - C++ Application

A command-line expense tracking application built in C++ that allows users to manage their personal finances by adding, viewing, and analyzing expenses.

## Features

-  **Add Expenses** - Record new expenses with date, amount, category, and description
-  **List All Expenses** - View all expenses in a formatted table
-  **Filter by Date Range** - Find expenses between specific dates
-  **Filter by Category** - View expenses by category (Food, Transport, etc.)
-  **Summary by Category** - Get spending breakdown by category
-  **Data Persistence** - Automatically saves to CSV file
-  **Input Validation** - Robust error handling and input validation
-  **Sample Data** - Includes sample expenses for testing

## Prerequisites

### Required Software:
1. **Visual Studio Build Tools 2022** (or Visual Studio Community)
2. **CMake** (version 3.10 or higher)
3. **Windows 10/11**

### Installation Steps:

#### Step 1: Install Visual Studio Build Tools
```powershell
winget install Microsoft.VisualStudio.2022.BuildTools

#### Step 2: Install CMake
```powershell
# Using winget
winget install Kitware.CMake

# Or download from: https://cmake.org/download/
```

## Project Structure

```
cpp/
├── CMakeLists.txt          # CMake configuration
├── include/
│   └── expense.h           # Expense struct definition
├── src/
│   ├── main.cpp           # Main application logic
│   └── expense_store.cpp   # Data management class
├── data/
│   └── sample_expenses.csv # Sample data file
└── build/                 # Build output directory
    └── Release/
        └── expense_tracker.exe
```

## Build Instructions

### Step 1: Navigate to Project Directory
```powershell
cd C:\Users\sarvi\Desktop\ExpenseTracker-Team2\cpp
```

### Step 2: Configure CMake
```powershell
cmake -S . -B build -G "Visual Studio 17 2022"
```

### Step 3: Build the Project
```powershell
cmake --build build --config Release
```

### Step 4: Run the Program
```powershell
.\build\Release\expense_tracker.exe
```

## Usage Guide

### Starting the Application
```powershell
.\build\Release\expense_tracker.exe
```

### Menu Options
```
===== Expense Tracker Menu =====
1. Add Expense
2. List All Expenses
3. Filter by Date Range
4. Filter by Category
5. Summary by Category
0. Exit
Enter choice:
```

### Adding an Expense
1. Select option `1` from the menu
2. Enter date in format `YYYY-MM-DD` (e.g., `2024-01-15`)
3. Enter amount as a positive number (e.g., `25.50`)
4. Enter category (e.g., `Food`, `Transport`, `Shopping`)
5. Enter description (e.g., `Lunch at restaurant`)

### Viewing Expenses
- **List All**: Select option `2` to see all expenses in a formatted table
- **Filter by Date**: Select option `3` and enter start/end dates
- **Filter by Category**: Select option `4` and enter category name
- **Summary**: Select option `5` for spending breakdown by category

## Sample Data

The application includes sample expenses for testing:

| ID    | Date       | Amount | Category  | Description    |
|-------|------------|--------|-----------|----------------|
| E1001 | 2025-10-01 | $25.50 | Food      | Lunch          |
| E1002 | 2025-10-03 | $50.00 | Transport | Gas refill     |
| E1003 | 2025-10-10 | $120.00| Rent      | Monthly rent   |
| E1004 | 2025-10-15 | $15.75 | Food      | Snacks         |
| E1005 | 2025-10-20 | $80.00 | Shopping  | New shoes      |

## Data Storage

- **File Format**: CSV (Comma-Separated Values)
- **Location**: `data/sample_expenses.csv`
- **Auto-Save**: Data is automatically saved when adding expenses
- **Auto-Load**: Data is automatically loaded when starting the application

## Error Handling

The application includes comprehensive error handling:

- **Input Validation**: Prevents invalid menu choices and negative amounts
- **File Operations**: Checks for successful file read/write operations
- **CSV Parsing**: Handles descriptions with commas correctly
- **User Feedback**: Clear error messages and validation prompts

## Troubleshooting

### Common Issues:

#### 1. "CMake not found"
```powershell
# Install CMake
winget install Kitware.CMake
# Refresh environment
$env:PATH = [System.Environment]::GetEnvironmentVariable("PATH","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("PATH","User")
```

#### 2. "Visual Studio not found"
```powershell
# Install Build Tools
winget install Microsoft.VisualStudio.2022.BuildTools
```

## Development Notes

### Code Structure:
- **expense.h**: Defines the Expense struct with display functionality
- **main.cpp**: Contains the main menu loop and user interaction
- **expense_store.cpp**: Handles data persistence and filtering operations

### Key Improvements Made:
1. **CSV Parsing**: Fixed to handle commas in description fields
2. **Input Validation**: Added comprehensive validation for all user inputs
3. **Error Handling**: Enhanced file operations with proper error checking
4. **Display Formatting**: Improved output with headers and proper alignment
5. **User Experience**: Added clear error messages and validation prompts

## License

This project is part of a team development exercise for learning C++ programming concepts including:
- Object-oriented programming
- File I/O operations
- Data structures (vectors, maps)
- Input validation
- Error handling
- CMake build system

## Contributing

This is a learning project. Feel free to suggest improvements or report issues for educational purposes.
