// RecipeDatabase.cpp

#include "RecipeDatabase.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>
using namespace std;

static bool compareByName(const Recipe& a, const Recipe& b) {
    return toLower(a.getName()) < toLower(b.getName());
}

static bool compareByPreparationTime(const Recipe& a, const Recipe& b) {
    if (a.getPreparationTime() != b.getPreparationTime()) {
        return a.getPreparationTime() < b.getPreparationTime();
    }
    return compareByName(a, b);   
}

RecipeDatabase::RecipeDatabase() {
}

bool RecipeDatabase::addRecipe(const Recipe& recipe) {
    if (recipe.getName() == "" || findRecipe(recipe.getName()) != nullptr) {
        return false;
    }
    recipes.push_back(recipe);
    return true;
}

void RecipeDatabase::addNewRecipe() {
    cout << endl << "--- Add a new recipe ---" << endl;
    string name = readLine("Recipe name (Enter to cancel): ");
    if (name == "") {
        return;
    }
    if (findRecipe(name) != nullptr) {
        cout << "A recipe named \"" << name << "\" already exists." << endl;
        return;
    }
    int servings = readInt("Servings (number of people): ", 1, 100);
    int preparationTime = readInt("Preparation time (min): ", 0, 1000);
    Recipe recipe(name, servings, preparationTime);

    cout << "Enter the ingredients (empty name = finish)." << endl;
    while (true) {
        string ingredientName = readLine("  Ingredient name: ");
        if (ingredientName == "") {
            break;
        }
        double amount = readDouble("  Amount: ");
        string unit = readLine("  Unit (ex: g, cup, tbsp / Enter for none): ");
        recipe.addIngredient(Ingredient(ingredientName, amount, unit));
    }

    cout << "Enter the cooking steps (empty line = finish)." << endl;
    int stepNumber = 1;
    while (true) {
        string step = readLine("  Step " + to_string(stepNumber) + ": ");
        if (step == "") {
            break;
        }
        recipe.addStep(step);
        stepNumber++;
    }

    recipe.setAnnotation(readLine("Note (Enter to skip): "));
    addRecipe(recipe);
    cout << "Recipe \"" << name << "\" was added." << endl;
}

bool RecipeDatabase::deleteRecipe(const string& name) {
    for (size_t i = 0; i < recipes.size(); i++) {
        if (toLower(recipes[i].getName()) == toLower(name)) {
            recipes.erase(recipes.begin() + i);
            return true;
        }
    }
    return false;
}

Recipe* RecipeDatabase::findRecipe(const string& name) {
    for (size_t i = 0; i < recipes.size(); i++) {
        if (toLower(recipes[i].getName()) == toLower(name)) {
            return &recipes[i];
        }
    }
    return nullptr;
}

vector<Recipe> RecipeDatabase::searchByName(const string& keyword) const {
    vector<Recipe> result;
    for (size_t i = 0; i < recipes.size(); i++) {
        if (toLower(recipes[i].getName()).find(toLower(keyword)) != string::npos) {
            result.push_back(recipes[i]);
        }
    }
    return result;
}

vector<Recipe> RecipeDatabase::searchByIngredient(const string& ingredient) const {
    vector<Recipe> result;
    for (size_t i = 0; i < recipes.size(); i++) {
        if (recipes[i].hasIngredient(ingredient)) {
            result.push_back(recipes[i]);
        }
    }
    return result;
}

void RecipeDatabase::sortByName() {
    sort(recipes.begin(), recipes.end(), compareByName);
}

void RecipeDatabase::sortByPreparationTime() {
    sort(recipes.begin(), recipes.end(), compareByPreparationTime);
}

void RecipeDatabase::browse() {
    if (recipes.empty()) {
        cout << "The recipe database is empty." << endl;
        return;
    }
    while (true) {
        cout << endl << "--- All recipes ---" << endl;
        displayAll();
        int number = readInt("Recipe number to view (0 = back): ", 0, (int)recipes.size());
        if (number == 0) {
            break;
        }
        viewRecipe(recipes[number - 1]);
    }
}

void RecipeDatabase::editRecipe() {
    Recipe* selected = selectRecipe();
    if (selected == nullptr) {
        return;
    }
    cout << "Selected: " << selected->getName() << endl;
    cout << "  1. Edit or annotate this recipe" << endl;
    cout << "  2. Delete this recipe" << endl;
    cout << "  0. Cancel" << endl;
    int choice = readInt("Select: ", 0, 2);

    if (choice == 1) {
        Recipe copy = *selected;   
        copy.edit();
        Recipe* sameName = findRecipe(copy.getName());
        if (sameName != nullptr && sameName != selected) {
            cout << "Another recipe is already named \"" << copy.getName()
                 << "\". Changes were not saved." << endl;
            return;
        }
        *selected = copy;
        cout << "Recipe updated." << endl;
    }
    else if (choice == 2) {
        string name = selected->getName();
        if (readYesNo("Really delete \"" + name + "\"?")) {
            deleteRecipe(name);
            cout << "Recipe deleted." << endl;
        }
    }
}

Recipe* RecipeDatabase::selectRecipe() {
    if (recipes.empty()) {
        cout << "The recipe database is empty." << endl;
        return nullptr;
    }
    cout << "How do you want to find the recipe?" << endl;
    cout << "  1. Show all recipes" << endl;
    cout << "  2. Search by name" << endl;
    cout << "  3. Search by ingredient" << endl;
    cout << "  0. Cancel" << endl;
    int choice = readInt("Select: ", 0, 3);
    if (choice == 0) {
        return nullptr;
    }

    vector<Recipe> list;
    if (choice == 1) {
        list = recipes;
    } else {
        string keyword = readLine("Keyword: ");
        if (choice == 2) {
            list = searchByName(keyword);
        } else {
            list = searchByIngredient(keyword);
        }
    }
    if (list.empty()) {
        cout << "No recipe found." << endl;
        return nullptr;
    }

    printRecipeList(list);
    int number = readInt("Recipe number (0 = cancel): ", 0, (int)list.size());
    if (number == 0) {
        return nullptr;
    }
    return findRecipe(list[number - 1].getName());
}

void RecipeDatabase::displayAll() const {
    if (recipes.empty()) {
        cout << "  (no recipes)" << endl;
        return;
    }
    printRecipeList(recipes);
}
