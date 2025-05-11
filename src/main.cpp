#include <iostream>

#include "interface.hpp"
#include "recipe.hpp"
#include "listaDoblementeLigada.hpp"

int main(){
    DoublyLinkedList<Recipe> recipes;
    Interface interface(recipes);

    return 0; 
}
