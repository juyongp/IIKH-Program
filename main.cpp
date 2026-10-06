// main.cpp
// IIKH - Interactive Intelligent Kitchen Helper

#include "Greeter.h"

// puts a few recipes into the database
void addSampleRecipes(RecipeDatabase& database) {
    Recipe friedRice("Kimchi fried rice", 1, 10);
    friedRice.addIngredient(Ingredient("rice", 1, "bowl"));
    friedRice.addIngredient(Ingredient("kimchi", 100, "g"));
    friedRice.addIngredient(Ingredient("egg", 1, ""));
    friedRice.addIngredient(Ingredient("sesame oil", 1, "tsp"));
    friedRice.addStep("Fry the kimchi until it is nicely cooked.");
    friedRice.addStep("Add the rice and fry together.");
    friedRice.addStep("Top with a fried egg and sesame oil.");
    database.addRecipe(friedRice);

    Recipe omurice("Omurice", 1, 20);
    omurice.addIngredient(Ingredient("rice", 1, "bowl"));
    omurice.addIngredient(Ingredient("egg", 2, ""));
    omurice.addIngredient(Ingredient("onion", 0.5, ""));
    omurice.addIngredient(Ingredient("ketchup", 2, "tbsp"));
    omurice.addIngredient(Ingredient("butter", 10, "g"));
    omurice.addStep("Fry the chopped onion in butter, then add the rice and ketchup.");
    omurice.addStep("Beat the eggs and cook them into a thin omelet.");
    omurice.addStep("Put the rice on the omelet and fold it over.");
    database.addRecipe(omurice);

    Recipe shrimpPasta("Shrimp cream pasta", 2, 25);
    shrimpPasta.addIngredient(Ingredient("spaghetti", 200, "g"));
    shrimpPasta.addIngredient(Ingredient("shrimp", 200, "g"));
    shrimpPasta.addIngredient(Ingredient("heavy cream", 1, "cup"));
    shrimpPasta.addIngredient(Ingredient("garlic", 3, "clove"));
    shrimpPasta.addIngredient(Ingredient("onion", 0.5, ""));
    shrimpPasta.addIngredient(Ingredient("parmesan cheese", 2, "tbsp"));
    shrimpPasta.addStep("Boil the spaghetti until it is soft.");
    shrimpPasta.addStep("Fry the garlic, onion and shrimp until the shrimp turns pink.");
    shrimpPasta.addStep("Pour in the cream and cheese, then mix with the spaghetti.");
    database.addRecipe(shrimpPasta);

    Recipe curry("Chicken curry", 4, 40);
    curry.addIngredient(Ingredient("chicken", 500, "g"));
    curry.addIngredient(Ingredient("potato", 2, ""));
    curry.addIngredient(Ingredient("carrot", 1, ""));
    curry.addIngredient(Ingredient("onion", 1, ""));
    curry.addIngredient(Ingredient("curry powder", 100, "g"));
    curry.addIngredient(Ingredient("water", 3, "cup"));
    curry.addIngredient(Ingredient("rice", 4, "bowl"));
    curry.addStep("Cut the chicken and vegetables into bite-size pieces.");
    curry.addStep("Fry the chicken until the outside is cooked, then add the vegetables.");
    curry.addStep("Add the water and boil until the vegetables are soft.");
    curry.addStep("Stir in the curry powder and simmer until it is thick.");
    curry.addStep("Serve over rice.");
    database.addRecipe(curry);

    Recipe kimbap("Tuna kimbap", 2, 30);
    kimbap.addIngredient(Ingredient("rice", 2, "bowl"));
    kimbap.addIngredient(Ingredient("dried seaweed", 2, "sheet"));
    kimbap.addIngredient(Ingredient("canned tuna", 1, "can"));
    kimbap.addIngredient(Ingredient("mayonnaise", 2, "tbsp"));
    kimbap.addIngredient(Ingredient("egg", 2, ""));
    kimbap.addIngredient(Ingredient("pickled radish", 2, "strip"));
    kimbap.addIngredient(Ingredient("sesame oil", 1, "tsp"));
    kimbap.addStep("Mix the rice with sesame oil and a little salt.");
    kimbap.addStep("Mix the tuna with mayonnaise.");
    kimbap.addStep("Cook the eggs into a thin omelet and cut it into strips.");
    kimbap.addStep("Put the rice on the seaweed, add the fillings and roll it tightly.");
    kimbap.addStep("Cut the roll into bite-size pieces.");
    database.addRecipe(kimbap);
}

int main() {
    RecipeDatabase database;
    addSampleRecipes(database);

    PlanManager planManager;
    Greeter greeter(&database, &planManager);
    greeter.run();
    return 0;
}
