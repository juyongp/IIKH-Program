// Utility.cpp

#include "Utility.h"
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

static string trim(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

int readInt(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { 
            cout << endl;
            return min;
        }
        stringstream ss(line);
        int value;
        char extra;
        
        if (ss >> value && !(ss >> extra) && value >= min && value <= max) {
            return value;
        }
        cout << "  Please enter a number from " << min << " to " << max << "." << endl;
    }
}

double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {   
            cout << endl;
            return 1.0;
        }
        stringstream ss(line);
        double value;
        char extra;
        if (ss >> value && !(ss >> extra) && value > 0) {
            return value;
        }
        cout << "  Please enter a number greater than 0." << endl;
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) {  
        cout << endl;
        return "";
    }
    return trim(line);
}

bool readYesNo(const string& prompt) {
    while (true) {
        string answer = toLower(readLine(prompt + " (y/n): "));
        if (!cin) {   
            return false;
        }
        if (answer == "y" || answer == "yes") {
            return true;
        }
        if (answer == "n" || answer == "no") {
            return false;
        }
        cout << "  Please enter y or n." << endl;
    }
}

string toLower(const string& text) {
    string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = (char)tolower((unsigned char)result[i]);
    }
    return result;
}

void addToGroceryList(vector<Ingredient>& list, const Ingredient& item) {
    for (size_t i = 0; i < list.size(); i++) {
        bool sameName = toLower(list[i].getName()) == toLower(item.getName());
        bool sameUnit = toLower(list[i].getUnit()) == toLower(item.getUnit());
        if (sameName && sameUnit) {
            list[i].setAmount(list[i].getAmount() + item.getAmount());
            return;
        }
    }
    list.push_back(item);
}

void printIngredientList(const vector<Ingredient>& list) {
    if (list.empty()) {
        cout << "  (nothing)" << endl;
        return;
    }
    for (size_t i = 0; i < list.size(); i++) {
        cout << "  [ ] ";
        list[i].display();
        cout << endl;
    }
}

void printRecipeList(const vector<Recipe>& list) {
    for (size_t i = 0; i < list.size(); i++) {
        cout << "  " << (i + 1) << ". " << list[i].getName()
             << "  (" << list[i].getPreparationTime() << " min)" << endl;
    }
}

void viewRecipe(const Recipe& recipe) {
    int people = readInt("How many people? (0 = cancel): ", 0, 100);
    if (people == 0) {
        return;
    }
    cout << endl;
    recipe.print(people);
}
