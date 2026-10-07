// RecipeRecommender.cpp

#include "RecipeRecommender.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

static const double HIGH_BMI = 25.0;         // 25 or more -> low-calorie dishes
static const double LOW_BMI = 18.5;          // less than 18.5 -> high-calorie dishes
static const int LOW_CALORIE_LIMIT = 500;    // kcal per serving
static const int HIGH_CALORIE_LIMIT = 700;   // kcal per serving

// number in [min, max]
static double readDoubleInRange(const string& prompt, double min, double max) {
    while (true) {
        double value = readDouble(prompt);
        if (!cin || (value >= min && value <= max)) {
            return value;
        }
        cout << "  Please enter a number from " << min << " to " << max << "." << endl;
    }
}

RecipeRecommender::RecipeRecommender() {
    height = 0;
    weight = 0;
}

void RecipeRecommender::readUserInfo() {
    height = readDoubleInRange("Height (cm): ", 50, 250);
    weight = readDoubleInRange("Weight (kg): ", 10, 300);
}

double RecipeRecommender::calculateBMI() const {
    if (height <= 0) {
        return 0;
    }
    double meters = height / 100;
    return weight / (meters * meters);
}

bool RecipeRecommender::isHighBMI() const {
    return calculateBMI() >= HIGH_BMI;
}

bool RecipeRecommender::isLowBMI() const {
    double bmi = calculateBMI();
    return bmi > 0 && bmi < LOW_BMI;
}

vector<Recipe> RecipeRecommender::findLowCalorieDishes(const RecipeDatabase& database) const {
    vector<Recipe> all = database.getAllRecipes();
    vector<Recipe> result;
    for (size_t i = 0; i < all.size(); i++) {
        // recipes with unknown calories (0) are skipped
        if (all[i].getCalories() > 0 && all[i].getCalories() <= LOW_CALORIE_LIMIT) {
            result.push_back(all[i]);
        }
    }
    return result;
}

vector<Recipe> RecipeRecommender::findHighCalorieDishes(const RecipeDatabase& database) const {
    vector<Recipe> all = database.getAllRecipes();
    vector<Recipe> result;
    for (size_t i = 0; i < all.size(); i++) {
        if (all[i].getCalories() >= HIGH_CALORIE_LIMIT) {
            result.push_back(all[i]);
        }
    }
    return result;
}

void RecipeRecommender::recommend(RecipeDatabase& database) {
    cout << endl << "--- Recommend recipes by BMI ---" << endl;
    readUserInfo();

    // format on a separate stream so cout keeps its default number format
    ostringstream bmiText;
    bmiText << fixed << setprecision(1) << calculateBMI();
    cout << "Your BMI is " << bmiText.str() << "." << endl;

    vector<Recipe> results;
    if (isHighBMI()) {
        cout << "Your BMI is high. Low-calorie dishes (" << LOW_CALORIE_LIMIT
             << " kcal or less per serving) are recommended." << endl;
        results = findLowCalorieDishes(database);
    }
    else if (isLowBMI()) {
        cout << "Your BMI is low. High-calorie dishes (" << HIGH_CALORIE_LIMIT
             << " kcal or more per serving) are recommended." << endl;
        results = findHighCalorieDishes(database);
    }
    else {
        cout << "Your BMI is in the normal range. Any recipe is fine - enjoy your meal!" << endl;
        return;
    }

    if (results.empty()) {
        cout << "No matching recipe is in the database." << endl;
        return;
    }
    while (true) {
        printRecipeList(results);
        int number = readInt("Recipe number to view (0 = back): ", 0, (int)results.size());
        if (number == 0) {
            break;
        }
        viewRecipe(results[number - 1]);
    }
}
