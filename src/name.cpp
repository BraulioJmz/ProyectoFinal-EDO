#include "Name.hpp"

Name::Name(){}

Name::Name(string& name, string& lastName){
    this -> name = name;
    this -> lastName = lastName;
}

Name::Name(const Name& n){
    name = n.name;
    lastName = n.lastName;
}

string Name::getName() const{
    return name;
}

string Name::getLastName() const{
    return lastName;
}

void Name::setName(const string& name){
    this -> name = name;
}

void Name::setLastName(const string& lastName){
    this -> lastName = lastName;
}

string Name::toString() const{
    return name + " " + lastName;
}

bool Name::operator==(const Name& n) const{
    return name == n.name;
}

bool Name::operator!=(const Name& n) const{
    return name != n.name;
}

bool Name::operator<(const Name& n) const{
    return name < n.name;
}

bool Name::operator>(const Name& n) const{
    return name > n.name;
}

bool Name::operator<=(const Name& n) const{
    return name <= n.name;
}

bool Name::operator>=(const Name& n) const{
    return name >= n.name;
}

Name& Name::operator=(const Name& n){
    name = n.name;
    lastName = n.lastName;
    return *this;
}

ostream& operator<<(ostream& os, const Name& name){
    os << name.getName() << "," << name.getLastName();
    return os;
}

istream& operator>>(istream& is, Name& nombre){
    string fn, ln;
    getline(is, fn, ',');
    getline(is, ln, '|');
    nombre.setName(fn);
    nombre.setLastName(ln);
    return is;
}

