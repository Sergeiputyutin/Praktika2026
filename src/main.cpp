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
        file << std::endl;
        file.close();
        std::cout << "Массив сохранен в файл: " << filename << std::endl;
    } else {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для записи" << std::endl;
    }
}

// Загрузка массива из файла
bool loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для чтения" << std::endl;
        return false;
    }
    
    int count = 0;
    int value;
    while (file >> value && count < sizeArray) {
        array[count] = value;
        count++;
    }
    
    file.close();
    
    if (count != sizeArray) {
        std::cout << "Предупреждение: прочитано " << count << " элементов, ожидалось " << sizeArray << std::endl;
        return false;
    }
    
    std::cout << "Массив загружен из файла: " << filename << std::endl;
    return true;
}

// Проверка существования файла
bool fileExists(const char* filename) {
    std::ifstream file(filename);
    return file.good();
}

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    std::cout << "=== Генерация и сохранение массива ===" << std::endl;
    
    // 1. Генерируем массив
    fillArray(array, sizeArray);
    std::cout << "Сгенерированный массив: ";
    printArr(array, sizeArray);
    
    // 2. Сохраняем в файл
    saveArrayToFile(array, sizeArray, "input.txt");
    
    // 3. Очищаем массив (чтобы убедиться, что данные загружаются из файла)
    for(int i = 0; i < sizeArray; i++) {
        array[i] = 0;
    }
    std::cout << "Массив очищен: ";
    printArr(array, sizeArray);
    
    std::cout << "\n=== Загрузка массива из файла ===" << std::endl;
    
    // 4. Загружаем массив из файла
    if (!loadArrayFromFile(array, sizeArray, "input.txt")) {
        std::cout << "Не удалось загрузить массив из файла" << std::endl;
        delete[] array;
        return 1;
    }
    
    std::cout << "Загруженный массив: ";
    printArr(array, sizeArray);
    
    std::cout << "\n=== Сортировка массива ===" << std::endl;
    
    // 5. Сортируем
    shellSort(array, sizeArray);
    std::cout << "Отсортированный массив: ";
    printArr(array, sizeArray);
    
    // 6. Сохраняем результат в другой файл
    saveArrayToFile(array, sizeArray, "output.txt");
    
    std::cout << "\n=== Готово! ===" << std::endl;
    std::cout << "Исходный массив сохранен в: input.txt" << std::endl;
    std::cout << "Отсортированный массив сохранен в: output.txt" << std::endl;
    
    delete[] array;
    return 0;
}