#include "library.h"
#include <iostream>
#include <algorithm>
using std::endl;

Book::Book(string t, string a, int id)
    : title_(t), author_(a), id_(id), checkedOut_(false) {}

Book::Book(const Book& other)
    : title_(other.title_), author_(other.author_),
      id_(other.id_), checkedOut_(other.checkedOut_) {}

Book::~Book() = default;

void Book::checkout()    { checkedOut_ = true;  }
void Book::returnBook()  { checkedOut_ = false; }
bool Book::isAvailable() const { return !checkedOut_; }
string Book::getTitle()  const { return title_;  }
string Book::getAuthor() const { return author_; }
int    Book::getId()     const { return id_;     }

bool Book::operator==(const Book& other) const {
    return id_ == other.id_;
}

User::User(string name) : name_(name) {}

string User::getName() const { return name_; }

void User::borrow(Book& b) {
    if (!b.isAvailable()) return;
    b.checkout();
    borrowedBooks_.push_back(&b);
}

void User::returnBook(Book& b) {
    auto it = std::find(borrowedBooks_.begin(), borrowedBooks_.end(), &b);
    if (it == borrowedBooks_.end()) return;
    b.returnBook();
    borrowedBooks_.erase(it);
}

std::ostream& operator<<(std::ostream& lhs, const User& rhs) {
    lhs << "User: " << rhs.name_ << std::endl;
    for (const Book* b : rhs.borrowedBooks_) {
        lhs << "  - " << b->getTitle() << std::endl;
    }
    return lhs;
}

void Library::addBook(const string& title, const string& author) {
    if (inventory_.capacity() == inventory_.size()) {
        inventory_.reserve(inventory_.size() + 16);
    }
    int id = inventory_.size();
    inventory_.push_back(Book(title, author, id));
}

void Library::addUser(const string& name) {
    users_.push_back(User(name));
}

Book* Library::findBook(int id) {
    for (auto& b : inventory_) {
        if (b.getId() == id) return &b;
    }
    return nullptr;
}

int Library::getBookIdByTitle(const string& title) const {
    for (const auto& b : inventory_) {
        if (b.getTitle() == title) return b.getId();
    }
    return -1;
}

int Library::getUserIdByName(const std::string& name) const {
    for (int i = 0; i < (int)users_.size(); i++) {
        if (users_[i].getName() == name) return i;
    }
    return -1;
}

void Library::checkoutBook(int user_id, int book_id) {
    Book* b = findBook(book_id);
    if (b == nullptr) return;
    users_[user_id].borrow(*b);
}

void Library::returnBook(int user_id, int book_id) {
    Book* b = findBook(book_id);
    if (b == nullptr) return;
    users_[user_id].returnBook(*b);
}

std::ostream& operator<<(std::ostream& lhs, const Library& rhs) {
    for (const auto& b : rhs.inventory_) {
        lhs << b.getTitle() << ": ";
        lhs << (b.isAvailable() ? "Available!" : "Checked Out");
        lhs << endl;
    }
    return lhs;
}