# Expense Tracker - C++

Command-line expense tracking application available in both C++.

## Prerequisites

### C++ Version:
- Visual Studio Build Tools 2022
- CMake 3.10+
- Windows 10/11

## Installation

### C++ Prerequisites:
```powershell
winget install Microsoft.VisualStudio.2022.BuildTools
winget install Kitware.CMake
```
## Build & Run Instructions

### C++ Version:
```powershell
# Navigate to project directory
cd ./ExpenseTracker-Team2

# Configure CMake
cmake -S . -B build -G "Visual Studio 17 2022"

# Build project
cmake --build build --config Release

# Run application
.\build\Release\expense_tracker.exe
```

## Usage

### C++ Menu Options:
1. Add Expense
2. List All Expenses
3. Filter by Date Range
4. Filter by Category
5. Summary by Category
0. Exit

## Troubleshooting

### C++ Issues:
- **CMake not found**: `winget install Kitware.CMake`
- **Visual Studio not found**: `winget install Microsoft.VisualStudio.2022.BuildTools`


# Expense Tracker - Python
Command-line expense tracking application available in Python.

### Python Version:
- Python 3.7+

## Installation

### Python Prerequisites:
```powershell
winget install Python.Python.3.11
```

## Build & Run Instructions

### Python Version:
```powershell
# Navigate to project directory
cd ./ExpenseTracker-Team2

# Run application
python python/expense_tracker_python.py
```

## Usage

### Python Menu Options:
1. Add Expense
2. View All Expenses
3. Filter Expenses
4. Show Summary
5. Exit

## Troubleshooting

### C++ Issues:
- **CMake not found**: `winget install Kitware.CMake`
- **Visual Studio not found**: `winget install Microsoft.VisualStudio.2022.BuildTools`

### Python Issues:
- **Python not found**: `winget install Python.Python.3.11`
- **Permission denied**: Run from correct directory
- **Module errors**: Verify with `python --version`
