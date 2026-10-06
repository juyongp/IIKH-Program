// Utility.h


#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"


int readInt(const std::string& prompt, int min, int max);   
double readDouble(const std::string& prompt);              
std::string readLine(const std::string& prompt);           
bool readYesNo(const std::string& prompt);                

// ----- text -----
std::string toLower(const std::string& text);               

// ----- grocery list -----
// adds an item; if the same item (same name and unit) is already there, adds the amounts
void addToGroceryList(std::vector<Ingredient>& list, const Ingredient& item);
void printIngredientList(const std::vector<Ingredient>& list);

// ----- recipe list -----
void printRecipeList(const std::vector<Recipe>& list);  
void viewRecipe(const Recipe& recipe);                   

#endif
