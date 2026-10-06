// Date.cpp

#include "Date.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Date::Date() {
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

string Date::toString() const {
    stringstream ss;
    ss << year << "-" << setw(2) << setfill('0') << month
       << "-" << setw(2) << setfill('0') << day;
    return ss.str();
}

void Date::addMeal(const Meal& meal) {
    meals.push_back(meal);
}

void Date::editMeal(RecipeDatabase& database) {
    if (meals.empty()) {
        cout << "No meals are planned for this day." << endl;
        return;
    }
    for (size_t i = 0; i < meals.size(); i++) {
        cout << "  " << (i + 1) << ". " << meals[i].getMealType()
             << " (" << meals[i].getNumberOfPeople()
             << (meals[i].getNumberOfPeople() == 1 ? " person)" : " people)") << endl;
    }
    int number = readInt("Meal number to edit (0 = cancel): ", 0, (int)meals.size());
    if (number > 0) {
        meals[number - 1].edit(database);
    }
}

void Date::addAnnotation(const string& note) {
    annotations.push_back(note);
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
    cout << "===== Grocery list for " << toString() << " =====" << endl;
    printIngredientList(makeGroceryList());
}

void Date::edit(RecipeDatabase& database) {
    while (true) {
        cout << endl;
        display();
        cout << "--- Edit " << toString() << " ---" << endl;
        cout << "  1. Add a meal" << endl;
        cout << "  2. Edit a meal" << endl;
        cout << "  3. Add a note (ex: Bob's Birthday)" << endl;
        cout << "  4. Show the grocery list for this day" << endl;
        cout << "  0. Back" << endl;
        int choice = readInt("Select: ", 0, 4);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            cout << "  1. Breakfast  2. Lunch  3. Dinner  0. Cancel" << endl;
            int type = readInt("Meal type: ", 0, 3);
            if (type == 0) {
                continue;
            }
            string typeName = (type == 1) ? "Breakfast" : (type == 2) ? "Lunch" : "Dinner";

            bool exists = false;
            for (size_t i = 0; i < meals.size(); i++) {
                if (meals[i].getMealType() == typeName) {
                    exists = true;
                }
            }
            if (exists) {
                cout << typeName << " is already planned. Use \"Edit a meal\"." << endl;
                continue;
            }

            int people = readInt("Number of people: ", 1, 100);
            addMeal(Meal(typeName, people));
            cout << typeName << " was added." << endl;
            if (readYesNo("Add recipes to this meal now?")) {
                meals.back().edit(database);
            }
        }
        else if (choice == 2) {
            editMeal(database);
        }
        else if (choice == 3) {
            string note = readLine("Note: ");
            if (note != "") {
                addAnnotation(note);
            }
        }
        else if (choice == 4) {
            printGroceryList();
        }
    }
}

void Date::display() const {
    cout << "===== " << toString() << " =====" << endl;
    for (size_t i = 0; i < annotations.size(); i++) {
        cout << "  * " << annotations[i] << endl;
    }
    if (meals.empty()) {
        cout << "  (no meals planned)" << endl;
    }
    for (size_t i = 0; i < meals.size(); i++) {
        cout << "  ";
        meals[i].display();
    }
}
