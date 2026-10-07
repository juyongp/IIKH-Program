// Utility.h
// Helper functions shared by all components
//   - safe console input (the user is asked again until the input is valid)
//   - text helpers
//   - printing of grocery lists and recipe lists

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"

// input 
int readInt(const std::string& prompt, int min, int max);   // integer in [min, max]
double readDouble(const std::string& prompt);               // number greater than 0
std::string readLine(const std::string& prompt);            // one line, leading/trailing spaces removed
bool readYesNo(const std::string& prompt);                  // true for "y"/"yes", false for "n"/"no"

// text 
std::string toLower(const std::string& text);               // lowercase copy

// grocery list
// adds an item; if the same name and unit is already there, adds the amounts
void addToGroceryList(std::vector<Ingredient>& list, const Ingredient& item);
void printIngredientList(const std::vector<Ingredient>& list);   // print as a checklist

// recipe list
void printRecipeList(const std::vector<Recipe>& list);   // numbered list of names, preparation times and calories
void viewRecipe(const Recipe& recipe);                    // ask the number of people and print the scaled recipe

#endif
