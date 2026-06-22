#include <iostream>
#include <mylib.hpp>
#include <fstream>
#include <locale>
#include <sstream>  // Для проверки

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

// Сохранение массива в файл (только числа, без размера)
void saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for(int i = 0; i < sizeArray; i++) {
            file << array[i];
            if (i < sizeArray - 1) file << " ";
        }
        file.close();
        std::cout << "Array saved to: " << filename << std::endl;
    } else {
        std::cout << "Error: cannot create file " << filename << std::endl;
    }
}

// Загрузка массива из файла (просто читаем числа)
bool loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << filename << std::endl;
        return false;
    }
    
    int count = 0;
    int value;
    
    // Читаем числа, пока есть данные и не превысили размер
    while (file >> value && count < sizeArray) {
        array[count] = value;
        count++;
    }
    
    file.close();
    
    if (count != sizeArray) {
        std::cout << "Warning: read " << count << " elements, expected " << sizeArray << std::endl;
        return false;
    }
    
    std::cout << "Array loaded from: " << filename << std::endl;
    return true;
}

int main() {
    // Настройка русского языка для Linux
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    
    // 1. СОЗДАЕМ И СОХРАНЯЕМ МАССИВ
    std::cout << "=== Creating and saving array ===" << std::endl;
    int* array = new int[sizeArray];
    fillArray(array, sizeArray);
    std::cout << "Generated array: ";
    printArr(array, sizeArray);
    saveArrayToFile(array, sizeArray, "input.txt");
    delete[] array;  // Освобождаем память
    
    // 2. ЗАГРУЖАЕМ МАССИВ ИЗ ФАЙЛА
    std::cout << "\n=== Loading array from file ===" << std::endl;
    int* loadedArray = new int[sizeArray];
    
    // Инициализируем массив нулями для чистоты
    for(int i = 0; i < sizeArray; i++) {
        loadedArray[i] = 0;
    }
    
    if (loadArrayFromFile(loadedArray, sizeArray, "input.txt")) {
        std::cout << "Loaded array: ";
        printArr(loadedArray, sizeArray);
        
        // 3. СОРТИРУЕМ ЗАГРУЖЕННЫЙ МАССИВ
        std::cout << "\n=== Sorting loaded array ===" << std::endl;
        shellSort(loadedArray, sizeArray);
        std::cout << "Sorted array: ";
        printArr(loadedArray, sizeArray);
        
        // 4. СОХРАНЯЕМ ОТСОРТИРОВАННЫЙ МАССИВ
        saveArrayToFile(loadedArray, sizeArray, "output.txt");
    } else {
        std::cout << "Failed to load array from file" << std::endl;
    }
    
    delete[] loadedArray;
    
    return 0;
}