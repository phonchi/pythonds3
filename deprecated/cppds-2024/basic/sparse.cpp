#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <stdexcept>

class SparseMatrix {
public:
    // Constructor
    SparseMatrix() {}

    // Method to create a sparse matrix from a dense matrix
    void fromDenseMatrix(const std::vector<std::vector<double>>& matrix) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] != 0) {
                    data[{i, j}] = matrix[i][j];
                }
            }
        }
    }

    // Overload subscript operator for accessing elements
    double& operator()(size_t i, size_t j) {
        return data[{i, j}];
    }

    double operator()(size_t i, size_t j) const {
        auto it = data.find({i, j});
        if (it != data.end()) {
            return it->second;
        }
        return 0.0;
    }

    // Overload addition operator
    SparseMatrix operator+(const SparseMatrix& other) const {
        SparseMatrix result;
        for (const auto& item : data) {
            result.data[item.first] = item.second + other(item.first.first, item.first.second);
        }
        for (const auto& item : other.data) {
            if (data.find(item.first) == data.end()) {
                result.data[item.first] = item.second;
            }
        }
        return result;
    }

    // Overload subtraction operator
    SparseMatrix operator-(const SparseMatrix& other) const {
        SparseMatrix result;
        for (const auto& item : data) {
            result.data[item.first] = item.second - other(item.first.first, item.first.second);
        }
        for (const auto& item : other.data) {
            if (data.find(item.first) == data.end()) {
                result.data[item.first] = -item.second;
            }
        }
        return result;
    }

    // Overload multiplication operator
    SparseMatrix operator*(const SparseMatrix& other) const {
        SparseMatrix result;
        for (const auto& item1 : data) {
            for (const auto& item2 : other.data) {
                if (item1.first.second == item2.first.first) {
                    result(item1.first.first, item2.first.second) += item1.second * item2.second;
                }
            }
        }
        return result;
    }

    // Overload scalar multiplication
    SparseMatrix operator*(double scalar) const {
        SparseMatrix result;
        for (const auto& item : data) {
            result.data[item.first] = item.second * scalar;
        }
        return result;
    }

    friend SparseMatrix operator*(double scalar, const SparseMatrix& matrix) {
        return matrix * scalar;
    }

    // Overload scalar division
    SparseMatrix operator/(double scalar) const {
        if (scalar == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        SparseMatrix result;
        for (const auto& item : data) {
            result.data[item.first] = item.second / scalar;
        }
        return result;
    }

    // Overload equality operator
    bool operator==(const SparseMatrix& other) const {
        return data == other.data;
    }

    // Overload inequality operator
    bool operator!=(const SparseMatrix& other) const {
        return data != other.data;
    }

    // Overload output stream operator for printing
    friend std::ostream& operator<<(std::ostream& os, const SparseMatrix& matrix) {
        for (const auto& item : matrix.data) {
            os << "(" << item.first.first << ", " << item.first.second << ") = " << item.second << std::endl;
        }
        return os;
    }

    // Additional methods for other operations can be implemented similarly

private:
    std::map<std::pair<size_t, size_t>, double> data;
};