#include <iostream>
#include <mylib.hpp>
#include <fstream>
#include <locale>
#include <sstream>

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

// ПРОСТОЕ СОХРАНЕНИЕ
void saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for(int i = 0; i < sizeArray; i++) {
            file << array[i] << " ";
        }
        file << std::endl;
        file.close();
        std::cout << "Array saved to: " << filename << std::endl;
    }
}

// ПРОСТАЯ ЗАГРУЗКА (РАБОТАЕТ!)
void loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        // Читаем построчно
        std::string line;
        std::getline(file, line);
        file.close();
        
        // Парсим строку
        std::istringstream iss(line);
        for(int i = 0; i < sizeArray; i++) {
            iss >> array[i];
        }
        std::cout << "Array loaded from: " << filename << std::endl;
    } else {
        std::cout << "Error: cannot open file " << filename << std::endl;
    }
}

int main() {
    // Настройка русского языка для Linux
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    // 1. СОЗДАЕМ МАССИВ
    fillArray(array, sizeArray);
    std::cout << "Generated array: ";
    printArr(array, sizeArray);
    
    // 2. СОХРАНЯЕМ В ФАЙЛ
    saveArrayToFile(array, sizeArray, "input.txt");
    
    // 3. ОЧИЩАЕМ МАССИВ
    for(int i = 0; i < sizeArray; i++) {
        array[i] = 0;
    }
    std::cout << "Array cleared: ";
    printArr(array, sizeArray);
    
    // 4. ЗАГРУЖАЕМ ИЗ ФАЙЛА
    loadArrayFromFile(array, sizeArray, "input.txt");
    std::cout << "Loaded array: ";
    printArr(array, sizeArray);
    
    // 5. СОРТИРУЕМ
    shellSort(array, sizeArray);
    std::cout << "Sorted array: ";
    printArr(array, sizeArray);
    
    // 6. СОХРАНЯЕМ РЕЗУЛЬТАТ
    saveArrayToFile(array, sizeArray, "output.txt");
    
    delete[] array;
    return 0;
}