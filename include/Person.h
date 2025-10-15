#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// Base class demonstrating inheritance
class Person {
protected:
    string name;
    string phoneNumber;
    int id;
    static int nextId;

public:
    // Multiple constructors demonstrating constructor overloading
    Person();
    Person(string name, string phone);
    Person(const Person& other); // Copy constructor
    
    // Virtual destructor for proper cleanup
    virtual ~Person();
    
    // Getters
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    int getId() const { return id; }
    
    // Setters demonstrating encapsulation
    void setName(string n) { name = n; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    
    // Pure virtual function for polymorphism
    virtual void displayInfo() const = 0;
};

#endif
