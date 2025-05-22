#ifndef __NAME_HPP__
#define __NAME_HPP__

#include <string>
#include <iostream>
using namespace std;

class Name {
private: 
    string name;
    string lastName; 

public:
    Name();
    Name(string&, string&);
    Name(const Name&);

    string getName() const;
    string getLastName() const;

    void setName(const string&);
    void setLastName(const string&);

    string toString() const;
    bool operator==(const Name&) const;
    bool operator!=(const Name&) const;
    bool operator<(const Name&) const;
    bool operator>(const Name&) const;
    bool operator<=(const Name&) const;
    bool operator>=(const Name&) const;

    Name& operator=(const Name&);
    friend ostream& operator<<(ostream&, const Name&);
    friend istream& operator>>(istream&, Name&);
}; 

#endif // __NAME_HPP__