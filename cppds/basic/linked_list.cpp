#include <iostream>
using namespace std;

// Template for Node class
// Template for Node class
template <typename T>
class Node {
    private:
        T data; // Data of generic type
        Node<T> *next; // Pointer to the next node

    public:
        Node(T initdata) {
            data = initdata;
            next = NULL;
        }

        T getData() const{
            return data;
        }

        Node<T> *getNext() const{
            return next;
        }

        void setData(T newData) {
            data = newData;
        }

        void setNext(Node<T> *newnext) {
            next = newnext;
        }
};

// Template for UnorderedList class
template <typename T>
class UnorderedList {
    private:
        Node<T> *head;

    public:
        UnorderedList() {
            head = NULL;
        }

        Node<T>* getHead() const{
            return head;
        }

        bool isEmpty() const{
            return head == NULL;
        }

        void add(T item) {
            Node<T> *temp = new Node<T>(item);
            temp->setNext(head);
            head = temp;
        }

        int size() const{
            Node<T> *current = head;
            int count = 0;
            while (current != NULL) {
                count++;
                current = current->getNext();
            }
            return count;
        }

        bool search(T item) const{
            Node<T> *current = head;
            while (current != NULL) {
                if (current->getData() == item) {
                    return true;
                }
                current = current->getNext();
            }
            return false;
        }

        void remove(T item) {
            Node<T> *current = head;
            Node<T> *previous = NULL;
            bool found = false;
            while (!found && current != NULL) {
                if (current->getData() == item) {
                    found = true;
                } else {
                    previous = current;
                    current = current->getNext();
                }
            }
            if (found) {
                if (previous == NULL) {
                    head = current->getNext();
                } else {
                    previous->setNext(current->getNext());
                }
                delete current;
            }
        }

        friend ostream& operator<<(ostream& os, const UnorderedList<T>& ol) {
            Node<T> *current = ol.head;
            while (current != NULL) {
                os << current->getData() << " ";
                current = current->getNext();
            }
            return os;
        }
};

// Template for OrderedList class
template <typename T>
class OrderedList {
    private:
        Node<T> *head;

    public:
        OrderedList() {
            head = NULL;
        }

        Node<T>* getHead() const{
            return head;
        }

        bool search(T item) const{
            Node<T> *current = head;
            while (current != NULL) {
                if (current->getData() == item) {
                    return true;
                } else if (current->getData() > item) {
                    return false;
                }
                current = current->getNext();
            }
            return false;
        }

        void add(T item) {
            Node<T> *newNode = new Node<T>(item);
            if (head == NULL || head->getData() >= item) {
                newNode->setNext(head);
                head = newNode;
            } else {
                Node<T> *current = head;
                while (current->getNext() != NULL && current->getNext()->getData() < item) {
                    current = current->getNext();
                }
                newNode->setNext(current->getNext());
                current->setNext(newNode);
            }
        }

        bool isEmpty() const{
            return head == NULL;
        }

        int size() const{
            Node<T> *current = head;
            int count = 0;
            while (current != NULL) {
                count++;
                current = current->getNext();
            }
            return count;
        }

        friend ostream& operator<<(ostream& os, const OrderedList<T>& ol) {
            Node<T> *current = ol.head;
            while (current != NULL) {
                os << current->getData() << " ";
                current = current->getNext();
            }
            return os;
        }
};