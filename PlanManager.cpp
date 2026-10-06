// PlanManager.cpp

#include "PlanManager.h"
#include "Utility.h"
#include <iostream>
using namespace std;

static bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int daysInMonth(int year, int month) {
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

// moves the given date to the next day
static void nextDay(int& year, int& month, int& day) {
    day++;
    if (day > daysInMonth(year, month)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

PlanManager::PlanManager() {
}

void PlanManager::createPlan() {
    cout << endl << "--- Create a new plan ---" << endl;
    if (!dates.empty()) {
        if (!readYesNo("A plan already exists. Replace it with a new plan?")) {
            return;
        }
        dates.clear();
    }

    int year = readInt("Start year (2000-2100): ", 2000, 2100);
    int month = readInt("Start month (1-12): ", 1, 12);
    int lastDay = daysInMonth(year, month);
    int day = readInt("Start day (1-" + to_string(lastDay) + "): ", 1, lastDay);
    int numberOfDays = readInt("Number of days to plan (1-14): ", 1, 14);

    for (int i = 0; i < numberOfDays; i++) {
        addDate(Date(year, month, day));
        nextDay(year, month, day);
    }
    cout << "A plan for " << numberOfDays << " day(s) was created: "
         << dates.front().toString() << " ~ " << dates.back().toString() << endl;
}

void PlanManager::editPlan(RecipeDatabase& database) {
    if (dates.empty()) {
        cout << "There is no plan yet. Create a plan first." << endl;
        return;
    }
    while (true) {
        cout << endl << "--- Plan: " << dates.front().toString()
             << " ~ " << dates.back().toString() << " ---" << endl;
        cout << "  1. Show the whole plan" << endl;
        cout << "  2. Edit a date" << endl;
        cout << "  3. Show the grocery list for the whole plan" << endl;
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
    if (dates.empty()) {
        cout << "There is no plan yet." << endl;
        return;
    }
    cout << endl;
    for (size_t i = 0; i < dates.size(); i++) {
        dates[i].display();
    }
}

void PlanManager::printGroceryList() const {
    if (dates.empty()) {
        cout << "There is no plan yet." << endl;
        return;
    }
    vector<Ingredient> list;
    for (size_t i = 0; i < dates.size(); i++) {
        vector<Ingredient> dayList = dates[i].makeGroceryList();
        for (size_t j = 0; j < dayList.size(); j++) {
            addToGroceryList(list, dayList[j]);
        }
    }
    cout << endl << "===== Grocery list: " << dates.front().toString()
         << " ~ " << dates.back().toString() << " =====" << endl;
    printIngredientList(list);
}

bool PlanManager::isEmpty() const {
    return dates.empty();
}
