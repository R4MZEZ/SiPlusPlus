#include <iostream>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <chrono>

template <typename T>
class SparseVector {
private:
    std::unordered_map<size_t, T> data;
    size_t size;

public:
    SparseVector(size_t size) : size(size) {}

    T get(size_t index) const {
        auto it = data.find(index);
        if (it != data.end()) {
            return it->second;
        }
        return T(0);
    }

    void set(size_t index, const T& value) {
        if (value == T(0)) {
            data.erase(index);
        } else {
            data[index] = value;
        }
    }

    size_t getSize() const { return size; }
    void setSize(size_t _size){
        size = _size;
    }
};

template <typename T>
class SparseMatrix {
private:
    std::unordered_map<std::pair<size_t, size_t>, T, std::hash<std::pair<size_t, size_t>>> data;  // Хеш-таблица для хранения элементов
    size_t rows, cols;

public:
    SparseMatrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

    T get(size_t row, size_t col) const {
        auto it = data.find({row, col});
        if (it != data.end()) {
            return it->second;
        }
        return T(0);
    }

    void set(size_t row, size_t col, const T& value) {
        if (value == T(0)) {
            data.erase({row, col});
        } else {
            data[{row, col}] = value;
        }
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    void setSize(size_t _rows, size_t _cols){
        rows = _rows;
        cols = _cols;
    }
};

template <typename T>
SparseMatrix<T>& transpose(SparseMatrix<T>& mat) {
    mat.setSize(mat.getCols(), mat.getRows());
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            T saved = mat.get(j, i);
            mat.set(j,i,mat.get(i,j));
            mat.set(i,j,saved);
        }
    }
    return mat;
}

// Сложение векторов
template <typename T>
SparseVector<T>& add(const SparseVector<T>& v1, SparseVector<T>& v2) {
    size_t size = std::max(v1.getSize(), v2.getSize());
    v2.setSize(size);
    
    for (size_t i = 0; i < size; ++i) {
        v2.set(i, v1.get(i) + v2.get(i));
    }
    return v2;
}

// Умножение матрицы на вектор
template <typename T>
SparseVector<T>& multiply(const SparseMatrix<T>& mat, SparseVector<T>& vec) {
    if (mat.getCols() != vec.getSize()) {
        throw std::invalid_argument("Matrix columns must match vector size");
    }

    vec.setSize(mat.getRows());

    for (size_t i = 0; i < mat.getRows(); ++i) {
        T sum = 0;
        for (size_t j = 0; j < mat.getCols(); ++j) {
            sum += mat.get(i, j) * vec.get(j);
        }
        vec.set(i, sum);
    }
    return vec;
}

// Возведение матрицы в степень
template <typename T>
SparseMatrix<T>& power(const SparseMatrix<T>& mat, int exponent) {
    if (mat.getRows() != mat.getCols()) {
        throw std::invalid_argument("Matrix must be square for exponentiation");
    }
    
    SparseMatrix<T> base = mat;
    while (exponent > 0) {
        mat = multiply(mat, mat);
        exponent -= 1;
    }
    return mat;
}

// Тестирование стандартных векторов
template <typename T>
SparseVector<T> standardVectorAddition(const std::vector<T>& v1, std::vector<T>& v2) {
    size_t size = std::max(v1.size(), v2.size());
    SparseVector<T> result(size);
    for (size_t i = 0; i < size; ++i) {
        result.set(i, (i < v1.size() ? v1[i] : 0) + (i < v2.size() ? v2[i] : 0));
    }
    return result;
}

// Сравнение скорости выполнения операций
void benchmark() {
    const size_t SIZE = 10000;
    
    // Стандартные вектора
    std::vector<int> v1(SIZE, 0), v2(SIZE, 0);
    v1[100] = 5;
    v2[100] = 10;
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = standardVectorAddition(v1, v2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> std_duration = end - start;
    
    std::cout << "Standard vector addition time: " << std_duration.count() << " seconds\n";

    // Разреженные векторы
    SparseVector<int> sparse_v1(SIZE), sparse_v2(SIZE);
    sparse_v1.set(100, 5);
    sparse_v2.set(100, 10);

    start = std::chrono::high_resolution_clock::now();
    auto result2 = add(sparse_v1, sparse_v2);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sparse_duration = end - start;

    std::cout << "Sparse vector addition time: " << sparse_duration.count() << " seconds\n";
}

int main() {
    benchmark();
    return 0;
}
