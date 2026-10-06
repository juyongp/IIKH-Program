// Ingredient.h


#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    std::string name;    
    double amount;       
    std::string unit;

public:
    Ingredient();
    Ingredient(const std::string& name, double amount, const std::string& unit);

    // getters
    std::string getName() const;
    double getAmount() const;
    std::string getUnit() const;

    // setter 
    void setAmount(double amount);

    // print ingredient
    void display() const;
};

#endif
