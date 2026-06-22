#include <iostream>
#include <mylib.hpp>
#include <fstream>
#include <locale>

void printArr(const int* array, const int sizeArray) {
    for(int i = 0; i < sizeArray; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}

void fillArray(int* array, int sizeArray) {
    mylib::Rng rng;
    
    for(int i = 0; i < sizeArray; i++)
    {
        array[i] = rng.nextInt(1, 10);
    }
}

void shellSort(int* array, int sizeArray) {
    for(int gap = sizeArray / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < sizeArray; i +=1)
        {
            int temp = array[i];
            int j;

            for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
        }
    }
}

// Сохранение массива в файл (с размером)
void saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        // Сохраняем размер массива первым числом
        file << sizeArray << "\n";
        for(int i = 0; i < sizeArray; i++) {
            file << array[i] << " ";
        }
        file.close();
        std::cout << "Array saved to: " << filename << std::endl;
    } else {
        std::cout << "Error: cannot create file " << filename << std::endl;
    }
}

// Загрузка массива из файла (с проверкой размера)
int* loadArrayFromFile(const char* filename, int& loadedSize) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << filename << std::endl;
        return nullptr;
    }
    
    // Читаем размер массива
    file >> loadedSize;
    if (loadedSize <= 0) {
        std::cout << "Error: invalid array size" << std::endl;
        file.close();
        return nullptr;
    }
    
    // Выделяем память и читаем элементы
    int* array = new int[loadedSize];
    for(int i = 0; i < loadedSize; i++) {
        file >> array[i];
    }
    
    // Проверяем, сколько чисел реально прочитано
    if (file.fail()) {
        std::cout << "Error: failed to read array data" << std::endl;
        delete[] array;
        file.close();
        return nullptr;
    }
    
    file.close();
    std::cout << "Array loaded from: " << filename << " (size: " << loadedSize << ")" << std::endl;
    return array;
}

int main() {
    // Настройка русского языка для Linux
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    // Заполняем массив
    fillArray(array, sizeArray);
    std::cout << "Original array: ";
    printArr(array, sizeArray);
    
    // Сохраняем исходный массив в файл
    saveArrayToFile(array, sizeArray, "input.txt");
    
    // Сортируем массив
    shellSort(array, sizeArray);
    std::cout << "Sorted array: ";
    printArr(array, sizeArray);
    
    // Сохраняем отсортированный массив в файл
    saveArrayToFile(array, sizeArray, "output.txt");
    
    delete[] array;
    
    // Загружаем массив из файла
    std::cout << "\n=== Loading array from file ===" << std::endl;
    int loadedSize = 0;
    int* loadedArray = loadArrayFromFile("input.txt", loadedSize);
    
    if (loadedArray != nullptr) {
        std::cout << "Loaded array: ";
        printArr(loadedArray, loadedSize);
        
        // Сортируем загруженный массив
        shellSort(loadedArray, loadedSize);
        std::cout << "Sorted loaded array: ";
        printArr(loadedArray, loadedSize);
        
        delete[] loadedArray;
    }
    
    return 0;
}