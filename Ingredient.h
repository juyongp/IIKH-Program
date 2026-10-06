// Ingredient.h
// Ingredient
// Responsibilities:
//   - holds one ingredient of a recipe (name, amount and unit)
//   - the amount can be changed so that a recipe can be scaled to a different number of people
//   - also used as one item of a grocery list

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    std::string name;   
    double amount;      // quantity in the given unit
    std::string unit;   // ex: "g", "cup", "tbsp" (empty if there is no unit, ex: 2 eggs)

public:
    Ingredient();
    Ingredient(const std::string& name, double amount, const std::string& unit);

    // getters
    std::string getName() const;
    double getAmount() const;
    std::string getUnit() const;

    // setter (used when scaling a recipe or merging grocery list items)
    void setAmount(double amount);

    // print the ingredient in one line
    void display() const;
};

#endif
