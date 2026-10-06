// Greeter.h

#ifndef GREETER_H
#define GREETER_H

#include "RecipeDatabase.h"
#include "PlanManager.h"

class Greeter {
private:
    RecipeDatabase* database;
    PlanManager* planManager;

public:
    Greeter(RecipeDatabase* database, PlanManager* planManager);

    void showWelcome() const;   
    void showMenu() const;         
    void run();                 
};

#endif
