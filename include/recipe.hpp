#ifndef __RECIPE_HPP__
#define __RECIPE_HPP__

#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

#include "listaSimplementeLigada.hpp"
#include "Ingredient.hpp"
#include "Name.hpp"

class Recipe {
private: 
    string name;
    SimpleLinkedList<Ingredient> ingredients; 
    int timeCooking;
    string instructions;
    string category; 
    Name author;

public: 
    Recipe();
    Recipe(string&, SimpleLinkedList<Ingredient>&, int&, string&, string&, Name&);
    Recipe(const Recipe&);

    string getName() const;
    SimpleLinkedList<Ingredient> getIngredients() const;
    int getTimeCooking() const;
    string getInstructions() const;
    string getCategory() const;

    void setName(const string&);
    void setIngredients(const SimpleLinkedList<Ingredient>&);
    void setTimeCooking(const int&);
    void setInstructions(const string&);
    void setCategory(const string&);

    string toStringResume() const;
    string toString() const; 

    static bool compareByName(const Recipe&, const Recipe&);
    static bool compareByTime(const Recipe&, const Recipe&);

    void addIngredient(const Ingredient&);
    void deleteIngredient(const string&);
    void deleteAllIngredients();

    bool operator==(const Recipe&) const;
    bool operator==(const string&) const;
    bool operator!=(const Recipe&) const;
    bool operator<(const Recipe&) const;
    bool operator>(const Recipe&) const;
    bool operator<=(const Recipe&) const;
    bool operator>=(const Recipe&) const;

    Recipe& operator=(const Recipe&);
    friend ostream& operator<<(ostream&, Recipe&);
    friend istream& operator>>(istream&, Recipe&);
};

#endif // __RECIPE_HPP__