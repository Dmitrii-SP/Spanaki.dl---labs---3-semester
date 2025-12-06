#include <iostream>
#include <random>
#include <chrono>

// ваш код здесь
template <typename T>
class subvector {
// public поля в классе с инвариантами?
public:
    T* mas;
    int top;
    int capacity;

    subvector() {
        mas = nullptr;
        top = 0;
        capacity = 0;
    }

    ~subvector() {
        // delete[] nullptr -- это корректная операция, не нужно проверять перед удалением
        if (mas != nullptr) delete[] mas;
    }

    void push_back(T item) {
        if (top == capacity) {
            // тот же самый код, что и в resize. нужно здесь его переиспользовать, чтобы не плодить
            // ошибки типа "тут исправил -- там забыл"
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_mas = new T[new_capacity];

            for (int i = 0; i < top; i++) new_mas[i] = mas[i];

            if (mas != nullptr) delete[] mas;

            mas = new_mas;
            capacity = new_capacity;
        }
        
        mas[top] = item;
        top++;
    }

    T pop_back() {
        if (top > 0) return mas[--top];
        return T{};
    }

// resize должен изменять capacity (емкость вектора) в нашем случае
// пока что в функции происходит не это. посмотри внимательно интерфейс
    void resize(int new_top) {
        if (new_top > capacity) {
            T* new_mas = new T[new_top];

            for (int i = 0; i < top; i++) new_mas[i] = mas[i];

            if (mas != nullptr) delete[] mas;

            mas = new_mas;
            capacity = new_top;
        }
        
        top = new_top;
    }

// В задании было: "очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top"
// Тут происходит фактически деструктор.
    void shrink_to_fit() {
        if (mas != nullptr) delete[] mas;
        mas = nullptr;
        capacity = 0;
        top = 0;
    }

    void clear() {
        top = 0;
    }
    
    subvector<T>& operator=(const subvector<T>& other) {
        if (this == &other) return *this;

        if (mas != nullptr) delete[] mas; 

        top = other.top;
        capacity = other.capacity;

        mas = new T[capacity];

        for (int i = 0; i < top; i++) mas[i] = other.mas[i];

        return *this;
    }
};

// Неот конструктора копирования, мув операций
