// RecipeDatabase.h
// Recipe Database component
// Responsibilities (Lecture 3, "The Recipe Database Component"):
//   - maintains the database of recipes
//   - allows the user to browse the database
//   - permits the user to edit or annotate an existing recipe
//   - permits the user to add a new recipe
// Also supports the required operations of this assignment:
//   insertion, search and sorting of recipes.

#ifndef RECIPEDATABASE_H
#define RECIPEDATABASE_H

#include <string>
#include <vector>
#include "Recipe.h"

class RecipeDatabase {
private:
    std::vector<Recipe> recipes;   // all recipes

public:
    RecipeDatabase();

    // ----- insertion -----
    bool addRecipe(const Recipe& recipe);   // false if a recipe with the same name exists
    void addNewRecipe();                    // ask the user for a new recipe and add it
    bool deleteRecipe(const std::string& name);

    // ----- search -----
    Recipe* findRecipe(const std::string& name);   // exact name, nullptr if not found
    std::vector<Recipe> searchByName(const std::string& keyword) const;         // name contains keyword
    std::vector<Recipe> searchByIngredient(const std::string& ingredient) const; // recipes using the ingredient

    // ----- sorting -----
    void sortByName();          // alphabetical order
    void sortByPreparationTime();   // shortest preparation time first

    // ----- user interaction -----
    void browse();              // show recipes and let the user look at them
    void editRecipe();          // let the user choose a recipe and edit/annotate it
    Recipe* selectRecipe();     // let the user choose one recipe (used by editRecipe), nullptr if canceled
    void displayAll() const;    // show the list of all recipes
};

#endif
