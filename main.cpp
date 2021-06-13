#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "models/data.h"
#include "utils/data_io_utils.h"
#include "utils/file_io_utils.h"

using namespace std;

vector<Data> expenses;
vector<Data> incomes;
vector<Data> recurringCost;

const string incomesSaveFilePath = "../incomes.txt";
const string expensesSaveFilePath = "../expenses.txt";
const string recurringCostsSaveFilePath = "../recurring_costs.txt";


void displayMainMenu() // Displays the main menu to the user
{
    // Displays the main menu of the app
    cout << "1. Add a new expense" << endl;
    cout << "2. Add a new income" << endl;
    cout << "3. Add a new recurring cost" << endl;
    cout << "4. List all recurring costs" << endl;
    cout << "5. List all income sources" << endl;
    cout << "6. Edit values" << endl;
    cout << "7. Delete values" << endl;
    cout << "8. Display a quick view" << endl;
    cout << "9. Display a detailed view" << endl;
    cout << "10. Show net income in a specified date range" << endl;
    cout << "11. Save your current session's data" << endl;

}

string getMonthName(int num) // takes a number from 1 to 12 and returns the month corresponding to the number
{
    string monthsArray[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (num < 1  || num > 12) {
        return "Fatal error in getMonthName function";
    }

    return monthsArray[num - 1];
}

void takeInput(vector<Data> &vec, int size, const string& s){ // takes input and adds it into a vector taking the size of input
    while(size--)
    {
        string IncomeName;
        float IncomeAmount;
        cout << "enter name of " << s <<  endl;
        cin >> IncomeName;
        cout << "enter the amount of " <<  IncomeName << endl;
        cin >> IncomeAmount;

        Data income;
        income.name = IncomeName;
        income.amount = IncomeAmount;
        income.date = time(nullptr);

        vec.push_back(income);
    }
}

void listOptions(const string& s) // lists vector options
{
    cout << "Please choose the list you want to " << s << endl;
    cout<<"1. " << s << " Expenses \n"
        <<"2. " << s << " income \n"
        << "3. "<< s << " recurring costs \n";
}


int getSelectedOption(const string& s) // take name of option of the list and makes a validation check
{
    int option;
    listOptions(s);
    cin >> option;
    while(option != 1 && option != 2 && option != 3){
        cout << "oops you entered an invalid getSelectedOption, try once more!" << endl;
        listOptions(s);
        cin >> option;
    }
    return option;
}

void listVector(vector<Data> vec) // takes a vector and returns its values
{
    for (int i = 0; i < vec.size(); ++i) {
        string month;

        tm *ltm = localtime(&vec[i].date);
        month = getMonthName(1 + ltm->tm_mon);
        cout << i+1 << ". " << vec[i].name << ": " << vec[i].amount << "( ";
        cout <<  ltm->tm_mday << " " << month << " " << 1900 + ltm->tm_year << " )"<< endl;
    }
}

double getDataTotalAmount(const vector<Data>& vec) // Calculate the total amount in a given vector
{
    double sum = 0;
    for (auto & i : vec) {
        sum += i.amount;
    }
    return sum;
}

void quickView() // Outputs a quick view of all lists
{
    double totalIncome = getDataTotalAmount(incomes);
    double totalExpenses = getDataTotalAmount(expenses);
    double totalReccuringCosts = getDataTotalAmount(recurringCost);

    cout << "Total Income " << totalIncome << endl;
    cout << "Total expenses " << totalExpenses << endl;
    cout << "Total recurring costs " << totalReccuringCosts << endl;
    cout <<"\n\nnet budget: " << totalIncome - totalExpenses - totalReccuringCosts << endl;
}

void editValue(vector<Data> &vec) // User enters list and number of item he wants to edit and edits the value
{
    int number;
    double newValue;
    cout << "enter the number of item you want to edit" << endl;
    listVector(vec);
    cin >> number;
    while(!(number>0 && number <= vec.size()) ) {
        cout << "oops you entered an invalid getSelectedOption, try once more!" << endl;
        listVector(vec);
        cin >> number;
    }

    number--;

    cout<<"Enter new Amount instead of " << vec[number].amount << endl;
    cin >> newValue;
    vec[number].amount = newValue;

}

void detailedView() { // outputs a detailed view of all lists
    double totalIncome = getDataTotalAmount(incomes);
    double totalExpenses = getDataTotalAmount(expenses);
    double totalReccuringCosts = getDataTotalAmount(recurringCost);

    cout << "Income:" << endl;
    listVector(incomes);
    cout << "\nTotal Income " << totalIncome << endl;
    cout << "Expenses:" << endl;
    listVector(expenses);
    cout << "\nTotal expenses " << totalExpenses << endl;
    cout << "Recurring costs" << endl;
    listVector(recurringCost);
    cout << "\nTotal recurring costs " << totalReccuringCosts << endl;

    cout <<"\n\n net budget: " << totalIncome - totalExpenses - totalReccuringCosts << "\n\n";
}

void listMonths(int startMonth) // lists all months starting from month ( startMonth )
{
    string month;

    for (int i = startMonth; i <= 12 ; ++i) {
        month = getMonthName(i);
        cout << i << ". " << month << endl;
    }
}

int startMonth() // takes the starting month from the user and returns it
{
    int start;
    cout<<"Choose the month you want your interval to start from"<<endl;
    listMonths(1);
    cin >> start;
    while(!(start > 0 && start <= 12)){
        cout << "oops you entered an invalid getSelectedOption, try once more!" << endl;
        listMonths(1);
        cin >> start;
    }
    return start;
}

int endMonth(int start) // lists months and take end month from user and returns it
{
    int end;
    cout<<"Choose the month you want your interval to end at "<<endl;
    listMonths(start + 1);
    cin >> end;
    while(!(end > start && end <= 12)){
        cout << "oops you entered an invalid getSelectedOption, try once more!" << endl;
        listMonths(start + 1);
        cin >> end;
    }
    return end;
}

double budgetDifferanceInAnInterval(int start, int end)
{
    double totalIncome = getDataTotalAmount(incomes);
    double totalExpenses = getDataTotalAmount(expenses);
    double original = getDataTotalAmount(recurringCost);
    double totalRecurring = 0;
    for (int i = start; i <= end ; ++i) {
        totalRecurring += original;
    }

    return (totalIncome - totalExpenses - totalRecurring);
}

void deleteValue (vector<Data> &vec) { //user enters list and number of item he wants to delete
    int number;
    cout << "enter the number of item you want to delete" << endl;
    listVector(vec);
    cin >> number;
    while (!(number > 0 && number <= vec.size())) {
        cout << "oops you entered an invalid getSelectedOption, try once more!" << endl;
        listVector(vec);
        cin >> number;
    }

    number--;

    vec.erase(vec.begin() + number);
}

int readUserDesiredInputsCount(const string& s) // asks the user how many inputs he wants to enter
{
    int input = -1;
    bool valid= false;
    do
    {
        cout << "Please enter number of " << s <<" you want to add" << flush;
        cin >> input;
        if (cin.good())
        {
            //everything went well, we'll get out of the loop and return the value
            valid = true;
        }
        else
        {
            //something went wrong, we reset the buffer's state to good
            cin.clear();
            //and empty it
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input; please re-enter." << endl;
        }
    } while (!valid);

    return (input);
}

void initSavedObjects() {
    if (isFileExist(expensesSaveFilePath)) {
        cout << "found saved expenses \n";

        expenses = readSaveFile((string&) expensesSaveFilePath);
        cout << "expenses read successfully \n";

        cout << "\n";
    }

    if (isFileExist(recurringCostsSaveFilePath)) {
        cout << "found saved recurring costs \n";

        recurringCost = readSaveFile((string&) recurringCostsSaveFilePath);
        cout << "recurring costs read successfully \n";

        cout << "\n";

    }

    if (isFileExist(incomesSaveFilePath)) {
        cout << "found saved incomes \n";
        incomes = readSaveFile((string&) incomesSaveFilePath);

        cout << "incomes read successfully \n";

        cout << "\n";

    }

    cout << "\n";
}

int main() {
    int option; // holds the option that the user chooses
    int size; // holds the size user want to enter for expenses or incomes

    initSavedObjects();

    do {
        displayMainMenu();
        cout << "Please enter a valid option from the list ( -1 to quit )" << endl;
        cin >> option;
        switch (option) {
            case 1: {
                size = readUserDesiredInputsCount("expenses");
                takeInput(expenses, size, "expense");
                break;
            }
            case 2: {
                size = readUserDesiredInputsCount("income");
                takeInput(incomes, size, "income");
                break;
            }
            case 3: {
                size = readUserDesiredInputsCount("recurring costs");
                takeInput(recurringCost, size, "recurring costs");
                break;
            }
            case 4: {
                listVector(recurringCost);
                cout << endl;
                break;
            }
            case 5: {
                listVector(incomes);
                cout << endl;
                break;
            }
            case 6: {
                int number = getSelectedOption("edit");
                switch (number) {
                    case 1 : {
                        editValue(expenses);
                        break;
                    }
                    case 2: {
                        editValue(incomes);
                        break;
                    }
                    case 3: {
                        editValue(recurringCost);
                        break;
                    }
                    default: {
                        cout << "Fatal error in case 6 ( main function )" << endl;
                    }
                }
                break;
            }
            case 7: {
                switch (getSelectedOption("delete")) {
                    case 1:{
                        deleteValue(expenses);
                        break;
                    }
                    case 2:
                    {
                        deleteValue(incomes);
                        break;
                    }
                    case 3: {
                        deleteValue(recurringCost);
                        break;
                    }
                }

                break;
            }
            case 8: {
                quickView();
                break;
            }
            case 9: {

                detailedView();
                break;
            }
            case 10: {
                int start = startMonth();
                string startMonthString;
                int end = endMonth(start);
                string endMonthString;
                double total = budgetDifferanceInAnInterval(start, end);

                startMonthString = getMonthName(start);
                endMonthString = getMonthName(end);

                cout << "total difference between " << startMonthString << " and " << endMonthString << " = "<< total << endl;
                break;
            }
            case 11: {
                if(writeSaveFile(expenses, (string &) expensesSaveFilePath)) {
                    cout << "expenses saved successfully \n";
                }
                if(writeSaveFile(incomes, (string &) incomesSaveFilePath)) {
                    cout << "incomes saved successfully \n";
                }
                if(writeSaveFile(recurringCost, (string &) recurringCostsSaveFilePath)) {
                    cout << "recurring costs saved successfully \n";
                }
            }
            case -1: {
                break;
            }
            default: {
                cout << "oops you entered an invalid option, try once more!" << endl;
                break;
            }
        }
    } while(option != -1);
}

