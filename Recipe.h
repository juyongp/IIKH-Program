// Recipe.h
// Recipe component
// Responsibilities:
//   - holds the information of one recipe: name, servings, preparation time,
//     ingredients, cooking steps and a user note
//   - lets the user edit or annotate the recipe
//   - scales the ingredients to any number of people
//   - prints the recipe scaled for the user

#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Recipe {
private:
    std::string name;                      // name of the dish, unique in the database
    int servings;                          // number of people the original recipe serves (> 0)
    int preparationTime;                   // expected preparation time in minutes (>= 0)
    std::vector<Ingredient> ingredients;   // ingredients for the original servings
    std::vector<std::string> steps;        // cooking steps in order
    std::string annotation;                // user note about the recipe (empty if none)

public:
    Recipe();
    Recipe(const std::string& name, int servings, int preparationTime);

    // getters
    std::string getName() const;
    int getServings() const;
    int getPreparationTime() const;

    // setters (invalid values are ignored)
    void setName(const std::string& name);
    void setServings(int servings);
    void setPreparationTime(int preparationTime);
    void setAnnotation(const std::string& annotation);   // empty string clears the note

    // ingredients and steps
    void addIngredient(const Ingredient& ingredient);
    bool removeIngredient(const std::string& ingredientName);   // false if not found
    void addStep(const std::string& step);

    // true if an ingredient name contains the given text,
    // used by RecipeDatabase::searchByIngredient
    bool hasIngredient(const std::string& ingredientName) const;

    // ingredients scaled from the original servings to the given number of people
    std::vector<Ingredient> getScaledIngredients(int people) const;

    void edit();                   // let the user change the name, servings, time, ingredients, steps or note
    void display() const;          // print the recipe for the original servings
    void print(int people) const;  // print the recipe scaled to the given number of people
};

#endif
