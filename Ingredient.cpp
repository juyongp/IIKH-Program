// Ingredient.cpp

#include "Ingredient.h"
#include <iostream>
#include <cmath>
using namespace std;

Ingredient::Ingredient() {
    name = "";
    amount = 0;
    unit = "";
}

Ingredient::Ingredient(const string& name, double amount, const string& unit) {
    this->name = name;
    this->amount = amount;
    this->unit = unit;
}

string Ingredient::getName() const { return name; }
double Ingredient::getAmount() const { return amount; }
string Ingredient::getUnit() const { return unit; }

void Ingredient::setAmount(double amount) { this->amount = amount; }

void Ingredient::display() const {
    double rounded = floor(amount * 100 + 0.5) / 100;
    cout << rounded << " ";
    if (unit != "") {
        cout << unit << " ";
    }
    cout << name;
}
