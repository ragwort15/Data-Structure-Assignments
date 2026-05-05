#ifndef LIBRARY_H
#define LIBRARY_H
#include <iosfwd>
#include <vector>
#include <string>
using std::string;
using std::vector;

class Book {
private:
    int id_;
    std::string title_;
    std::string author_;
    bool checkedOut_;

public:
    Book(string t, string a, int id);
    Book(const Book& other);
    virtual ~Book();
    void checkout();
    void returnBook();
    bool isAvailable() const;
    string getTitle() const;
    string getAuthor() const;
    int getId() const;
    bool operator==(const Book& other) const;
};

class User {
private:
    std::string name_;
    vector<Book*> borrowedBooks_;
public:
    User(string name);
    string getName() const;
    void borrow(Book& b);
    void returnBook(Book& b);
    friend std::ostream& operator<<(std::ostream& out, const User& other);
};

class Library {
private:
    vector<Book> inventory_;
    vector<User> users_;

public:
    void addBook(const string& title, const string& author);
    void addUser(const string& name); // FIX: take name, construct internally
    Book* findBook(int id);
    int getBookIdByTitle(const string& title) const;
    int getUserIdByName(const std::string& name) const;
    void checkoutBook(int user_id, int book_id);
    void returnBook(int user_id, int book_id);
    friend std::ostream& operator<<(std::ostream& lhs, const Library& rhs);
};

#endif