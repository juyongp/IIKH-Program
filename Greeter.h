// Greeter.h
// Greeter component
// Responsibilities (Lecture 3, "The first component, The Greeter"):
//   - shows a friendly welcome message when the program starts
//   - offers the user a choice of actions
//   - passes control to the RecipeDatabase or the PlanManager

#ifndef GREETER_H
#define GREETER_H

#include "RecipeDatabase.h"
#include "PlanManager.h"

class Greeter {
private:
    RecipeDatabase* database;    // component for recipe actions
    PlanManager* planManager;    // component for plan actions

public:
    Greeter(RecipeDatabase* database, PlanManager* planManager);

    void showWelcome() const;   // welcome message
    void showMenu() const;      // list of actions:
                                //  1. browse recipes     2. search recipes
                                //  3. sort recipes       4. add a new recipe
                                //  5. edit a recipe      6. review a plan
                                //  7. create a plan      0. quit
    void run();                 // repeat: show menu, read choice, pass control
};

#endif
