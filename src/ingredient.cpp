#include "ingredient.hpp"

Ingredient::Ingredient(){}

Ingredient::Ingredient(const string& name, float quantity){
    this -> name = name;
    this -> quantity = quantity;
}

Ingredient::Ingredient(const Ingredient& i){
    name = i.name;
    quantity = i.quantity;
}

string Ingredient::getName() const{
    return name;
}

float Ingredient::getQuantity() const{
    return quantity;
}

void Ingredient::setName(const string& name){
    this -> name = name;
}

void Ingredient::setQuantity(const float& quantity){
    this -> quantity = quantity;
}

string Ingredient::toString() const{
    stringstream ss;
    ss << name << " | Quantity: " << fixed << setprecision(2) << quantity;
    return ss.str();
}

bool Ingredient::operator==(const Ingredient& i) const{
    return name == i.name;  
}

bool Ingredient::operator!=(const Ingredient& i) const{
    return name != i.name;
}

bool Ingredient::operator<(const Ingredient& i) const{
    return name < i.name;
}

bool Ingredient::operator>(const Ingredient& i) const{
    return name > i.name;
}

bool Ingredient::operator<=(const Ingredient& i) const{
    return name <= i.name;
}

bool Ingredient::operator>=(const Ingredient& i) const{
    return name >= i.name;
}

Ingredient& Ingredient::operator=(const Ingredient& i){
    name = i.name;
    quantity = i.quantity;
    return *this;
}

ostream& operator<<(ostream& os, const Ingredient& i){
    os << i.getName() << "," << i.getQuantity();
    return os;
}

istream& operator>>(istream& is, Ingredient& i){
    string ingLine;
    getline(is, ingLine); 

    size_t commaPos = ingLine.rfind(','); 
    if (commaPos != string::npos) {
        i.setName(ingLine.substr(0, commaPos));
        i.setQuantity(stoi(ingLine.substr(commaPos + 1)));
    } else {
        i.setName(ingLine);
        i.setQuantity(0);
    }

    return is;
}

