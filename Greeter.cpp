// Greeter.cpp

#include "Greeter.h"
#include "Utility.h"
#include <iostream>
using namespace std;

static void searchRecipes(RecipeDatabase* database) {
    cout << endl << "--- Search recipes ---" << endl;
    cout << "  1. Search by name" << endl;
    cout << "  2. Search by ingredient" << endl;
    cout << "  0. Back" << endl;
    int choice = readInt("Select: ", 0, 2);
    if (choice == 0) {
        return;
    }
    string keyword = readLine("Keyword: ");
    if (keyword == "") {
        return;
    }

    vector<Recipe> results;
    if (choice == 1) {
        results = database->searchByName(keyword);
    } else {
        results = database->searchByIngredient(keyword);
    }
    cout << results.size() << " recipe(s) found." << endl;

    while (!results.empty()) {
        printRecipeList(results);
        int number = readInt("Recipe number to view (0 = back): ", 0, (int)results.size());
        if (number == 0) {
            break;
        }
        viewRecipe(results[number - 1]);
    }
}

static void sortRecipes(RecipeDatabase* database) {
    cout << endl << "--- Sort recipes ---" << endl;
    cout << "  1. By name (A -> Z)" << endl;
    cout << "  2. By preparation time (shortest first)" << endl;
    cout << "  0. Back" << endl;
    int choice = readInt("Select: ", 0, 2);
    if (choice == 0) {
        return;
    }
    if (choice == 1) {
        database->sortByName();
    } else {
        database->sortByPreparationTime();
    }
    cout << "Recipes sorted:" << endl;
    database->displayAll();
}

Greeter::Greeter(RecipeDatabase* database, PlanManager* planManager) {
    this->database = database;
    this->planManager = planManager;
}

void Greeter::showWelcome() const {
    cout << "==========================================" << endl;
    cout << "            Welcome to the IIKH" << endl;
    cout << "  Interactive Intelligent Kitchen Helper" << endl;
    cout << "==========================================" << endl;
    readLine("Press Enter to begin...");
}

void Greeter::showMenu() const {
    cout << endl << "=============== Main Menu ===============" << endl;
    cout << "  1. Browse recipes" << endl;
    cout << "  2. Search recipes" << endl;
    cout << "  3. Sort recipes" << endl;
    cout << "  4. Add a new recipe" << endl;
    cout << "  5. Edit or annotate a recipe" << endl;
    cout << "  6. Review the meal plan" << endl;
    cout << "  7. Create a new meal plan" << endl;
    cout << "  8. Recommend recipes by BMI" << endl;
    cout << "  0. Quit" << endl;
}

void Greeter::run() {
    showWelcome();
    while (true) {
        showMenu();
        int choice = readInt("Select: ", 0, 8);
        if (choice == 0) {
            break;
        }
        // pass control to the component responsible for the action
        switch (choice) {
        case 1: database->browse(); break;
        case 2: searchRecipes(database); break;
        case 3: sortRecipes(database); break;
        case 4: database->addNewRecipe(); break;
        case 5: database->editRecipe(); break;
        case 6:
        case 7:
            cout << "Meal planning is not available yet." << endl;
            break;
        case 8:
            cout << "BMI recommendation is not available yet." << endl;
            break;
        }
    }
    cout << "Goodbye!" << endl;
}
