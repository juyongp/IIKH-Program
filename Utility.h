// Utility.h
// Small helper functions used by several classes:
// keyboard input, text, grocery list and recipe list printing.

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"

// ----- keyboard input -----
// Each function repeats the question until the answer is valid.
int readInt(const std::string& prompt, int min, int max);   // number in [min, max] (returns min if input ends)
double readDouble(const std::string& prompt);               // number greater than 0
std::string readLine(const std::string& prompt);            // one line of text (may be empty)
bool readYesNo(const std::string& prompt);                  // y -> true, n -> false

// ----- text -----
std::string toLower(const std::string& text);               // "Salmon" -> "salmon"

// ----- grocery list -----
// adds an item; if the same item (same name and unit) is already there, adds the amounts
void addToGroceryList(std::vector<Ingredient>& list, const Ingredient& item);
void printIngredientList(const std::vector<Ingredient>& list);

// ----- recipe list -----
void printRecipeList(const std::vector<Recipe>& list);   // "1. Salmon with dill  (25 min, 2 servings)"
void viewRecipe(const Recipe& recipe);                    // show a recipe, then offer to print it

#endif
