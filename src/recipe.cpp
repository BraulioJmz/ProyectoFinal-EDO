#include "recipe.hpp"

Recipe::Recipe() {}

Recipe::Recipe(string& name, SimpleLinkedList<Ingredient>& ingredients, int& time,
    string& instructions, string& category, Name& author) {
    this->name = name;
    this->ingredients = ingredients;
    this->timeCooking = time;
    this->instructions = instructions;
    this->category = category;
    this->author = author;
}

Recipe::Recipe(const Recipe& r) {
    name = r.name;
    ingredients = r.ingredients;
    timeCooking = r.timeCooking;
    instructions = r.instructions;
    category = r.category;
    author = r.author;
}

string Recipe::getName() const {
    return name;
}

SimpleLinkedList<Ingredient> Recipe::getIngredients() const {
    return ingredients;
}

int Recipe::getTimeCooking() const {
    return timeCooking;
}

string Recipe::getInstructions() const {
    return instructions;
}

string Recipe::getCategory() const {
    return category;
}

void Recipe::setName(const string& name) {
    this->name = name;
}

void Recipe::setIngredients(const SimpleLinkedList<Ingredient>& ingredients) {
    this->ingredients = ingredients;
}

void Recipe::setTimeCooking(const int& timeCooking) {
    this->timeCooking = timeCooking;
}

void Recipe::setInstructions(const string& instructions) {
    this->instructions = instructions;
}


void Recipe::setCategory(const string& category) {
    this->category = category;
}

string Recipe::toStringResume() const {
    stringstream ss;
    ss << left << setw(25) << name
       << " | " << setw(10) << category
       << " | " << setw(5) << (to_string(timeCooking) + " min");
    return ss.str();
}

string Recipe::toString() const {
    string result;
    result += "Name: " + name + "\n";
    result += "Category: " + category + "\n";
    result += "Time cooking: " + to_string(timeCooking) + " min\n";
    result += "Ingredients:\n" + (ingredients.isEmpty() ? "No ingredients\n" : ingredients.toString());
    result += "Instructions: " + instructions + "\n";
    result += "Author: " + author.toString() + "\n";

    return result;
}

bool Recipe::compareByName(const Recipe& a, const Recipe& b) {
    return a.getName() < b.getName();
}

bool Recipe::compareByTime(const Recipe& a, const Recipe& b) {
    return a.getTimeCooking() < b.getTimeCooking();
}

void Recipe::addIngredient(const Ingredient& ingredient) {
    try {
        ingredients.insertData(ingredients.getLastPos(), ingredient);
    } catch (const SimpleLinkedList<Ingredient>::Exception& e) {
        throw SimpleLinkedList<Ingredient>::Exception("Error adding ingredient: " + string(e.what()));
    }
}

void Recipe::deleteIngredient(const string& ingredientName) {
    auto pos = ingredients.getFirstPos();
    while (pos != nullptr) {
        if (ingredients.retrieve(pos).getName() == ingredientName) {
            ingredients.deleteData(pos);
            return;
        }
        pos = ingredients.getNextPos(pos);
    }
    throw SimpleLinkedList<Ingredient>::Exception("Ingredient not found: " + ingredientName);
}

void Recipe::deleteAllIngredients() {
    ingredients.deleteAll();
}

bool Recipe::operator==(const Recipe& r) const {
    return name == r.name || category == r.category;
}

bool Recipe::operator!=(const Recipe& r) const {
    return name != r.name;
}

bool Recipe::operator<(const Recipe& r) const {
    return name < r.name;
}

bool Recipe::operator>(const Recipe& r) const {
    return name > r.name;
}

bool Recipe::operator<=(const Recipe& r) const {
    return name <= r.name;
}

bool Recipe::operator>=(const Recipe& r) const {
    return name >= r.name;
}

Recipe& Recipe::operator=(const Recipe& r) {
    name = r.name;
    ingredients = r.ingredients;
    timeCooking = r.timeCooking;
    instructions = r.instructions;
    category = r.category;
    author = r.author;
    return *this;
}

ostream& operator<<(ostream& os, Recipe& r) {
    os << r.name << '|'
       << r.category << '|'
       << r.timeCooking << '|'
       << r.instructions << '|'
       << r.author << '|';

    int ingredientCount = 0;
    auto pos = r.ingredients.getFirstPos();

    while (pos != nullptr) {
        ingredientCount++;
        pos = pos->getNext();
    }

    os << ingredientCount << '|';

    pos = r.ingredients.getFirstPos();

    int index = 0;
    while (pos != nullptr) {
        os << pos->getData();
        if (index < ingredientCount - 1) {
            os << '~';  
        }
        pos = pos->getNext();
        index++;
    }

    return os;
}

istream& operator>>(istream& is, Recipe& r) {
    string name, category, instructions;
    int timeCooking, ingredientCount;
    Name author;
    SimpleLinkedList<Ingredient> ingredients;

    getline(is, name, '|');
    getline(is, category, '|');
    is >> timeCooking;
    is.ignore();
    getline(is, instructions, '|');
    is >> author;
    is >> ingredientCount;
    is.ignore();

    for (int i = 0; i < ingredientCount; ++i) {
        string ingData;
        getline(is, ingData, '~');  
        if (ingData.empty()) continue;
    
        stringstream ingStream(ingData);
        Ingredient ingredient;
        ingStream >> ingredient;

        // Verificar si la lista está vacía
        if (ingredients.getLastPos() == nullptr) {
            // Inserta en la primera posición
            ingredients.insertData(nullptr, ingredient);
        } else {
            // Inserta al final
            ingredients.insertData(ingredients.getLastPos(), ingredient);
        }
    }

    r = Recipe(name, ingredients, timeCooking, instructions, category, author);
    return is;
}

