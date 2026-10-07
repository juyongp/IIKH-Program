// Date.cpp

#include "Date.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

static const string MEAL_TYPES[] = { "Breakfast", "Lunch", "Dinner" };

// position of a meal type in a day (unknown types go last)
static int mealOrder(const string& mealType) {
    for (int i = 0; i < 3; i++) {
        if (MEAL_TYPES[i] == mealType) {
            return i;
        }
    }
    return 3;
}

static bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

Date::Date() {
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(int year, int month, int day) {
    if (isValid(year, month, day)) {
        this->year = year;
        this->month = month;
        this->day = day;
    } else {
        this->year = 2000;
        this->month = 1;
        this->day = 1;
    }
}

bool Date::isValid(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12) {
        return false;
    }
    return day >= 1 && day <= daysInMonth(year, month);
}

int Date::daysInMonth(int year, int month) {
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

string Date::toString() const {
    ostringstream out;
    out << setfill('0') << setw(4) << year << "-" << setw(2) << month << "-" << setw(2) << day;
    return out.str();
}

Date Date::nextDay() const {
    int y = year;
    int m = month;
    int d = day + 1;
    if (d > daysInMonth(y, m)) {
        d = 1;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }
    return Date(y, m, d);
}

void Date::addMeal(const Meal& meal) {
    size_t position = 0;
    while (position < meals.size() && mealOrder(meals[position].getMealType()) <= mealOrder(meal.getMealType())) {
        position++;
    }
    meals.insert(meals.begin() + position, meal);
}

int Date::chooseMeal() const {
    if (meals.empty()) {
        cout << "No meals are planned for " << toString() << "." << endl;
        return -1;
    }
    for (size_t i = 0; i < meals.size(); i++) {
        cout << "  " << (i + 1) << ". ";
        meals[i].display();
    }
    int number = readInt("Meal number (0 = cancel): ", 0, (int)meals.size());
    return number - 1;
}

void Date::editMeal(RecipeDatabase& database) {
    int index = chooseMeal();
    if (index >= 0) {
        meals[index].edit(database);
    }
}

void Date::addAnnotation(const string& note) {
    if (note != "") {
        annotations.push_back(note);
    }
}

vector<Ingredient> Date::makeGroceryList() const {
    vector<Ingredient> list;
    for (size_t i = 0; i < meals.size(); i++) {
        vector<Ingredient> mealList = meals[i].makeGroceryList();
        for (size_t j = 0; j < mealList.size(); j++) {
            addToGroceryList(list, mealList[j]);
        }
    }
    return list;
}

void Date::printGroceryList() const {
    cout << "Grocery list for " << toString() << ":" << endl;
    printIngredientList(makeGroceryList());
}

void Date::edit(RecipeDatabase& database) {
    while (true) {
        cout << endl;
        display();
        cout << "--- Edit " << toString() << " ---" << endl;
        cout << "  1. Add a meal" << endl;
        cout << "  2. Edit a meal" << endl;
        cout << "  3. Remove a meal" << endl;
        cout << "  4. Add a note (ex: Bob's birthday)" << endl;
        cout << "  5. Print the recipes for this day" << endl;
        cout << "  6. Show the grocery list for this day" << endl;
        cout << "  0. Done" << endl;
        int choice = readInt("Select: ", 0, 6);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            cout << "  1. Breakfast" << endl;
            cout << "  2. Lunch" << endl;
            cout << "  3. Dinner" << endl;
            int type = readInt("Meal type (0 = cancel): ", 0, 3);
            if (type > 0) {
                int people = readInt("Number of people: ", 1, 100);
                Meal meal(MEAL_TYPES[type - 1], people);
                meal.edit(database);   // choose the recipes of the new meal
                addMeal(meal);
            }
        }
        else if (choice == 2) {
            editMeal(database);
        }
        else if (choice == 3) {
            int index = chooseMeal();
            if (index >= 0) {
                meals.erase(meals.begin() + index);
                cout << "Meal removed." << endl;
            }
        }
        else if (choice == 4) {
            addAnnotation(readLine("Note: "));
        }
        else if (choice == 5) {
            if (meals.empty()) {
                cout << "No meals are planned for " << toString() << "." << endl;
            }
            for (size_t i = 0; i < meals.size(); i++) {
                cout << endl << "##### " << meals[i].getMealType() << " #####" << endl;
                meals[i].print();
            }
        }
        else if (choice == 6) {
            printGroceryList();
        }
    }
}

void Date::display() const {
    cout << "===== " << toString() << " =====" << endl;
    for (size_t i = 0; i < annotations.size(); i++) {
        cout << "  Note: " << annotations[i] << endl;
    }
    if (meals.empty()) {
        cout << "  (no meals planned)" << endl;
    }
    for (size_t i = 0; i < meals.size(); i++) {
        cout << "  ";
        meals[i].display();
    }
}
