// Recipe.h

#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "Ingredient.h"

class Recipe {
private:
    std::string name;                     
    int servings;                         
    int preparationTime;                      
    std::vector<Ingredient> ingredients;  
    std::vector<std::string> steps;       
    std::string annotation;        

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
    void setAnnotation(const std::string& annotation);   

 
    void addIngredient(const Ingredient& ingredient);
    bool removeIngredient(const std::string& ingredientName);  
    void addStep(const std::string& step);


    bool hasIngredient(const std::string& ingredientName) const;


    std::vector<Ingredient> getScaledIngredients(int people) const;

    void edit();                   
    void display() const;          
    void print(int people) const;   
};

#endif
