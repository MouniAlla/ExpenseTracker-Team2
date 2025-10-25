# ===========================================
# Expense Tracker Application
# Language: Python 3
# Author: [Team 2]
# ===========================================

from datetime import datetime
import sys

# Global list to store expense records
expenses = []

# -------------------------------
# Function: Add Expense
# -------------------------------
def add_expense():
    """Prompts user for expense details and adds it to the list."""
    print("\n=== Add New Expense ===")
    try:
        date_str = input("Enter date (YYYY-MM-DD): ")
        date = datetime.strptime(date_str, "%Y-%m-%d")
        amount = float(input("Enter amount (e.g. 45.75): "))
        category = input("Enter category (e.g. Food, Transport): ").strip()
        description = input("Enter description: ").strip()

        # Create expense dictionary
        expense = {
            "date": date,
            "amount": amount,
            "category": category,
            "description": description
        }

        expenses.append(expense)
        print("Expense added successfully!\n")

    except ValueError:
        print("Invalid input! Please use correct formats (e.g. YYYY-MM-DD for date).")
    except (EOFError, KeyboardInterrupt):
        print("\nOperation cancelled.")

# -------------------------------
# Function: View All Expenses
# -------------------------------
def view_expenses():
    """Displays all recorded expenses."""
    print("\n=== All Expenses ===")
    if not expenses:
        print("No expenses recorded yet.\n")
        return

    print(f"{'Date':<12} {'Amount':<10} {'Category':<15} {'Description'}")
    print("-" * 55)
    for e in expenses:
        print(f"{e['date'].date()}  ${e['amount']:<8.2f}  {e['category']:<15}  {e['description']}")
    print()

# -------------------------------
# Function: Filter Expenses
# -------------------------------
def filter_expenses():
    """Filters expenses by category or date range."""
    print("\n=== Filter Expenses ===")
    try:
        category = input("Enter category to filter (leave blank for all): ").strip()
        start_str = input("Enter start date (YYYY-MM-DD, leave blank for none): ").strip()
        end_str = input("Enter end date (YYYY-MM-DD, leave blank for none): ").strip()

        start_date = datetime.strptime(start_str, "%Y-%m-%d") if start_str else None
        end_date = datetime.strptime(end_str, "%Y-%m-%d") if end_str else None

        filtered = expenses
        if category:
            filtered = [e for e in filtered if e['category'].lower() == category.lower()]
        if start_date and end_date:
            filtered = [e for e in filtered if start_date <= e['date'] <= end_date]

        if not filtered:
            print("No expenses found for the given filters.\n")
            return

        print(f"\nFiltered Expenses (Category: {category or 'All'})")
        print(f"{'Date':<12} {'Amount':<10} {'Category':<15} {'Description'}")
        print("-" * 55)
        for e in filtered:
            print(f"{e['date'].date()}  ${e['amount']:<8.2f}  {e['category']:<15}  {e['description']}")
        print()
    except (EOFError, KeyboardInterrupt):
        print("\nOperation cancelled.")
    except ValueError:
        print("Invalid date format! Please use YYYY-MM-DD format.")

# -------------------------------
# Function: Summary
# -------------------------------
def summary():
    """Shows total and per-category spending."""
    print("\n=== Expense Summary ===")
    if not expenses:
        print("No expenses to summarize.\n")
        return

    total = sum(e['amount'] for e in expenses)
    print(f"Total Expenses: ${total:.2f}\n")

    category_totals = {}
    for e in expenses:
        category_totals[e['category']] = category_totals.get(e['category'], 0) + e['amount']

    print("Expenses by Category:")
    for cat, amt in category_totals.items():
        print(f"  {cat:<15} ${amt:.2f}")
    print()

# -------------------------------
# Function: Menu Display
# -------------------------------
def show_menu():
    """Displays the main menu."""
    print("===================================")
    print("     Expense Tracker Menu       ")
    print("===================================")
    print("1. Add Expense")
    print("2. View All Expenses")
    print("3. Filter Expenses")
    print("4. Show Summary")
    print("5. Exit")
    print("===================================")

# -------------------------------
# Main Program Loop
# -------------------------------
def main():
    """Runs the main menu loop."""
    while True:
        show_menu()
        try:
            choice = input("Enter your choice (1-5): ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nExiting Expense Tracker. Goodbye!")
            sys.exit()

        if choice == "1":
            add_expense()
        elif choice == "2":
            view_expenses()
        elif choice == "3":
            filter_expenses()
        elif choice == "4":
            summary()
        elif choice == "5":
            print("Exiting Expense Tracker. Goodbye!")
            sys.exit()
        else:
            print("Invalid choice! Please enter a number between 1 and 5.\n")

# Run the program
if __name__ == "__main__":
    main()


