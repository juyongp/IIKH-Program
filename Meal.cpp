// Meal.cpp

#include "Meal.h"
#include "Utility.h"
#include <iostream>
using namespace std;

Meal::Meal() {
    mealType = "Dinner";
    numberOfPeople = 1;
}

Meal::Meal(const string& mealType, int numberOfPeople) {
    this->mealType = mealType;
    this->numberOfPeople = (numberOfPeople > 0) ? numberOfPeople : 1;
}

string Meal::getMealType() const { return mealType; }
int Meal::getNumberOfPeople() const { return numberOfPeople; }

void Meal::setNumberOfPeople(int numberOfPeople) {
    if (numberOfPeople > 0) {
        this->numberOfPeople = numberOfPeople;
    }
}

void Meal::addRecipe(const Recipe& recipe) {
    for (size_t i = 0; i < recipes.size(); i++) {
        if (toLower(recipes[i].getName()) == toLower(recipe.getName())) {
            cout << "\"" << recipe.getName() << "\" is already in this meal." << endl;
            return;
        }
    }
    recipes.push_back(recipe);
    cout << "\"" << recipe.getName() << "\" was added to " << mealType << "." << endl;
}

bool Meal::removeRecipe(const string& recipeName) {
    for (size_t i = 0; i < recipes.size(); i++) {
        if (toLower(recipes[i].getName()) == toLower(recipeName)) {
            recipes.erase(recipes.begin() + i);
            return true;
        }
    }
    return false;
}

void Meal::selectRecipe(RecipeDatabase& database) {
    Recipe* chosen = database.selectRecipe();
    if (chosen != nullptr) {
        addRecipe(*chosen);
    }
}

vector<Ingredient> Meal::makeGroceryList() const {
    vector<Ingredient> list;
    for (size_t i = 0; i < recipes.size(); i++) {
        vector<Ingredient> scaled = recipes[i].getScaledIngredients(numberOfPeople);
        for (size_t j = 0; j < scaled.size(); j++) {
            addToGroceryList(list, scaled[j]);
        }
    }
    return list;
}

void Meal::edit(RecipeDatabase& database) {
    while (true) {
        cout << endl << "--- Edit meal ---" << endl;
        display();
        cout << "  1. Add a recipe from the database" << endl;
        cout << "  2. Remove a recipe" << endl;
        cout << "  3. Change the number of people" << endl;
        cout << "  4. Print the recipes of this meal" << endl;
        cout << "  5. Show the grocery list for this meal" << endl;
        cout << "  0. Back" << endl;
        int choice = readInt("Select: ", 0, 5);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            selectRecipe(database);
        }
        else if (choice == 2) {
            if (recipes.empty()) {
                cout << "There are no recipes in this meal." << endl;
            } else {
                printRecipeList(recipes);
                int number = readInt("Recipe number to remove (0 = cancel): ", 0, (int)recipes.size());
                if (number > 0) {
                    removeRecipe(recipes[number - 1].getName());
                }
            }
        }
        else if (choice == 3) {
            setNumberOfPeople(readInt("Number of people: ", 1, 100));
        }
        else if (choice == 4) {
            print();
        }
        else if (choice == 5) {
            cout << "Grocery list for " << mealType << ":" << endl;
            printIngredientList(makeGroceryList());
        }
    }
}

void Meal::display() const {
    cout << mealType << " for " << numberOfPeople << (numberOfPeople == 1 ? " person" : " people") << endl;
    if (recipes.empty()) {
        cout << "    (no recipes yet)" << endl;
    }
    for (size_t i = 0; i < recipes.size(); i++) {
        cout << "    - " << recipes[i].getName() << endl;
    }
}

void Meal::print() const {
    cout << endl << "##### " << mealType << " (" << numberOfPeople
         << (numberOfPeople == 1 ? " person" : " people") << ") #####" << endl;
    if (recipes.empty()) {
        cout << "(no recipes yet)" << endl;
    }
    for (size_t i = 0; i < recipes.size(); i++) {
        recipes[i].print(numberOfPeople);
        cout << endl;
    }
}
