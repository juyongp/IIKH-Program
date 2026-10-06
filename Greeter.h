// Greeter.h
// Greeter component
// Responsibilities:
//   - shows an welcome screen when the IIKH starts
//   - offers the user a menu of actions (browse / search / sort / add / edit
//     recipes, review or create a meal plan, BMI-based recommendation)


#ifndef GREETER_H
#define GREETER_H

#include "RecipeDatabase.h"
#include "PlanManager.h"

class Greeter {
private:
    RecipeDatabase* database;   // the recipe database
    PlanManager* planManager;   // the plan manager 

public:
    Greeter(RecipeDatabase* database, PlanManager* planManager);

    void showWelcome() const;   // print the welcome banner and wait for Enter
    void showMenu() const;      // print the main menu
    void run();                 // main loop: show the menu, read a choice and dispatch it until the user quits
};

#endif
