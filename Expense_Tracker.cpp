#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

// Structure to hold each expense
struct Expense {
    string item;
    double cost;
    string date;
};

// Global variable for budget
double monthlyBudget = 0.0;

// Function prototypes
void displayMenu();
void addExpense(vector<Expense>& expenses);
void viewExpenses(const vector<Expense>& expenses);
void saveToFile(const vector<Expense>& expenses);
void loadFromFile(vector<Expense>& expenses);
void showStatistics(const vector<Expense>& expenses);
void setBudget();
void saveBudgetToFile();
void loadBudgetFromFile();
string getCurrentDate();

int main() {
    vector<Expense> expenses;
    
    // Load existing data and budget
    loadFromFile(expenses);
    loadBudgetFromFile();
    
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch(choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                showStatistics(expenses);
                break;
            case 4:
                setBudget();
                break;
            case 5:
                cout << "\nData saved successfully! Exiting...\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while(choice != 5);
    
    // Save data before exiting
    saveToFile(expenses);
    saveBudgetToFile();
    
    return 0;
}

void displayMenu() {
    system("cls"); // Clear screen (use "clear" for Linux/Mac)
    
    cout << "\n==========================================\n";
    cout << "        HOUSEHOLD EXPENSE TRACKER\n";
    cout << "==========================================\n";
    cout << "1. Add New Expense\n";
    cout << "2. View All Expenses\n";
    cout << "3. Show Statistics\n";
    cout << "4. Set Budget\n";
    cout << "5. Save & Exit\n";
    cout << "==========================================\n";
    if(monthlyBudget > 0) {
        cout << "Current Monthly Budget: Rs " << fixed << setprecision(2) << monthlyBudget << endl;
        cout << "==========================================\n";
    }
}

void addExpense(vector<Expense>& expenses) {
    Expense newExpense;
    
    cout << "\n--- Add New Expense ---\n";
    
    cout << "Enter item name: ";
    getline(cin, newExpense.item);
    
    cout << "Enter cost: ";
    cin >> newExpense.cost;
    cin.ignore(); // Clear buffer
    
    cout << "Enter date (DD/MM/YYYY) or press Enter for today: ";
    string dateInput;
    getline(cin, dateInput);
    
    if(dateInput.empty()) {
        newExpense.date = getCurrentDate();
    } else {
        newExpense.date = dateInput;
    }
    
    expenses.push_back(newExpense);
    
    cout << "\nExpense added successfully!\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void viewExpenses(const vector<Expense>& expenses) {
    if(expenses.empty()) {
        cout << "\nNo expenses recorded yet!\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    cout << "\n--- All Expenses ---\n";
    cout << left << setw(5) << "No." << setw(20) << "Item" 
         << setw(15) << "Cost" << setw(12) << "Date" << endl;
    cout << string(55, '-') << endl;
    
    double total = 0;
    string previousDate = "";
    
    for(int i = 0; i < expenses.size(); i++) {
        // Add blank line when date changes
        if(previousDate != "" && previousDate != expenses[i].date) {
            cout << endl; // Blank line between different dates
        }
        
        cout << left << setw(5) << i+1 
             << setw(20) << expenses[i].item 
             << setw(15) << fixed << setprecision(2) << expenses[i].cost 
             << setw(12) << expenses[i].date << endl;
        total += expenses[i].cost;
        
        previousDate = expenses[i].date;
    }
    
    cout << string(55, '-') << endl;
    cout << "Total: Rs " << fixed << setprecision(2) << total << endl;
    cout << "\nPress Enter to continue...";
    cin.get();
}

void showStatistics(const vector<Expense>& expenses) {
    if(expenses.empty()) {
        cout << "\nNo expenses to analyze!\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    double total = 0;
    for(int i = 0; i < expenses.size(); i++) {
        total += expenses[i].cost;
    }
    
    double remainingBudget = monthlyBudget - total;
    
    cout << "\n--- Budget Analysis ---\n";
    cout << left << setw(25) << "Monthly Budget:" << "Rs " << fixed << setprecision(2) << monthlyBudget << endl;
    cout << left << setw(25) << "Total Spent:" << "Rs " << fixed << setprecision(2) << total << endl;
    cout << left << setw(25) << "Remaining Budget:" << "Rs " << fixed << setprecision(2) << remainingBudget << endl;
    cout << string(55, '-') << endl;
    
    if(remainingBudget >= 0) {
        cout << "Status: Within Budget\n";
    } else {
        cout << "Status: Over Budget by Rs " << fixed << setprecision(2) << -remainingBudget << endl;
    }
    
    cout << "\nPress Enter to continue...";
    cin.get();
}

void setBudget() {
    cout << "\n--- Set Monthly Budget ---\n";
    if(monthlyBudget > 0) {
        cout << "Current Monthly Budget: Rs " << fixed << setprecision(2) << monthlyBudget << endl;
    }
    cout << "Enter new monthly budget (Rs): ";
    cin >> monthlyBudget;
    
    if(monthlyBudget > 0) {
        cout << "\nMonthly budget set to: Rs " << fixed << setprecision(2) << monthlyBudget << endl;
        saveBudgetToFile(); // Save immediately after setting
    } else {
        cout << "\nInvalid budget amount!\n";
        monthlyBudget = 0.0;
    }
    
    cout << "Press Enter to continue...";
    cin.get();
    cin.get(); // Extra get() to clear the buffer
}

void saveToFile(const vector<Expense>& expenses) {
    ofstream file("expenses.txt");
    
    if(file.is_open()) {
        for(int i = 0; i < expenses.size(); i++) {
            file << expenses[i].item << "," << expenses[i].cost << "," << expenses[i].date << "\n";
        }
        file.close();
    }
}

void loadFromFile(vector<Expense>& expenses) {
    ifstream file("expenses.txt");
    
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string item, costStr, date;
            
            getline(ss, item, ',');
            getline(ss, costStr, ',');
            getline(ss, date);
            
            Expense expense;
            expense.item = item;
            expense.cost = atof(costStr.c_str());
            expense.date = date;
            
            expenses.push_back(expense);
        }
        file.close();
    }
}

void saveBudgetToFile() {
    ofstream file("budget.txt");
    if(file.is_open()) {
        file << monthlyBudget;
        file.close();
    }
}

void loadBudgetFromFile() {
    ifstream file("budget.txt");
    if(file.is_open()) {
        file >> monthlyBudget;
        file.close();
    }
}

string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    
    stringstream ss;
    ss << setw(2) << setfill('0') << localTime->tm_mday << "/"
       << setw(2) << setfill('0') << (localTime->tm_mon + 1) << "/"
       << (localTime->tm_year + 1900);
    
    return ss.str();
}

