// Recipe.cpp

#include "Recipe.h"
#include "Utility.h"
#include <iostream>
using namespace std;

Recipe::Recipe() {
    name = "";
    servings = 1;
    preparationTime = 0;
    annotation = "";
}

Recipe::Recipe(const string& name, int servings, int preparationTime) {
    this->name = name;
    this->servings = (servings > 0) ? servings : 1;
    this->preparationTime = (preparationTime >= 0) ? preparationTime : 0;
    annotation = "";
}

string Recipe::getName() const { return name; }
int Recipe::getServings() const { return servings; }
int Recipe::getPreparationTime() const { return preparationTime; }

void Recipe::setName(const string& name) { this->name = name; }

void Recipe::setServings(int servings) {
    if (servings > 0) {
        this->servings = servings;
    }
}

void Recipe::setPreparationTime(int preparationTime) {
    if (preparationTime >= 0) {
        this->preparationTime = preparationTime;
    }
}

void Recipe::setAnnotation(const string& annotation) { this->annotation = annotation; }

void Recipe::addIngredient(const Ingredient& ingredient) {
    ingredients.push_back(ingredient);
}

bool Recipe::removeIngredient(const string& ingredientName) {
    for (size_t i = 0; i < ingredients.size(); i++) {
        if (toLower(ingredients[i].getName()) == toLower(ingredientName)) {
            ingredients.erase(ingredients.begin() + i);
            return true;
        }
    }
    return false;
}

void Recipe::addStep(const string& step) {
    steps.push_back(step);
}

bool Recipe::hasIngredient(const string& ingredientName) const {
    string wanted = toLower(ingredientName);
    for (size_t i = 0; i < ingredients.size(); i++) {
        // "tuna" also matches "canned tuna"
        if (toLower(ingredients[i].getName()).find(wanted) != string::npos) {
            return true;
        }
    }
    return false;
}

vector<Ingredient> Recipe::getScaledIngredients(int people) const {
    double factor = (double)people / servings;
    vector<Ingredient> scaled;
    for (size_t i = 0; i < ingredients.size(); i++) {
        Ingredient item = ingredients[i];
        item.setAmount(item.getAmount() * factor);
        scaled.push_back(item);
    }
    return scaled;
}

void Recipe::edit() {
    while (true) {
        cout << endl;
        display();
        cout << "--- Edit recipe ---" << endl;
        cout << "  1. Change name" << endl;
        cout << "  2. Change servings" << endl;
        cout << "  3. Change preparation time" << endl;
        cout << "  4. Add an ingredient" << endl;
        cout << "  5. Remove an ingredient" << endl;
        cout << "  6. Add a cooking step" << endl;
        cout << "  7. Write a note (annotate)" << endl;
        cout << "  0. Done" << endl;
        int choice = readInt("Select: ", 0, 7);

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            string newName = readLine("New name: ");
            if (newName != "") {
                setName(newName);
            }
        }
        else if (choice == 2) {
            setServings(readInt("New servings: ", 1, 100));
        }
        else if (choice == 3) {
            setPreparationTime(readInt("New preparation time (min): ", 0, 1000));
        }
        else if (choice == 4) {
            string ingredientName = readLine("Ingredient name: ");
            if (ingredientName != "") {
                double amount = readDouble("Amount: ");
                string unit = readLine("Unit (ex: g, cup, tbsp / Enter for none): ");
                addIngredient(Ingredient(ingredientName, amount, unit));
            }
        }
        else if (choice == 5) {
            if (ingredients.empty()) {
                cout << "There are no ingredients." << endl;
            } else {
                for (size_t i = 0; i < ingredients.size(); i++) {
                    cout << "  " << (i + 1) << ". ";
                    ingredients[i].display();
                    cout << endl;
                }
                int number = readInt("Ingredient number to remove (0 = cancel): ", 0, (int)ingredients.size());
                if (number > 0) {
                    removeIngredient(ingredients[number - 1].getName());
                }
            }
        }
        else if (choice == 6) {
            string step = readLine("New step: ");
            if (step != "") {
                addStep(step);
            }
        }
        else if (choice == 7) {
            setAnnotation(readLine("Note (Enter to clear): "));
        }
    }
}

void Recipe::display() const {
    print(servings);
}

void Recipe::print(int people) const {
    cout << "========== " << name << " ==========" << endl;
    cout << "For " << people << (people == 1 ? " person" : " people") << endl;
    // the time of estimate for the original recipe
    cout << "Expected preparation time: about " << preparationTime << " min";
    if (people != servings) {
        cout << " (for " << servings << (servings == 1 ? " serving)" : " servings)");
    }
    cout << endl;

    cout << "Ingredients:" << endl;
    vector<Ingredient> scaled = getScaledIngredients(people);
    if (scaled.empty()) {
        cout << "  (none)" << endl;
    }
    for (size_t i = 0; i < scaled.size(); i++) {
        cout << "  - ";
        scaled[i].display();
        cout << endl;
    }

    cout << "Steps:" << endl;
    if (steps.empty()) {
        cout << "  (none)" << endl;
    }
    for (size_t i = 0; i < steps.size(); i++) {
        cout << "  " << (i + 1) << ". " << steps[i] << endl;
    }
    if (annotation != "") {
        cout << "Note: " << annotation << endl;
    }
}
