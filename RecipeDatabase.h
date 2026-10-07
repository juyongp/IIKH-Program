// RecipeDatabase.h
// Recipe Database component
// Responsibilities:
//   - maintains the collection of all recipes
//   - permits the user to browse the recipes
//   - permits the user to add new recipes
//   - permits the user to edit or annotate existing recipes
//   - searches recipes by name or by ingredient, and sorts them

#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H

#include <string>
#include <vector>
#include "Recipe.h"

class RecipeDatabase {
private:
    std::vector<Recipe> recipes;

public:
    RecipeDatabase();

    // insertion / deletion
    bool addRecipe(const Recipe& recipe);          // false if the name is empty or already used
    void addNewRecipe();                           // ask the user for a new recipe and add it
    bool deleteRecipe(const std::string& name);    // false if not found

    // search
    Recipe* findRecipe(const std::string& name);   // exact name, nullptr if not found
    std::vector<Recipe> searchByName(const std::string& keyword) const;          // names containing the keyword
    std::vector<Recipe> searchByIngredient(const std::string& ingredient) const; // recipes that use the ingredient
    std::vector<Recipe> getAllRecipes() const;     // copy of every recipe

    // sorting
    void sortByName();              // alphabetical order
    void sortByPreparationTime();   // shortest preparation time first

    // user interaction
    void browse();                  // list all recipes and let the user view one
    void editRecipe();              // let the user choose a recipe, then edit/annotate or delete it
    Recipe* selectRecipe();         // let the user choose a recipe (list or search), nullptr if cancelled
    void displayAll() const;        // print the names and preparation times of all recipes
};

#endif
