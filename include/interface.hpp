#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <iostream>
using namespace std;

#include "listaDoblementeLigada.hpp"
#include "recipe.hpp"
#include "ingredient.hpp"

class Interface {
public:
    Interface(DoublyLinkedList<Recipe>&);

    void showMenu();
    void showFullList(DoublyLinkedList<Recipe>&);
    void showResumeList(DoublyLinkedList<Recipe>&);

    void addRecipe(DoublyLinkedList<Recipe>&);
    void deleteRecipe(DoublyLinkedList<Recipe>&);
    int deleteOption(); 
    void sortRecipes(DoublyLinkedList<Recipe>&);
    void searchRecipe(DoublyLinkedList<Recipe>&);
    void modifyRecipe(DoublyLinkedList<Recipe>&);
    void modifyIngredient(Recipe&);

    void saveList(DoublyLinkedList<Recipe>&);
    void loadList(DoublyLinkedList<Recipe>&);

}; 

#endif // __INTERFACE_HPP__