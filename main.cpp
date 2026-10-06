// main.cpp
// IIKH - Interactive Intelligent Kitchen Helper
// Creates the components and starts the program.

#include "Greeter.h"

// puts a few recipes into the database so the program can be tried right away
void addSampleRecipes(RecipeDatabase& database) {
    Recipe pasta("Tomato pasta", 2, 20);
    pasta.addIngredient(Ingredient("spaghetti", 200, "g"));
    pasta.addIngredient(Ingredient("tomato sauce", 1, "cup"));
    pasta.addIngredient(Ingredient("garlic", 2, "clove"));
    pasta.addIngredient(Ingredient("olive oil", 1, "tbsp"));
    pasta.addStep("Boil the spaghetti until it is soft.");
    pasta.addStep("Fry the garlic in olive oil, then add the tomato sauce.");
    pasta.addStep("Mix the spaghetti with the sauce.");
    database.addRecipe(pasta);

    Recipe salmonDill("Salmon with dill", 2, 25);
    salmonDill.addIngredient(Ingredient("salmon fillet", 2, "piece"));
    salmonDill.addIngredient(Ingredient("dill-weed", 1, "tbsp"));
    salmonDill.addIngredient(Ingredient("lemon", 1, ""));
    salmonDill.addIngredient(Ingredient("butter", 20, "g"));
    salmonDill.addStep("Put the salmon on a baking tray.");
    salmonDill.addStep("Add butter, dill-weed and lemon slices.");
    salmonDill.addStep("Bake at 200 C until the salmon is cooked through.");
    database.addRecipe(salmonDill);

    Recipe friedRice("Kimchi fried rice", 1, 10);
    friedRice.addIngredient(Ingredient("rice", 1, "bowl"));
    friedRice.addIngredient(Ingredient("kimchi", 100, "g"));
    friedRice.addIngredient(Ingredient("egg", 1, ""));
    friedRice.addIngredient(Ingredient("sesame oil", 1, "tsp"));
    friedRice.addStep("Fry the kimchi until it is nicely cooked.");
    friedRice.addStep("Add the rice and fry together.");
    friedRice.addStep("Top with a fried egg and sesame oil.");
    database.addRecipe(friedRice);

    Recipe sandwich("Egg sandwich", 1, 15);
    sandwich.addIngredient(Ingredient("egg", 2, ""));
    sandwich.addIngredient(Ingredient("bread", 2, "slice"));
    sandwich.addIngredient(Ingredient("mayonnaise", 1, "tbsp"));
    sandwich.addStep("Boil the eggs and mash them with mayonnaise.");
    sandwich.addStep("Put the egg mix between the bread slices.");
    database.addRecipe(sandwich);

    Recipe teriyaki("Salmon teriyaki", 2, 30);
    teriyaki.addIngredient(Ingredient("salmon fillet", 2, "piece"));
    teriyaki.addIngredient(Ingredient("soy sauce", 3, "tbsp"));
    teriyaki.addIngredient(Ingredient("sugar", 1, "tbsp"));
    teriyaki.addStep("Mix soy sauce and sugar.");
    teriyaki.addStep("Pan-fry the salmon and pour the sauce over it.");
    database.addRecipe(teriyaki);
}

int main() {
    RecipeDatabase database;
    PlanManager planManager;
    addSampleRecipes(database);

    Greeter greeter(&database, &planManager);
    greeter.run();
    return 0;
}
