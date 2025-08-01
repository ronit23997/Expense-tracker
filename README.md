# Expense Tracker (C)

A command-line personal expense tracker written in C, featuring multi-currency support, persistent file storage, and advanced filtering and statistics.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Multi-currency support:** Add expenses in USD, EUR, INR, or GBP, with real-time conversion for statistics.
- **Persistent storage:** Expenses are saved to a file and loaded automatically on startup.
- **Menu-driven workflow:** Easily add, view, and search expenses by category or month.
- **Statistical analysis:** View total, average, highest, and lowest expenses in your preferred currency.
- **Monthly filtering:** Quickly view all expenses for a specific month.

## Getting Started

### Prerequisites

- GCC or any standard C compiler

### Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/expense-tracker-c.git
    cd expense-tracker-c
    ```

2. **Compile the source code:**
    ```bash
    gcc expense_tracker.c -o expense_tracker
    ```

3. **Run the application:**
    ```bash
    ./expense_tracker
    ```

## Usage

- **Add Expense:** Enter the date, category, amount, currency, and description.
- **View All Expenses:** Display all recorded expenses.
- **Search by Category:** Filter expenses by category.
- **View by Month:** Filter expenses by a specific month (YYYY-MM).
- **Show Statistics:** View total, average, highest, and lowest expenses in your chosen currency.
- **Save & Exit:** Save all data to `expenses.dat` for future sessions.

All data is stored in `expenses.dat` in the project directory.

