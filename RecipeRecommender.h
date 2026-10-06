// RecipeRecommender.h
// Recipe Recommender component
// Responsibilities:
//   - asks the user's height and weight
//   - calculates the BMI (weight(kg) / height(m)^2)
//   - BMI is high  -> recommends low-calorie dishes
//   - BMI is low   -> recommends high-calorie dishes
//   - BMI is normal -> tells the user that any recipe is fine

#ifndef RECIPERECOMMENDER_H
#define RECIPERECOMMENDER_H

#include <vector>
#include "Recipe.h"
#include "RecipeDatabase.h"

class RecipeRecommender {
private:
    double height;   // cm
    double weight;   // kg

public:
    void readUserInfo();             // ask the height and weight
    double calculateBMI() const;     // weight(kg) / height(m)^2
    bool isHighBMI() const;          // true if low-calorie dishes should be recommended
    bool isLowBMI() const;           // true if high-calorie dishes should be recommended

    std::vector<Recipe> findLowCalorieDishes(const RecipeDatabase& database) const;
    std::vector<Recipe> findHighCalorieDishes(const RecipeDatabase& database) const;

    void recommend(RecipeDatabase& database);   // show the BMI and the recommended recipes
};

#endif
