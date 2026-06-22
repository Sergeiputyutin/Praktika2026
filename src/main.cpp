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

// Сохранение массива в файл
void saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
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

// Загрузка массива из файла (возвращает новый массив)
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
    
    file.close();
    std::cout << "Array loaded from: " << filename << " (size: " << loadedSize << ")" << std::endl;
    return array;
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
    int loadedSize = 0;
    int* loadedArray = loadArrayFromFile("input.txt", loadedSize);
    
    if (loadedArray == nullptr) {
        std::cout << "Failed to load array from file" << std::endl;
        return 1;
    }
    
    std::cout << "Loaded array: ";
    printArr(loadedArray, loadedSize);
    
    // 3. СОРТИРУЕМ ЗАГРУЖЕННЫЙ МАССИВ
    std::cout << "\n=== Sorting loaded array ===" << std::endl;
    shellSort(loadedArray, loadedSize);
    std::cout << "Sorted array: ";
    printArr(loadedArray, loadedSize);
    
    // 4. СОХРАНЯЕМ ОТСОРТИРОВАННЫЙ МАССИВ
    saveArrayToFile(loadedArray, loadedSize, "output.txt");
    
    delete[] loadedArray;
    
    return 0;
}