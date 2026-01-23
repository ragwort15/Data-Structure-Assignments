#include "CircularLinkedList.h"
#include <stdexcept>

CircularLinkedList::CircularLinkedList() {
    this->head = nullptr;
    this->count = 0;
}

CircularLinkedList::~CircularLinkedList() {
    while (count > 0) {
        pop(ClockWise);
    }
}

void CircularLinkedList::push(int value, ClockDirection d) {
    Node* newNode = new Node(value);

    if (!head) {
        
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else if (d == ClockWise) {
        
        Node* after = head->next;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = after;
        after->prev = newNode;
    } else {
        
        Node* before = head->prev;
        before->next = newNode;
        newNode->prev = before;
        newNode->next = head;
        head->prev = newNode;
    }

    count++;
}

int CircularLinkedList::pop(ClockDirection d) {
    if (!head) {
        throw std::runtime_error("List is empty");
    }

    int value = head->value;

    if (head->next == head) {
    
        delete head;
        head = nullptr;
    } else {
        Node* toDelete = head;
        Node* newHead;
        if (d == ClockWise) {
            newHead = head->next;
        } else {
            newHead = head->prev;
        }

        head->prev->next = head->next;
        head->next->prev = head->prev;

        head = newHead;
        delete toDelete;
    }

    count--;
    return value;
}


int CircularLinkedList::peek() const {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    return head->value;
}

void CircularLinkedList::rotate(unsigned int n, ClockDirection d) {
    if (!head) { 
        return;
    }
    for (unsigned int i = 0; i < n; ++i) {
        head = (d == ClockWise) ? head->next : head->prev;
    }
}

// std::cout << "Circular linked list: " << list << std::endl;
std::ostream& operator<<(std::ostream& os, const CircularLinkedList& list) {
    if (!list.head) {
        os << "{ }";
        return os;
    }

    os << "{ ";
    Node* current = list.head;
    do {
        os << current->value;
        current = current->next;
        if (current != list.head) {
            os << ", ";
        }
    } while (current != list.head);
    os << " }";
    return os;
}
