#ifndef __LISTADOBLEMENTELIGADA_HPP__
#define __LISTADOBLEMENTELIGADA_HPP__

#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

template <class T>
class DoublyLinkedList {
class Node;

public:
    typedef Node* Position;

private:
    class Node {
    private:
        T data;
        Position next = nullptr;
        Position prev = nullptr;

    public:
        Node();
        Node(const T&);

        T& getData();
        Position getNext();
        Position getPrev();

        void setData(const T&);
        void setNext(const Position&);
        void setPrev(const Position&);
    };

    Position anchor = nullptr;

    bool isValid(const Position&) const;

    void copyAll(const DoublyLinkedList<T>&);

public:
    class Exception : public std::exception {
    private:
        string msg;

    public:
        Exception()noexcept: msg("ERROR"){};
        Exception(const Exception &ex) noexcept: msg(ex.msg){}
        Exception(const std::string&m):msg(m){}
        Exception &operator=(const Exception &ex) noexcept
        {
            msg = ex.msg;
            return *this;
        }
        virtual ~Exception() {}
        virtual const char *what() const noexcept{
            return this->msg.c_str();
        }
    };

    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();

    bool isEmpty() const;

    void insertData(const Position&, const T&);
    
    void deleteData(const Position&);
    
    Position getFirstPos() const;
    
    Position getLastPos() const;
    
    Position getPrevPos(const Position&) const;
    
    Position getNextPos(const Position&) const;

    Position findDataL(const T&) const; 
    
    Position findData(const T&, int (*compare)(const T*, const T*)) const;

    T& retrieve(const Position&);

    void sortDataQuick(bool (*compare)(const T&, const T&));
    void quickSortRec(Position left, Position right, bool (*compare)(const T&, const T&));
    Position partition(Position left, Position right, bool (*compare)(const T&, const T&));

    void writeToDisk(const string&);
    void readFromDisk(const string&);
    
    string toString() const;
    string toStringResume() const; 
    
    void deleteAll();

    Position getPos(const int&) const; 
    
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);

    T& operator[](const int&); //Implementar con vector

};

template <class T>
DoublyLinkedList<T>::Node::Node() {}

template <class T>
DoublyLinkedList<T>::Node::Node(const T& e) : data(e) { }

template <class T>  
T& DoublyLinkedList<T>::Node::getData() {  //Quizas cambiar tipo de dato que regresa
    return this->data;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::Node::getNext() {
    return this->next;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::Node::getPrev() {
    return this->prev;
}

template <class T>
void DoublyLinkedList<T>::Node::setData(const T& e) {
    this->data = e;
}

template <class T>
void DoublyLinkedList<T>::Node::setNext(const Position& p) {
    this->next = p;
}

template <class T>
void DoublyLinkedList<T>::Node::setPrev(const Position& p) {
    this->prev = p;
}

template <class T>
bool DoublyLinkedList<T>::isValid(const Position& p) const {
    Position aux(this -> anchor);

    while(aux != nullptr) {
        if(aux == p) {
            return true;
        }

        aux = aux -> getNext();
    }

    return false;
}

template <class T>
void DoublyLinkedList<T>::copyAll(const DoublyLinkedList<T>& other) {
    Position aux(other.anchor), lastInserted(this -> getLastPos()), newNode;

    while(aux != nullptr) {
        if((newNode = new(nothrow) Node(aux -> getData())) == nullptr) {
            throw Exception("Memory not available, addData");
        }

        if(lastInserted == nullptr) {
            this -> anchor = newNode;
        }
        else {
            lastInserted -> setNext(newNode);
            newNode->setPrev(lastInserted); 
        }

        lastInserted = newNode;
        aux = aux -> getNext();
        
    }
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : anchor(nullptr){}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& l) {
    copyAll(l);
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    deleteAll();
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() const {
    return this -> anchor == nullptr;
}

template <class T>
void DoublyLinkedList<T>::insertData(const Position& p, const T& e) {
    if (p != nullptr and !this -> isValid(p)) {
        throw Exception("Invalid position, insertData");
    }

    Position newNode(new(nothrow) Node(e));

    if(newNode == nullptr) {
        throw Exception("Memory not available, insertData");
    }

    if(p == nullptr) {  // Insertar al inicio
        newNode -> setNext(this -> anchor);
        
        if(anchor != nullptr) {
            this -> anchor -> setPrev(newNode);
        }
        this -> anchor = newNode;
    }
    else { // Insertar en cualquier otra posición
        newNode -> setPrev(p); 
        newNode -> setNext(p -> getNext());

        if(p -> getNext() != nullptr) {
            p -> getNext() -> setPrev(newNode);
        }
        p -> setNext(newNode);
    }
}

template <class T>
void DoublyLinkedList<T>::deleteData(const Position& p) {
    if(!this -> isValid(p)) {
        throw Exception("Invalid position, deleteData");
    }

    if(p->getPrev() != nullptr) {
        p -> getPrev() -> setNext(p -> getNext());
    }
    if(p -> getNext() != nullptr) {
        p -> getNext() -> setPrev(p -> getPrev());
    }

    if(p == this -> anchor) {
        this -> anchor = p -> getNext();
    }

    delete p;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::getFirstPos() const {
    return this -> anchor;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::getLastPos() const {
    if(this -> isEmpty()) {
        return nullptr;
    }
    
    Position aux(this -> anchor);

    while(aux -> getNext() != nullptr) {
        aux = aux -> getNext();
    }

    return aux;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::getPrevPos(const Position& p) const {
    return this -> isValid(p) ? p -> getPrev() : nullptr;
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::getNextPos(const Position& p) const {
    return this -> isValid(p) ? p -> getNext() : nullptr;
}

template <class T>
T& DoublyLinkedList<T>::retrieve(const Position& p) {
    if(!this -> isValid(p)) {
        throw Exception("Invalid position, retrieve");
    }

    return p -> getData();
}

template <class T>
void DoublyLinkedList<T>::sortDataQuick(bool (*compare)(const T&, const T&)) {
    if (this->isEmpty() || this->anchor->getNext() == nullptr) {
        return;
    }
    quickSortRec(this->anchor, getLastPos(), compare);
}

template <class T>
void DoublyLinkedList<T>::quickSortRec(Position left, Position right, bool (*compare)(const T&, const T&)) {
    if (left != right && left != nullptr && right != nullptr && left != right->getNext()) {
        Position pivot = partition(left, right, compare);
        quickSortRec(left, pivot->getPrev(), compare);
        quickSortRec(pivot->getNext(), right, compare);
    }
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::partition(Position left, Position right, bool (*compare)(const T&, const T&)) {
    T pivotData = right->getData();
    Position i = left->getPrev();
    for (Position j = left; j != right; j = j->getNext()) {
        if (compare(j->getData(), pivotData)) {
            i = (i == nullptr) ? left : i->getNext();
            std::swap(i->getData(), j->getData());
        }
    }
    i = (i == nullptr) ? left : i->getNext();
    std::swap(i->getData(), right->getData());
    return i;
}

template <class T>
void DoublyLinkedList<T>::writeToDisk(const string& fileName) {
    ofstream myFile(fileName, ios_base::trunc);

    if (!myFile.is_open()) {
        throw Exception("The file can't be opened for writing");
    }

    Position aux = this->anchor;

    while (aux != nullptr) {
        myFile << aux->getData() << '\n';
        aux = aux->getNext();
    }

    myFile.close();
}

template <class T>
void DoublyLinkedList<T>::readFromDisk(const string& fileName) {
    ifstream myFile;
    string myStr;
    T myObjeto;

    myFile.open(fileName);
    if (!myFile.is_open()) {
        throw Exception("The file can't be opened for reading");
    }

    this->deleteAll();

    while (getline(myFile, myStr)) {
        if (myStr.empty()) {
            continue;
        }

        stringstream mySStream(myStr);
        mySStream >> myObjeto;

        this->insertData(this->getLastPos(), myObjeto);
    }

    myFile.close();
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::findDataL(const T& e) const {
    Position aux(this->anchor);

    while (aux != nullptr) {
        if (aux->getData() == e) {
            return aux;
        }
        aux = aux->getNext();
    }

    return nullptr; 
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::findData(const T& e, int (*compare)(const T*, const T*)) const {
    Position aux(this->anchor);

    while (aux != nullptr) {
        if (compare(&aux->getData(), &e) == 0) {
            return aux;
        }
        aux = aux->getNext();
    }

    return nullptr; 
}

template <class T>
string DoublyLinkedList<T>::toString() const {
    string result;
    Position aux(this -> anchor);

    while(aux != nullptr) {
        result += aux->getData().toString() + "\n";

        aux = aux -> getNext();
    }

    return result;
}

template <class T>
string DoublyLinkedList<T>::toStringResume() const {
    string result;
    Position aux(this -> anchor);

    while(aux != nullptr) {
        result += aux->getData().toStringResume() + "\n";

        aux = aux -> getNext();
    }

    return result;
}

template <class T>
void DoublyLinkedList<T>::deleteAll() {
    Position aux;

    while(this -> anchor != nullptr) {
        aux = this -> anchor;
        this -> anchor = aux -> getNext();
        delete aux;
    }
}

template <class T>
typename DoublyLinkedList<T>::Position DoublyLinkedList<T>::getPos(const int& index) const{
    if(index < 0){
        throw Exception("Invalid index, getPos"); 
    }

    Position aux = this -> anchor; 
    int count = 0; 

    while(aux != nullptr && count != index){
        aux = aux -> getNext(); 
        count++; 
    }

    if(aux == nullptr && count != index){
        throw Exception("Index out of range, getPos"); 
    }

    return aux; 
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const DoublyLinkedList<T>& l) {
    this -> deleteAll();
    addData(l);
    return *this;
}

#endif // __LISTADOBLEMENTELIGADA_HPP__