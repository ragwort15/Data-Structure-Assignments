#ifndef BOOK_H
#define BOOK_H
#include<string>

class Book {
    public:
    Book(string t, string a, int id);
    Book(const Book& other);
    int getId() const ;
    string getTitle() const;
    bool isAvailable();
    ~Book();
    void returnBook(); 
    bool checkout();
        
    

    private:
    string title_;
    string author_;
    int id_;
    bool checkedOut_;

};

#endif
