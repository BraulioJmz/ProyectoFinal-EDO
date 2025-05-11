#ifndef __LISTASIMPLEMENTELIGADA_HPP__
#define __LISTASIMPLEMENTELIGADA_HPP__

#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

template <class T>
class SimpleLinkedList {
class Node;

public:
    typedef Node* Position;

private:
    class Node {
    private:
        T data;
        Position next = nullptr;

    public:
        Node();
        Node(const T&);

        T& getData();
        Position getNext();

        void setData(const T&);
        void setNext(const Position&);
    };

    Position anchor = nullptr;

    bool isValid(const Position&) const;

    void copyAll(const SimpleLinkedList<T>&);

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

    SimpleLinkedList();
    SimpleLinkedList(const SimpleLinkedList<T>&);
    ~SimpleLinkedList();

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
    
    string toString() const;
    
    void deleteAll();

    Position getPos(const int&) const; 
    
    SimpleLinkedList<T>& operator=(const SimpleLinkedList<T>&);

};

template <class T>
SimpleLinkedList<T>::Node::Node() {}

template <class T>
SimpleLinkedList<T>::Node::Node(const T& e) : data(e) { }

template <class T>  
T& SimpleLinkedList<T>::Node::getData() {  //Quizas cambiar tipo de dato que regresa
    return this->data;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::Node::getNext() {
    return this->next;
}

template <class T>
void SimpleLinkedList<T>::Node::setData(const T& e) {
    this->data = e;
}

template <class T>
void SimpleLinkedList<T>::Node::setNext(const Position& p) {
    this->next = p;
}

template <class T>
bool SimpleLinkedList<T>::isValid(const Position& p) const {
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
void SimpleLinkedList<T>::copyAll(const SimpleLinkedList<T>& other) {
    Position aux(other.anchor), lastInserted(this -> getLastPos()), newNode;

    if(aux != nullptr) {
        if((newNode = new(nothrow) Node(aux -> getData())) == nullptr) {
            throw Exception("Memory not available, addData");
        }

        if(lastInserted == nullptr) {
            this -> anchor = newNode;
        }
        else {
            lastInserted -> setNext(newNode);
        }

        lastInserted = newNode;
        aux = aux -> getNext();
    }
}

template <class T>
SimpleLinkedList<T>::SimpleLinkedList() : anchor(nullptr){}

template <class T>
SimpleLinkedList<T>::SimpleLinkedList(const SimpleLinkedList<T>& l) {
    copyAll(l);
}

template <class T>
SimpleLinkedList<T>::~SimpleLinkedList() {
    deleteAll();
}

template <class T>
bool SimpleLinkedList<T>::isEmpty() const {
    return this -> anchor == nullptr;
}

template <class T>
void SimpleLinkedList<T>::insertData(const Position& p, const T& e) {
    if (p != nullptr and !this -> isValid(p)) {
        throw Exception("Invalid position, insertData");
    }

    Position newNode(new(nothrow) Node(e));

    if(newNode == nullptr) {
        throw Exception("Memory not available, insertData");
    }

    if(p == nullptr) {  
        newNode -> setNext(this -> anchor);
        this -> anchor = newNode;
    }
    else { 
        newNode -> setNext(p -> getNext());
        p -> setNext(newNode);
    }
}

template <class T>
void SimpleLinkedList<T>::deleteData(const Position& p) {
    if(!this -> isValid(p)) {
        throw Exception("Invalid position, deleteData");
    }

    if(p == this -> anchor) {
        this -> anchor = p -> getNext();
    }
    else {
        this -> getPrevPos(p) -> setNext(p -> getNext());
    }

    delete p;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getFirstPos() const {
    return this -> anchor;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getLastPos() const {
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
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getPrevPos(const Position& p) const {
    Position aux(this -> anchor);

    while(aux != nullptr and aux -> getNext() != p) {
        aux = aux -> getNext();
    }

    return aux;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getNextPos(const Position& p) const {
    return this -> isValid(p) ? p -> getNext() : nullptr;
}

template <class T>
T& SimpleLinkedList<T>::retrieve(const Position& p) {
    if(!this -> isValid(p)) {
        throw Exception("Invalid position, retrieve");
    }

    return p -> getData();
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::findDataL(const T& e) const {
    Position aux(this -> anchor);

    while(aux != nullptr and aux -> getData() != e) {
        aux = aux -> getNext();
    }

    return aux;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::findData(const T& e, int (*compare)(const T*, const T*)) const {
    Position aux(this -> anchor);

    while(aux != nullptr and compare(&aux -> getData(), &e) != 0) {
        aux = aux -> getNext();
    }

    return aux;
}

template <class T>
string SimpleLinkedList<T>::toString() const {
    string result;
    Position aux(this -> anchor);

    while(aux != nullptr) {
        result += aux->getData().toString() + "\n";

        aux = aux -> getNext();
    }

    return result;
}

template <class T>
void SimpleLinkedList<T>::deleteAll() {
    Position aux;

    while(this -> anchor != nullptr) {
        aux = this -> anchor;
        this -> anchor = aux -> getNext();
        delete aux;
    }
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getPos(const int& index) const{
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
SimpleLinkedList<T>& SimpleLinkedList<T>::operator = (const SimpleLinkedList<T>& l) {
    this -> deleteAll();
    copyAll(l);
    return *this;
}

#endif