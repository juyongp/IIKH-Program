// Recipe.h
// Recipe component
// Responsibilities (Lecture 3, "Responsibilities of a Recipe"):
//   - maintains the list of ingredients and the cooking steps
//   - knows how to edit these data values
//   - knows how to display itself on the screen
//   - knows how to print itself
//   - can scale itself for a given number of people

#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Recipe {
private:
    std::string name;                     // recipe name (ex: "Salmon with dill")
    int servings;                         // number of people this recipe is written for
    int preparationTime;                      // expected preparation time in minutes (for the original servings)
    std::vector<Ingredient> ingredients;  // list of ingredients
    std::vector<std::string> steps;       // cooking steps in order
    std::string annotation;               // user's note about the recipe

public:
    Recipe();
    Recipe(const std::string& name, int servings, int preparationTime);

    // getters
    std::string getName() const;
    int getServings() const;
    int getPreparationTime() const;

    // setters
    void setName(const std::string& name);
    void setServings(int servings);
    void setPreparationTime(int preparationTime);
    void setAnnotation(const std::string& annotation);   // annotate the recipe

    // edit the ingredient list and the steps
    void addIngredient(const Ingredient& ingredient);
    bool removeIngredient(const std::string& ingredientName);  // false if not found
    void addStep(const std::string& step);

    // true if this recipe uses the given ingredient (used for search)
    bool hasIngredient(const std::string& ingredientName) const;

    // ingredient list scaled for 'people' persons
    // (ex: recipe for 2, people = 4  ->  every amount x2)
    std::vector<Ingredient> getScaledIngredients(int people) const;

    void edit();                    // let the user change the data values
    void display() const;           // show the whole recipe on the screen
    void print(int people) const;   // print the recipe scaled for 'people' persons
};

#endif
