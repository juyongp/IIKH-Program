// Greeter.h

#ifndef GREETER_H
#define GREETER_H

#include "RecipeDatabase.h"

class Greeter {
private:
    RecipeDatabase* database;

public:
    Greeter(RecipeDatabase* database);

    void showWelcome() const;   
    void showMenu() const;         
    void run();                 
};

#endif
