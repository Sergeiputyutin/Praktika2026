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
        for(int i = 0; i < sizeArray; i++) {
            file << array[i] << " ";
        }
        file.close();
        std::cout << "Массив сохранен в: " << filename << std::endl;
    } else {
        std::cout << "Ошибка: не удалось создать файл " << filename << std::endl;
    }
}

// Загрузка массива из файла
void loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for(int i = 0; i < sizeArray; i++) {
            file >> array[i];
        }
        file.close();
        std::cout << "Массив загружен из: " << filename << std::endl;
    } else {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
    }
}

int main() {
    // НАСТРОЙКА РУССКОГО ЯЗЫКА ДЛЯ LINUX
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    // Заполняем массив
    fillArray(array, sizeArray);
    std::cout << "Исходный массив: ";
    printArr(array, sizeArray);
    
    // Сохраняем исходный массив в файл
    saveArrayToFile(array, sizeArray, "input.txt");
    
    // Сортируем массив
    shellSort(array, sizeArray);
    std::cout << "Отсортированный массив: ";
    printArr(array, sizeArray);
    
    // Сохраняем отсортированный массив в файл
    saveArrayToFile(array, sizeArray, "output.txt");
    
    // Пример загрузки из файла
    int* loadedArray = new int[sizeArray];
    loadArrayFromFile(loadedArray, sizeArray, "input.txt");
    std::cout << "Загруженный массив: ";
    printArr(loadedArray, sizeArray);
    delete[] loadedArray;
    
    delete[] array;
    return 0;
}