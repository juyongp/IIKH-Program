// Ingredient.h
// One ingredient of a recipe (example: "2 cup rice").

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    std::string name;    // ingredient name (ex: "rice")
    double amount;       // quantity (ex: 2)
    std::string unit;    // unit (ex: "cup", "g", "tbsp")

public:
    Ingredient();
    Ingredient(const std::string& name, double amount, const std::string& unit);

    // getters
    std::string getName() const;
    double getAmount() const;
    std::string getUnit() const;

    // setter (used when a recipe is scaled)
    void setAmount(double amount);

    // print this ingredient on the screen (ex: "2 cup rice")
    void display() const;
};

#endif
