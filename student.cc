#include "student.h"

Student:: Student() {cout << "default constructor called" << endl;}
Student:: Student(const string& n, int a) {
    cout << "parametrized constructor " << endl;
    name = n;
    age = a;
}

Student:: Student(int id) : id_(id){}
Student:: Student(const Student& other) : name(other.name), age(other.age) {cout <<"copy constructor called " << endl;}

 Student& Student:: operator=(const Student& other){
    cout << "assignment opearator called" << endl;
    if (this == &other) {
        return *this;
    }
     name = other.name;
     age = other. age;
     return *this;

 }

ostream& operator<< (ostream& out, const Student& s) {
    out << "ID " << s.id_;
    return out;

}

int main() {
    Student s = 1;
    cout << s << endl;
    // cout << "---- Default constructor ----" << endl;
    // Student s0;                 
    // cout << s0 << endl;

    // cout << "\n---- Parameterized constructor ----" << endl;
    // Student s1("Alice", 20);    
    // cout << s1;

    // cout << "\n---- Copy constructor ----" << endl;
    // Student s2 = s0;   
    // cout << s2;         

    // cout << "\n----  assignment operator ----" << endl;
    // Student s3("Bob", 30);
    // cout << "Before assignment: " << s3 << endl;
    // s3 = s0;                    
    // cout << "After assignment:  " << s3 << endl;

    // cout << "\n---- Self-assignment test ----" << endl;
    // s1 = s1;                    
    // cout << s1 << endl;

    return 0;
}