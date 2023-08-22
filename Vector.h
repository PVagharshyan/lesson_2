#pragma once
#include <iostream>
#include <string>

template <class T>
class Vector {
public:
    Vector();
    Vector(int);
    Vector(const Vector&);
    Vector(const std::initializer_list<T>&);
    void push_back(const T&);
    void push_front(const T&);
    T pop_back();
    int size() const; 
    bool operator==(const Vector<T>&) const;
    T operator[](int) const;
    Vector<T>& operator=(const Vector&);
    T at(int) const;
    std::string repr() const;
    ~Vector();
private:
    int m_capacity;
    int m_size;
    T* m_arr;
};

template <class T>
Vector<T>::Vector() 
    :m_size{0}, m_capacity{4}, m_arr{new T[m_capacity]}
{}

template <class T>
Vector<T>::Vector(int size) 
{
    if (size < 0) throw std::runtime_error("Error");
    m_capacity = size*2;
    m_size = size; 
    m_arr = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(const Vector& vector) {
    Vector tmp;
    tmp.m_capacity = vector.m_capacity;
    tmp.m_size = vector.m_size;
    tmp.m_arr = new T[tmp.m_capacity];
    for (int i = 0; i < tmp.m_size; ++i) {
        tmp.m_arr[i] = vector.m_arr[i];
    }
    std::swap(tmp.m_capacity, m_capacity);
    std::swap(tmp.m_size, m_size);
    std::swap(tmp.m_arr, m_arr);
}
template <class T>
Vector<T>::Vector(const std::initializer_list<T>& args) {
    m_size = args.size();
    m_capacity = m_size*2;
    m_arr = new T[m_capacity];
    int i = 0;
    for (const auto& item : args) {
        m_arr[i++] = item;
    } 
}

template <class T>
void Vector<T>::push_back(const T& element) {
    if (m_capacity < m_size + 1) {
        m_capacity *= 2;
        T* tmp = new T[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp;
        tmp = nullptr;
    }
    ++m_size;
    m_arr[m_size - 1] = element;
    
}

template <class T>
void Vector<T>::push_front(const T& element) {
    if (m_capacity < m_size + 1) {
        m_capacity *= 2;
        T* tmp = new T[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp;
        tmp = nullptr;
    }
    ++m_size;
    for (int i = m_size - 1;i > 0; --i) {
        m_arr[i] = m_arr[i - 1];
    }
    m_arr[0] = element;
}

template <class T>
T Vector<T>::pop_back() {
    if (m_size > 0) {
        return m_arr[--m_size];
    }
    else {
        throw std::runtime_error("Error:vector is empty!");
    }
}

template <class T>
int Vector<T>::size() const {
    return m_size;
}

template <class T>
bool Vector<T>::operator==(const Vector<T>& vector) const{
    if (m_size != vector.m_size) {
        return false;
    }
    else {
        for (int i = 0; i < m_size; ++i) {
            if (vector.m_arr[i] != m_arr[i]) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
T Vector<T>::operator[](int index) const{
    if (index < 0) throw std::runtime_error("Error: Out of range!");
    return m_arr[index];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& vector) {     
    if (*this == vector) {
        return *this;
    }
    Vector tmp;
    tmp.m_capacity = vector.m_capacity;
    tmp.m_size = vector.m_size;
    tmp.m_arr = new T[tmp.m_capacity];
    for (int i = 0; i < tmp.m_size; ++i) {
        tmp.m_arr[i] = vector.m_arr[i];
    }
    std::swap(tmp.m_capacity, m_capacity);
    std::swap(tmp.m_size, m_size);
    std::swap(tmp.m_arr, m_arr);
    return *this;
}

template <class T>
T Vector<T>::at(int index) const {
    if (index < 0 || index >= m_size) throw std::runtime_error("Error: Out of range!");
    return m_arr[index];
}

template <class T>
std::string Vector<T>::repr() const {
    std::string size = "m_size: " + std::to_string(m_size);
    std::string capacity = "m_capacity: " + std::to_string(m_capacity);
    std::string arr = "arr: ";
    for (int i = 0; i < m_size; ++i) {
        if (i != m_size - 1) arr += std::to_string(m_arr[i]) + ", ";
        else arr += std::to_string(m_arr[i]);
    }
    if (m_size == 0) arr += "empty";
    return (size + "\n" + capacity + "\n" + arr);
}

template <class T>
Vector<T>::~Vector() {
    delete[] m_arr;
}
