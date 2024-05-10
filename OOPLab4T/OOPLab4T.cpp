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

// завдання 2


class Association {
private:
    std::map<std::string, std::map<std::string, std::string>> data;

public:
    std::map<std::string, std::string>& operator[](const std::string& key) {
        return data[key];
    }

    std::string& operator()(const std::string& key1, const std::string& key2) {
        return data[key1][key2];
    }

    const std::map<std::string, std::string>& operator[](const std::string& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        else {
            throw std::out_of_range("Key not found");
        }
    }

    const std::string& operator()(const std::string& key1, const std::string& key2) const {
        auto it1 = data.find(key1);
        if (it1 != data.end()) {
            auto it2 = it1->second.find(key2);
            if (it2 != it1->second.end()) {
                return it2->second;
            }
        }
        throw std::out_of_range("Keys not found");
    }

    void print() const {
        for (const auto& entry : data) {
            std::cout << "Email: " << entry.first << std::endl;
            for (const auto& info : entry.second) {
                std::cout << info.first << ": " << info.second << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Введення розмірів та значень першого вектора
    int size1;
    std::cout << "Enter the size of the first vector: ";
    std::cin >> size1;
    VectorLong vector1(size1);
    std::cout << "Enter the elements of the first vector: ";
    std::cin >> vector1;

    // Введення розмірів та значень другого вектора
    int size2;
    std::cout << "Enter the size of the second vector: ";
    std::cin >> size2;
    VectorLong vector2(size2);
    std::cout << "Enter the elements of the second vector: ";
    std::cin >> vector2;

    // Додавання векторів
    VectorLong sum = vector1 + vector2;
    std::cout << "Sum of vectors: " << sum << std::endl;

    // Віднімання векторів
    VectorLong diff = vector1 - vector2;
    std::cout << "Difference of vectors: " << diff << std::endl;

    // Множення першого вектора на число
    long scalar;
    std::cout << "Enter a scalar value for multiplication: ";
    std::cin >> scalar;
    VectorLong product = vector1 * scalar;
    std::cout << "Product of vector1 and scalar: " << product << std::endl;

    // Перевірка на менше рівне
    if (vector1 <= vector2) {
        std::cout << "Vector1 is less than or equal to vector2." << std::endl;
    }
    else {
        std::cout << "Vector1 is greater than vector2." << std::endl;
    }
    // завдання 2
    Association associations;
    associations["katerynka@gmail.com"]["last_name"] = "Shevchuk";
    associations["katerynka@gmail.com"]["first_name"] = "Kateryna";
    associations["katerynka@gmail.com"]["middle_name"] = "Mykhailivna";

    associations.print();


    return 0;
}