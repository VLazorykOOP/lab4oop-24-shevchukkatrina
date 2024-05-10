#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

// завдання 1
class VectorLong {
private:
    long* ptr;
    int size;
    mutable int codeError; // Зробити codeError змінною

public:
    static int objectCount;

    // Конструктор за замовчуванням
    VectorLong() : ptr(nullptr), size(0), codeError(0) {
        objectCount++;
    }

    // Конструктор з одним параметром - розмір вектора
    VectorLong(int s) : ptr(new long[s]), size(s), codeError(0) {
        for (int i = 0; i < size; ++i)
            ptr[i] = 0;
        objectCount++;
    }

    // Деструктор
    ~VectorLong() {
        delete[] ptr;
        objectCount--;
    }

    // Перегрузка оператора додавання +
    VectorLong operator+(const VectorLong& other) const {
        if (size != other.size) {
            codeError = 1; // Змінено на змінну codeError
            return *this; // Повертаємо не змінений вектор у разі різних розмірів
        }
        VectorLong result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] + other.ptr[i];
        return result;
    }

    // Перегрузка оператора віднімання -
    VectorLong operator-(const VectorLong& other) const {
        if (size != other.size) {
            codeError = 1; // Змінено на змінну codeError
            return *this; // Повертаємо не змінений вектор у разі різних розмірів
        }
        VectorLong result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] - other.ptr[i];
        return result;
    }

    // Перегрузка оператора множення *
    VectorLong operator*(long scalar) const {
        VectorLong result(size);
        for (int i = 0; i < size; ++i)
            result.ptr[i] = ptr[i] * scalar;
        return result;
    }

    // Перегрузка оператора менше рівне <=
    bool operator<=(const VectorLong& other) const {
        for (int i = 0; i < size; ++i) {
            if (ptr[i] > other.ptr[i])
                return false;
        }
        return true;
    }

    // Перегрузка оператора введення >>
    friend std::istream& operator>>(std::istream& in, VectorLong& vector) {
        for (int i = 0; i < vector.size; ++i)
            in >> vector.ptr[i];
        return in;
    }

    // Перегрузка оператора виведення <<
    friend std::ostream& operator<<(std::ostream& out, const VectorLong& vector) {
        for (int i = 0; i < vector.size; ++i)
            out << vector.ptr[i] << " ";
        return out;
    }
};

int VectorLong::objectCount = 0;

