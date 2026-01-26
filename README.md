# 💰 Household Expense Tracker

A simple, efficient, and persistent Command Line Interface (CLI) application built in C++ to help users track their daily expenses and manage monthly budgets.

## 📝 Description

This project is a console-based application designed to help individuals manage their personal finances. It allows users to record daily spending, view a history of expenses, set a monthly budget, and analyze their financial status (whether they are within budget or overspending). 

All data is **persistent**, meaning expenses and budget settings are saved to text files (`expenses.txt` and `budget.txt`) and reloaded automatically when the program starts.

## ✨ Features

* **Add Expenses:** Record items with cost and date.
    * *Smart Date Entry:* Automatically uses the current system date if the user skips the date input.
* **View History:** Displays a clean, tabulated list of all recorded expenses.
* **Budget Management:** Set a monthly budget limit.
* **Financial Statistics:**
    * Calculates total spending.
    * Shows remaining budget.
    * Alerts if you are over budget.
* **Data Persistence:** Uses file handling (`fstream`) to save data so it isn't lost when the program closes.
* **Currency:** Defaulted to Pakistani Rupees (Rs).

## 🛠️ Tech Stack

* **Language:** C++
* **Libraries Used:** `<iostream>`, `<vector>`, `<fstream>`, `<iomanip>`, `<algorithm>`, `<ctime>`
* **Interface:** Console / Command Line

## 🚀 How to Run

### Prerequisites
You need a C++ compiler installed on your system (e.g., **g++** via MinGW or Visual Studio).

### Compilation & Execution

1.  **Clone the repository** (or download the source code):
    ```bash
    git clone [https://github.com/your-username/expense-tracker.git](https://github.com/your-username/expense-tracker.git)
    cd expense-tracker
    ```

2.  **Compile the code:**
    ```bash
    g++ main.cpp -o expense_tracker
    ```

3.  **Run the application:**
    * **Windows:**
        ```bash
        expense_tracker.exe
        ```
    * **Linux/Mac:**
        ```bash
        ./expense_tracker
        ```

## 📂 File Structure

* `main.cpp`: The source code containing the logic.
* `expenses.txt`: Automatically created to store transaction history.
* `budget.txt`: Automatically created to store your budget limit.

## ⚠️ Note for Linux/macOS Users

The current code uses `system("cls")` to clear the screen, which is specific to **Windows**. 

If you are running this on Linux or macOS, please modify the `displayMenu` function in `main.cpp`:

**Change this:**
```cpp
system("cls");
