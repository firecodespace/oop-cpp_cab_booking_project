#include "../include/Person.h"
#include <iostream>

int Person::nextId = 1;

Person::Person() : name(""), phoneNumber(""), id(nextId++) {
    cout << "Person default constructor called" << endl;
}

Person::Person(string name, string phone) 
    : name(name), phoneNumber(phone), id(nextId++) {
    cout << "Person parameterized constructor called for " << name << endl;
}

Person::Person(const Person& other) 
    : name(other.name), phoneNumber(other.phoneNumber), id(nextId++) {
    cout << "Person copy constructor called" << endl;
}

Person::~Person() {
    cout << "Person destructor called for " << name << endl;
}
