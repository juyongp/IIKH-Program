// Meal.h
// Meal component
// Responsibilities:
//   - holds information about a single meal
//   - lets the user select recipes from the recipe database
//   - user sets the number of people, and recipes are scaled automatically
//   - produces a grocery list for the meal by combining the
//     scaled ingredients of its recipes

#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <vector>
#include "Recipe.h"
#include "Ingredient.h"
#include "RecipeDatabase.h"

class Meal {
private:
    std::string mealType;          // "Breakfast", "Lunch" or "Dinner"
    int numberOfPeople;            // people at this meal
    std::vector<Recipe> recipes;   // recipes of this meal

public:
    Meal();
    Meal(const std::string& mealType, int numberOfPeople);

    // getters / setters
    std::string getMealType() const;
    int getNumberOfPeople() const;
    void setNumberOfPeople(int numberOfPeople);   // recipes are scaled to this number

    // add / remove recipes
    void addRecipe(const Recipe& recipe);
    bool removeRecipe(const std::string& recipeName);   // false if not found
    void selectRecipe(RecipeDatabase& database);        // browse the database and add the chosen recipe

    // grocery list for this meal
    std::vector<Ingredient> makeGroceryList() const;

    void edit(RecipeDatabase& database);   // let the user add/remove recipes or change the number of people
    void display() const;                  // show meal type, people and recipe names
    void print() const;                    // print all recipes of this meal
};

#endif
