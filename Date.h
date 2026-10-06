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

public:
    Date();
    Date(int year, int month, int day);

    // getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    std::string toString() const;   // ex: "2026-09-23"

    // meals
    void addMeal(const Meal& meal);
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
