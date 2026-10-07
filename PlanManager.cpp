// PlanManager.cpp

#include "PlanManager.h"
#include "Utility.h"
#include <iostream>
using namespace std;

void PlanManager::createPlan() {
    cout << endl << "--- Create a new meal plan ---" << endl;
    if (!isEmpty() && !readYesNo("This will replace the current plan. Continue?")) {
        return;
    }
    int year = readInt("Start year: ", 2000, 2100);
    int month = readInt("Start month: ", 1, 12);
    int day = readInt("Start day: ", 1, Date::daysInMonth(year, month));
    int numberOfDays = readInt("Number of days to plan (1-31, 7 = a week): ", 1, 31);

    dates.clear();
    Date date(year, month, day);
    for (int i = 0; i < numberOfDays; i++) {
        addDate(date);
        date = date.nextDay();
    }
    cout << "A plan from " << dates.front().toString() << " to "
         << dates.back().toString() << " was created." << endl;
}

void PlanManager::editPlan(RecipeDatabase& database) {
    if (isEmpty()) {
        cout << "There is no meal plan yet. Please create one first." << endl;
        return;
    }
    while (true) {
        cout << endl << "--- Meal plan (" << dates.front().toString() << " ~ "
             << dates.back().toString() << ") ---" << endl;
        cout << "  1. Show the menus for the whole period" << endl;
        cout << "  2. Edit a date (meals and notes)" << endl;
        cout << "  3. Print the grocery list for the whole period" << endl;
        cout << "  0. Back" << endl;
        int choice = readInt("Select: ", 0, 3);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            displayPlan();
        }
        else if (choice == 2) {
            for (size_t i = 0; i < dates.size(); i++) {
                cout << "  " << (i + 1) << ". " << dates[i].toString() << endl;
            }
            int number = readInt("Date number (0 = cancel): ", 0, (int)dates.size());
            if (number > 0) {
                dates[number - 1].edit(database);
            }
        }
        else if (choice == 3) {
            printGroceryList();
        }
    }
}

void PlanManager::addDate(const Date& date) {
    if (findDate(date.getYear(), date.getMonth(), date.getDay()) == nullptr) {
        dates.push_back(date);
    }
}

Date* PlanManager::findDate(int year, int month, int day) {
    for (size_t i = 0; i < dates.size(); i++) {
        if (dates[i].getYear() == year && dates[i].getMonth() == month && dates[i].getDay() == day) {
            return &dates[i];
        }
    }
    return nullptr;
}

void PlanManager::displayPlan() const {
    if (isEmpty()) {
        cout << "There is no meal plan yet." << endl;
        return;
    }
    for (size_t i = 0; i < dates.size(); i++) {
        cout << endl;
        dates[i].display();
    }
}

void PlanManager::printGroceryList() const {
    vector<Ingredient> list;
    for (size_t i = 0; i < dates.size(); i++) {
        vector<Ingredient> dateList = dates[i].makeGroceryList();
        for (size_t j = 0; j < dateList.size(); j++) {
            addToGroceryList(list, dateList[j]);
        }
    }
    cout << "Grocery list for the whole period:" << endl;
    printIngredientList(list);
}

bool PlanManager::isEmpty() const {
    return dates.empty();
}
