// Date.h
// Date component
// Responsibilities:
//   - holds the meals planned for one day
//   - user can edit specific meals
//   - user can annotate information about the date 
//   - can print out the grocery list for all meals of the day

#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include "Meal.h"
#include "Ingredient.h"
#include "RecipeDatabase.h"

class Date {
private:
    int year;
    int month;
    int day;
    std::vector<Meal> meals;               // meals planned for this day
    std::vector<std::string> annotations;  // notes about this day

    int chooseMeal() const;   // let the user pick a meal, -1 if cancelled or there are none

public:
    Date();
    Date(int year, int month, int day);   // an invalid date becomes 2000-01-01

    static bool isValid(int year, int month, int day);
    static int daysInMonth(int year, int month);

    // getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    std::string toString() const;   // ex: "2026-09-23"
    Date nextDay() const;           // the following day (with no meals or notes)

    // meals
    void addMeal(const Meal& meal);            // kept in breakfast, lunch, dinner order
    void editMeal(RecipeDatabase& database);   // let the user choose a meal and edit it

    // annotations
    void addAnnotation(const std::string& note);

    // grocery list for all meals of this day
    std::vector<Ingredient> makeGroceryList() const;
    void printGroceryList() const;

    void edit(RecipeDatabase& database);   // let the user add a meal, edit a meal or add a note
    void display() const;                  // show the date, notes and meals
};

#endif
