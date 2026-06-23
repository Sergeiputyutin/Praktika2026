#pragma once
#include <iostream>
#include <fstream>
#include <mylib.hpp>

template <typename T>
class Array
{
public: 
    Array() : arr(nullptr), size(0) {} 
    Array(T* arr, int size) : size(size)
    {
        this->arr = new T[size];
        for(int i = 0; i < size; i++)
            this->arr[i] = arr[i];
    }
    Array(const Array& other) : size(other.size)
    {
        arr = new T[size];
        for(int i = 0; i < size; i++)
            arr[i] = other.arr[i];
    }
    ~Array() { delete[] arr; }

    int getSize() { return size; };
    const T* getArray() const { return arr; };
    void setArray(T* arr, int size);
    void writeFile(const char* path);
    void readFile(const char* path);
    void fillRnd(int size, int min, int max);
    void shellSort();
    void printArray();
    
    T& operator [] (int i) {  return arr[i]; };
    Array& operator = (const Array& other);
    
private:
    T* arr;
    int size;
    void cleanArray(int size);
};

template<typename T>
void Array<T>::cleanArray(int size)
{
    delete[] arr;
    arr = new T[size];
}

template<typename T>
void Array<T>::setArray(T* arr, int size)
{
    cleanArray(size);
    this->size=size;
    for(int i = 0; i < size; i++)
        this->arr[i] = arr[i];
}

template<typename T>
void Array<T>::writeFile(const char* path)
{
    std::ofstream file(path);
    if(!file.is_open())
    {
        std::cerr << "File not open";
        return;
    }
    for (int i = 0; i < size; i++)
        file << arr[i] << " ";
}

template<typename T>
void Array<T>::readFile(const char* path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cerr << "File not open";
        return;
    }
    int count = 0;
    T element;
    while(file >> element) count++;
    file.clear();
    file.seekg(0);
    this->size = count;
    cleanArray(count);
    for(int i = 0; i < count; i++)
    {
        file >> arr[i];
    }
}

template<typename T>
void Array<T>::fillRnd(int size, int min, int max)
{   
    cleanArray(size);
    this->size = size;
    mylib::Rng rng;
    for(int i = 0; i < size; i++)
        arr[i] = rng.nextInt(min, max);
}

template<typename T>
void Array<T>::shellSort()
{
    for(int gap = size / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < size; i++) {
            int j;
            T temp = arr[i];
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            
            arr[j] = temp;
        }
    }
}

template<typename T>
void Array<T>::printArray()
{
    for(int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << '\n';
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this == &other) return *this;

    size = other.size;
    cleanArray(size);
    for (int i = 0; i < size; i++)
        arr[i] = other.arr[i];

    return *this;
}