// PlanManager.h
// Plan Manager (Planner) component
// Responsibilities:
//   - permits the user to select a sequence of dates for planning
//   - permits the user to edit an existing plan
//   - works with Date objects
//   - prints the menus and the grocery list for the whole period

#ifndef PLANMANAGER_H
#define PLANMANAGER_H

#include <vector>
#include "Date.h"
#include "RecipeDatabase.h"

class PlanManager {
private:
    std::vector<Date> dates;   // a sequence of dates

public:
    void createPlan();                        // ask a start date and number of days, then make the dates
    void editPlan(RecipeDatabase& database);  // let the user choose a date and edit it
    void addDate(const Date& date);
    Date* findDate(int year, int month, int day);   // nullptr if the date is not in the plan

    void displayPlan() const;        // show the menus for the whole period
    void printGroceryList() const;   // grocery list for all dates in the plan
    bool isEmpty() const;            // true if no plan has been made yet
};

#endif
