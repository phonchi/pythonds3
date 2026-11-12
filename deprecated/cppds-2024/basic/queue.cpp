#include <iostream>

template<typename T>
class Queue {
private:
    int front;
    int rear;
    int size;
    T* Q; // Queue now holds generic type T

public:
    Queue(int size = 10) : front(-1), rear(-1), size(size) {
        Q = new T[this->size];
    }

    ~Queue() {
        delete[] Q;
    }

    void enqueue(T x) {
        if (rear == size - 1) {
            std::cout << "Queue is Full" << std::endl;
        } else {
            Q[++rear] = x;
        }
    }

    T dequeue() {
        T x = nullptr;  // Adjusted for generic type, nullptr for pointer types
        if (front == rear) {
            std::cout << "Queue is Empty" << std::endl;
        } else {
            x = Q[++front];
        }
        return x;
    }

    bool isEmpty() {
        return front == rear;
    }

    void display() {
        for (int i = front + 1; i <= rear; i++)
            std::cout << Q[i] << " ";
        std::cout << std::endl;
    }
};
