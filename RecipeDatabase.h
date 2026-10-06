// RecipeDatabase.h

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
    bool addRecipe(const Recipe& recipe);  
    void addNewRecipe();              
    bool deleteRecipe(const std::string& name);

    // ----- search -----
    Recipe* findRecipe(const std::string& name);   
    std::vector<Recipe> searchByName(const std::string& keyword) const;     
    std::vector<Recipe> searchByIngredient(const std::string& ingredient) const; 

    // ----- sorting -----
    void sortByName();          // alphabetical order
    void sortByPreparationTime();   // shortest preparation time first

    // ----- user interaction -----
    void browse();              
    void editRecipe();          
    Recipe* selectRecipe();     
    void displayAll() const;    
};

#endif
