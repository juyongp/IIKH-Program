// Utility.h


#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "Recipe.h"


int readInt(const std::string& prompt, int min, int max);   
double readDouble(const std::string& prompt);              
std::string readLine(const std::string& prompt);           
bool readYesNo(const std::string& prompt);                

// ----- text -----
std::string toLower(const std::string& text);               

// ----- recipe list -----
void printRecipeList(const std::vector<Recipe>& list);  
void viewRecipe(const Recipe& recipe);                   

#endif
