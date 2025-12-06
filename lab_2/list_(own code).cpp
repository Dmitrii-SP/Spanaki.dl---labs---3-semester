#include <iostream>
#include <random>
#include <chrono>

// код здесь
template <typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node(const T& value) : data(value), next(nullptr) {}
};

// Q: думаю, что структура Node должна находиться внутри класса листа, потому что это его внутренняя характеристика

template <typename T>
class subforwardlist
{
private:
    Node<T>* head;
    unsigned int count;

public:
    subforwardlist() : head(nullptr), count(0) {}
    ~subforwardlist()
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            Node<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
        // Зачем здесь эти две операции? Компилятор самостоятельно их выкинет при компиляции. Это лишнее приседание
        head = nullptr;
        count = 0;
    }
    subforwardlist(subforwardlist&& other) noexcept
        : head(other.head), count(other.count)
    {
        other.head = nullptr;
        other.count = 0;
    }

// Здесь переписана логика деструктора. Подумай, как можно её переиспользовать, а не писать второй раз
// Посмотри идеому copy & swap
    subforwardlist& operator=(subforwardlist&& other) noexcept
    {
        if (this != &other)
        {
            Node<T>* current = head;
            while (current != nullptr)
            {
                Node<T>* next_node = current->next;
                delete current;
                current = next_node;
            }
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }
    unsigned int size() const { return count; }
    void push_back(const T& value)
    {
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr) { head = new_node; }
        else
        {
            Node<T>* current = head;
            while (current->next != nullptr) { current = current->next; }
            current->next = new_node;
        }
        count++;
    }
    void push_forward(const T& value)
    {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        head = new_node;
        count++;
    }
    void push_where(unsigned int where, const T& value)
    {
        if (where > count) { push_back(value); return; }
        if (where == 0) { push_forward(value); return; }
        Node<T>* current = head;
        for (unsigned int i = 0; i < where - 1; i++) { current = current->next; }
        Node<T>* new_node = new Node<T>(value);
        new_node->next = current->next;
        current->next = new_node;
        count++;
    }
    T pop_forward()
    {
        if (head == nullptr) { return T(); }
        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        count--;
        return value;
    }
    T pop_back()
    {
        if (head == nullptr) { return T(); }
        if (head->next == nullptr)
        {
            T value = head->data;
            delete head;
            head = nullptr;
            count--;
            return value;
        }
        Node<T>* current = head;
        while (current->next->next != nullptr) { current = current->next; }
        Node<T>* last = current->next;
        T value = last->data;
        current->next = nullptr;
        delete last;
        count--;
        return value;
    }
    T erase_where(unsigned int where)
    {
        if (head == nullptr || where >= count) { return T(); }
        if (where == 0) { return pop_forward(); }
        Node<T>* current = head;
        for (unsigned int i = 0; i < where - 1; i++) { current = current->next; }
        Node<T>* to_delete = current->next;
        T value = to_delete->data;
        current->next = to_delete->next;
        delete to_delete;
        count--;
        return value;
    }
};

// 1) В методах push_smth, pop_smth и erase_where можно вынести метод, который считает указатель на заданную индексом ноду. 
// Это сильно увеличит читаемость кода и не замедлит его. При этом не нужно будет по несколько раз копировать и изменять одно и то же
// 2) Не увидел обычных конструктора копирования и оператора присваивания. Сейчас лист нельзя скопировать, а можно только мувнуть.   
