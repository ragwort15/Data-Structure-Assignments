#include <iostream>
#include "library.h"
using std::cout;
using std::endl;

int main() {
    cout << "===== Test Case 1: Book Class Initialization =====" << endl;
    Book b("The Hobbit", "J.R.R. Tolkien", 101);
    cout << "Title: " << b.getTitle() << endl;
    cout << "Available: " << b.isAvailable() << endl;

    cout << "\n===== Test Case 2: Book Operator Overloading =====" << endl;
    Book b1("A", "B", 101);
    Book b2("C", "D", 101);
    cout << "b1 == b2: " << (b1 == b2 ? "true" : "false") << endl;

    cout << "\n===== Test Case 3: User Class Borrow Logic =====" << endl;
    User u("Patel");
    cout << "Before borrowing:" << endl;
    cout << u << endl;
    u.borrow(b1);
    cout << "After borrowing:" << endl;
    cout << u << endl;

    cout << "\n===== Test Case 4: User Operator Overloading =====" << endl;
    cout << u << endl;

    cout << "\n===== Test Case 5: Library Add & Search Books =====" << endl;
    Library lib;
    lib.addBook("Art of the Deal", "DJ Trump");
    lib.addBook("C++", "Deitel");
    int bookId = lib.getBookIdByTitle("Art of the Deal");
    cout << "Book ID for 'Art of the Deal': " << bookId << endl;

    cout << "\n===== Test Case 6: Library Add & Search Users =====" << endl;
    // FIX: add by name; the library owns the User object
    lib.addUser("Patel");
    int userId = lib.getUserIdByName("Patel");
    cout << "User ID for Patel: " << userId << endl;

    cout << "\n===== Test Case 7: Library Checkout Transaction =====" << endl;
    lib.checkoutBook(userId, bookId);
    cout << "Library after checkout:" << endl;
    cout << lib << endl;

    cout << "\n===== Test Case 8: Library Return Transaction =====" << endl;
    lib.returnBook(userId, bookId);
    cout << "Library after return:" << endl;
    cout << lib << endl;

    cout << "\n===== Test Case 9: Library Operator Overloading =====" << endl;
    cout << "Full Library Inventory:" << endl;
    cout << lib << endl;

    return 0;
}