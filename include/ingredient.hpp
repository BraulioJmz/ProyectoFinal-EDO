#ifndef __INGREDIENT_HPP__
#define __INGREDIENT_HPP__

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

class Ingredient {
private:
    string name; 
    float quantity;

public:
    Ingredient();
    Ingredient(const string&, float);
    Ingredient(const Ingredient&);

    string getName() const;
    float getQuantity() const;

    void setName(const string&);
    void setQuantity(const float&);

    string toString() const;
    bool operator==(const Ingredient&) const;
    bool operator!=(const Ingredient&) const;
    bool operator<(const Ingredient&) const;
    bool operator>(const Ingredient&) const;
    bool operator<=(const Ingredient&) const;
    bool operator>=(const Ingredient&) const;

    Ingredient& operator=(const Ingredient&);
    friend ostream& operator<<(ostream&, const Ingredient&);
    friend istream& operator>>(istream&, Ingredient&);
};


#endif // __INGREDIENT_HPP__