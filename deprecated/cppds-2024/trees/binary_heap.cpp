#include <iostream>
#include <vector>
#include <stdexcept> // for std::underflow_error

template<typename T>
class BinHeap {
private:
    std::vector<T> heapvector;
    int currentSize;

    void percUp(int i) {
        while (i / 2 > 0) {
            int parent = i / 2;
            if (heapvector[i] < heapvector[parent]) {
                std::swap(heapvector[i], heapvector[parent]);
            }
            i = parent;
        }
    }

    void percDown(int i) {
        while (i * 2 <= currentSize) {
            int mc = minChild(i);
            if (heapvector[i] > heapvector[mc]) {
                std::swap(heapvector[i], heapvector[mc]);
            }
            i = mc;
        }
    }

    int minChild(int i) const {
        if (i * 2 + 1 > currentSize) {
            return i * 2;
        } else {
            return heapvector[i * 2] < heapvector[i * 2 + 1] ? i * 2 : i * 2 + 1;
        }
    }

public:
    BinHeap() : currentSize(0) {
        heapvector.push_back(T());  // Dummy element at index 0 for easier indexing
    }

    void insert(const T& item) {
        if (currentSize + 1 >= heapvector.size()) {
            heapvector.push_back(item);
        } else {
            heapvector[currentSize + 1] = item;
        }
        currentSize++;
        percUp(currentSize);
    }

    T delMin() {
        if (isEmpty()) {
            throw std::underflow_error("Heap is empty");
        }
        T minItem = heapvector[1];
        heapvector[1] = heapvector[currentSize];
        heapvector.pop_back();
        currentSize--;
        if (!isEmpty()) {
            percDown(1);
        }
        return minItem;
    }

    void buildHeap(const std::vector<T>& avector) {
        heapvector.resize(avector.size() + 1);
        for (int i = 0; i < avector.size(); i++) {
            heapvector[i + 1] = avector[i];
        }
        currentSize = avector.size();
        for (int i = currentSize / 2; i > 0; i--) {
            percDown(i);
        }
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    T findMin() const {
        if (isEmpty()) {
            throw std::underflow_error("Heap is empty");
        }
        return heapvector[1];
    }
};

template<typename K>
class PriorityQueue : public BinHeap<std::pair<int, K>> {
public:
    void insert(int priority, const K& item) {
        this->BinHeap<std::pair<int, K>>::insert(std::make_pair(priority, item));
    }

    std::pair<int, K> delMin() {
        std::pair<int, K> minPair = this->BinHeap<std::pair<int, K>>::delMin();
        return minPair;
    }

    void changePriority(const K& item, int newPriority) {
        for (int i = 1; i <= this->currentSize; i++) {
            if (this->heapvector[i].second == item) {
                this->heapvector[i].first = newPriority;
                this->percUp(i);
                this->percDown(i);
                break;
            }
        }
    }

    bool contains(const K& item) const {
        for (int i = 1; i <= this->currentSize; i++) {
            if (this->heapvector[i].second == item) {
                return true;
            }
        }
        return false;
    }
};