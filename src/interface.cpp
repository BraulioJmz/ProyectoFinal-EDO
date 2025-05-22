#include "interface.hpp"

Interface::Interface(DoublyLinkedList<Recipe>& recipes) {
    int opc;
    do {
        showResumeList(recipes);
        showMenu();
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1:
                addRecipe(recipes);
                break;
            case 2:
                deleteRecipe(recipes);
                break;
            case 3:
                showFullList(recipes);
                break;
            case 4:
                sortRecipes(recipes);
                break;
            case 5:
                searchRecipe(recipes);
                break;
            case 6:
                modifyRecipe(recipes);
                break;
            case 7:
                saveList(recipes);
                break;
            case 8:
                loadList(recipes);
                break;
            default:
                cout << "Invalid option" << endl;
        }
    } while (opc != 9);
}

void Interface::showMenu() {
    cout << "\n1. Add recipe" << endl;
    cout << "2. Delete recipe" << endl;
    cout << "3. Show full list" << endl;
    cout << "4. Sort list" << endl;
    cout << "5. Search recipe " << endl;
    cout << "6. Modify recipe" << endl;
    cout << "7. Save list" << endl;
    cout << "8. Load list" << endl;
    cout << "9. Exit" << endl;
    cout << "Option: ";
}

void Interface::showFullList(DoublyLinkedList<Recipe>& recipes) {
    if (recipes.isEmpty()) {
        system("cls");
        return;
    }

    cout << "\nRecipe list:\n\n";
    cout << recipes.toString();
}

void Interface::showResumeList(DoublyLinkedList<Recipe>& recipes) {
    if (recipes.isEmpty()) {
        cout << "\nThe recipe list is empty" << endl;
        return;
    }

    cout << "\nRecipe list:\n";
    cout << recipes.toStringResume();
}

void Interface::addRecipe(DoublyLinkedList<Recipe>& recipes) {
    string name, category, instructions;
    int timeCooking;
    SimpleLinkedList<Ingredient> ingredients;

    cout << "\nName: ";
    getline(cin, name);

    cout << "Category: ";
    getline(cin, category);

    cout << "Time cooking (min): ";
    cin >> timeCooking;
    cin.ignore();

    cout << "Instructions: ";
    getline(cin, instructions);

    cout << "Author \n";
    string autorName, autorLastName;
    cout << "Name: ";
    getline(cin, autorName);
    cout << "Last name: ";
    getline(cin, autorLastName);

    Name autor(autorName, autorLastName);

    char opc;
    cout << "\nIngredients: ";
    do {
        string ingredientName;
        float ingredientQuantity;

        cout << "\nIngredient name: ";
        getline(cin, ingredientName);

        cout << "Quantity: ";
        cin >> ingredientQuantity;
        cin.ignore();

        Ingredient ingredient(ingredientName, ingredientQuantity);

        auto pos = ingredients.getFirstPos(); 
        while(pos != nullptr && pos->getData() < ingredient) {
            pos = pos->getNext(); 
        }
        auto prev = ingredients.getPrev(pos);

        try {
            ingredients.insertData(prev, ingredient);
        } catch (const SimpleLinkedList<Ingredient>::Exception& e) {
            cout << "Error adding ingredient: " << e.what() << endl;
        }

        cout << "Add another ingredient? (Y/N): ";
        cin >> opc;
        cin.ignore();
    } while (opc != 'N' && opc != 'n');

    try {
        Recipe recipe(name, ingredients, timeCooking, instructions, category, autor);
        recipes.insertData(recipes.getLastPos(), recipe);
        system("cls");
    } catch (const DoublyLinkedList<Recipe>::Exception& e) {
        cout << "Error adding recipe: " << e.what() << endl;
    }
}

void Interface::deleteRecipe(DoublyLinkedList<Recipe>& recipes) {
    string name;

    if (recipes.isEmpty()) {
        system("cls");
        cout << "The recipe list is empty.\n";
        return;
    }

    int opc = deleteOption();
    switch (opc) {
        case 1: {
            cout << "\nName of the recipe to delete: ";
            getline(cin, name);

            auto pos = recipes.getFirstPos();  

            while (pos != nullptr) {
                if (pos->getData().getName() == name) {
                    recipes.deleteData(pos);
                    cout << "Recipe deleted\n";
                    return;  
                }
                pos = pos->getNext();
            }

            cout << "Recipe not found" << endl;
        }
        break;

        case 2:
            system("cls");
            cout << "All recipes deleted\n";
            recipes.deleteAll();
            break;

        case 3:
            cout << "Canceling...\n";
            break;

        default:
            cout << "Invalid option." << endl;
            break;
    }
}

int Interface::deleteOption() {
    int opc;
    cout << "\n1.Delete a recipe\n";
    cout << "2.Delete all recipes\n";
    cout << "3.Cancel\n";
    cout << "Option: ";
    cin >> opc;
    cin.ignore();

    return opc;
}

void Interface::sortRecipes(DoublyLinkedList<Recipe>& recipes) {
    if (recipes.isEmpty()) {
        system("cls");
        return;
    }

    int opc;
    cout << "\n1. Sort by name\n";
    cout << "2. Sort by time cooking\n";
    cout << "Option: ";
    cin >> opc;
    cin.ignore();

    switch (opc) {
        case 1:
            recipes.sortDataQuick(Recipe::compareByName);
            system("cls");
            break;

        case 2:
            recipes.sortDataQuick(Recipe::compareByTime);
            system("cls");
            break;

        default:
            cout << "Invalid option" << endl;
            break;
    }
}

void Interface::searchRecipe(DoublyLinkedList<Recipe>& recipes) {
    if (recipes.isEmpty()) {
        system("cls");
        return;
    }

    int opc;
    cout << "\n1. Search by name\n";
    cout << "2. Search by category\n";
    cout << "Option: ";
    cin >> opc;
    cin.ignore();

    switch (opc) {
        case 1: {
            string name;
            cout << "\nName of the recipe to search: ";
            getline(cin, name);

            Recipe temp;
            temp.setName(name);

            auto pos = recipes.findDataL(temp);
            if (pos != nullptr) {
                cout << "\nRecipe found:\n" << recipes.retrieve(pos).toString() << endl;
            } else {
                cout << "Recipe not found" << endl;
            }
        }
        break;

        case 2: {
            string category;
            cout << "\nCategory of the recipe to search: ";
            getline(cin, category);

            Recipe temp;
            temp.setCategory(category);

            auto pos = recipes.findDataL(temp);
            if (pos != nullptr) {
                cout << "\nRecipe found:\n" << recipes.retrieve(pos).toString() << endl;
            } else {
                cout << "Recipe not found" << endl;
            }
        }
        break;

        default:
            cout << "Invalid option" << endl;
            break;
    }
}

void Interface::modifyRecipe(DoublyLinkedList<Recipe>& recipes) {
    if (recipes.isEmpty()) {
        system("cls");
        return;
    }

    string name;
    cout << "\nName of the recipe to modify: ";
    getline(cin, name);

    Recipe temp;
    temp.setName(name);

    auto pos = recipes.findDataL(temp);
    if (pos != nullptr) {
        Recipe& recipe = recipes.retrieve(pos);
        recipe.toString();
        modifyIngredient(recipe);

    } else {
        cout << "Recipe not found" << endl;
    }
}

void Interface::modifyIngredient(Recipe& recipe) {
    int opc;

    recipe.toString();

    cout << "\n1. Add ingredient\n";
    cout << "2. Delete ingredient\n";
    cout << "3. Modify ingredient\n";
    cout << "4. Delete all ingredients\n";
    cout << "5. Modify instructions\n";
    cout << "Option: ";
    cin >> opc;
    cin.ignore();

    switch (opc) {
        case 1: {
            string ingredientName;
            float ingredientQuantity;

            cout << "\nIngredient name: ";
            getline(cin, ingredientName);

            cout << "Quantity: ";
            cin >> ingredientQuantity;
            cin.ignore();

            Ingredient ingredient(ingredientName, ingredientQuantity);

            try {
                recipe.addIngredient(ingredient);
                cout << "Ingredient added\n";
            } catch (const DoublyLinkedList<Ingredient>::Exception& e) {
                cout << "Error adding ingredient: " << e.what() << endl;
            }
        }
        break;

        case 2: {
            string ingredientName;
            cout << "\nIngredient to delete: ";
            getline(cin, ingredientName);

            try {
                recipe.deleteIngredient(ingredientName);
            } catch (const DoublyLinkedList<Recipe>::Exception& e) {
                cout << e.what() << endl;
            }
        }
        break;

        case 3: {
            string ingredientName;
            float ingredientQuantity;

            cout << "\nIngredient name: ";
            getline(cin, ingredientName);

            cout << "Quantity: ";
            cin >> ingredientQuantity;
            cin.ignore();

            Ingredient ingredient(ingredientName, ingredientQuantity);

            try {
                recipe.deleteIngredient(ingredientName);
                recipe.addIngredient(ingredient);
                cout << "Ingredient modified\n";
            } catch (const DoublyLinkedList<Ingredient>::Exception& e) {
                cout << "Error modifying ingredient: " << e.what() << endl;
            }
        }
        break;

        case 4: {
            recipe.deleteAllIngredients();
            cout << "All ingredients deleted\n";
            break;
        }
        break;

        case 5: {
            string instructions;
            cout << "\nInstructions: ";
            getline(cin, instructions);
            recipe.setInstructions(instructions);
            cout << "Instructions modified\n";
        }
        break;

        default:
            cout << "Invalid option" << endl;
            break;
    }
}

void Interface::saveList(DoublyLinkedList<Recipe>& recipes) {
    string fileName;
    cout << "\nFile name: ";
    getline(cin, fileName);

    try {
        recipes.writeToDisk(fileName);
        cout << "List saved to " << fileName << endl;
    } catch (const DoublyLinkedList<Recipe>::Exception& e) {
        cout << "Error saving list: " << e.what() << endl;
    }
}

void Interface::loadList(DoublyLinkedList<Recipe>& recipes) {
    string fileName;
    cout << "\nFile name: ";
    getline(cin, fileName);

    try {
        recipes.readFromDisk(fileName);
        cout << "List loaded from " << fileName << endl;
    } catch (const DoublyLinkedList<Recipe>::Exception& e) {
        cout << "Error loading list: " << e.what() << endl;
    }
}
