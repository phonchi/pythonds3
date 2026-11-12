#include <iostream>
using namespace std;

template<typename T>
class Stack {
private:
    int size;
    int top;
    T* S; // Use template type for the stack elements

public:
    Stack(int size);
    ~Stack();
    void push(T x);
    T pop();
    T peek(int index) const;
    bool isFull() const;
    bool isEmpty() const;
    void display() const;
    T stackTop() const;
};

template<typename T>
Stack<T>::Stack(int size) {
    this->size = size;
    top = -1;
    S = new T[size]; // Dynamically allocate array of template type
}

template<typename T>
Stack<T>::~Stack() {
    delete[] S;
}

template<typename T>
void Stack<T>::push(T x) {
    if (isFull()) {
        cout << "Stack Overflow!" << endl;
    } else {
        S[++top] = x;
    }
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow!" << endl;
        return T(); // Return default-constructed value for type T
    } else {
        return S[top--];
    }
}

template<typename T>
T Stack<T>::peek(int index) const {
    if (index < 0 || index > top) {
        cout << "Invalid position!" << endl;
        return T(); // Return default-constructed value for type T
    } else {
        return S[top - index];
    }
}

template<typename T>
bool Stack<T>::isFull() const {
    return top == size - 1;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return top == -1;
}

template<typename T>
void Stack<T>::display() const {
    for (int i = top; i >= 0; i--) {
        cout << S[i] << " | ";
    }
    cout << endl;
}

template<typename T>
T Stack<T>::stackTop() const {
    if (!isEmpty()) {
        return S[top];
    } else {
        return T(); // Return default-constructed value for type T
    }
}
