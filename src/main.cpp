#include <iostream>
#include <mylib.hpp>
#include <fstream>
#include <locale>
#include <cstring>  // Для strerror

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

// Сохранение массива в файл (с проверкой)
bool saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << filename << " for writing" << std::endl;
        return false;
    }
    
    // Проверяем, что файл открыт
    std::cout << "Writing " << sizeArray << " elements to " << filename << std::endl;
    
    for(int i = 0; i < sizeArray; i++) {
        file << array[i];
        if (i < sizeArray - 1) {
            file << " ";
        }
        // Проверяем, что запись прошла успешно
        if (file.fail()) {
            std::cout << "Error: failed to write element " << i << std::endl;
            file.close();
            return false;
        }
    }
    file << std::endl;  // Добавляем перевод строки
    
    file.close();
    std::cout << "Array saved to: " << filename << std::endl;
    return true;
}

// Загрузка массива из файла (с подробной диагностикой)
bool loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << filename << " for reading" << std::endl;
        std::cout << "Check if file exists: " << filename << std::endl;
        return false;
    }
    
    std::cout << "File opened successfully: " << filename << std::endl;
    
    // Проверяем размер файла
    file.seekg(0, std::ios::end);
    long fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::cout << "File size: " << fileSize << " bytes" << std::endl;
    
    // Читаем все числа из файла
    int count = 0;
    int value;
    while (file >> value && count < sizeArray) {
        array[count] = value;
        std::cout << "Read element " << count << ": " << value << std::endl;
        count++;
    }
    
    file.close();
    
    std::cout << "Read " << count << " elements from file" << std::endl;
    
    if (count != sizeArray) {
        std::cout << "Warning: read " << count << " elements, expected " << sizeArray << std::endl;
        return false;
    }
    
    std::cout << "Array loaded from: " << filename << std::endl;
    return true;
}

// Проверка содержимого файла
void showFileContent(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    std::cout << "Content of " << filename << ": ";
    char ch;
    while (file.get(ch)) {
        std::cout << ch;
    }
    std::cout << std::endl;
    file.close();
}

int main() {
    // Настройка русского языка для Linux
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    
    // 1. УДАЛЯЕМ СТАРЫЕ ФАЙЛЫ
    std::cout << "Removing old files..." << std::endl;
    remove("input.txt");
    remove("output.txt");
    
    // 2. СОЗДАЕМ И СОХРАНЯЕМ МАССИВ
    std::cout << "\n=== Creating and saving array ===" << std::endl;
    int* array = new int[sizeArray];
    fillArray(array, sizeArray);
    std::cout << "Generated array: ";
    printArr(array, sizeArray);
    
    if (saveArrayToFile(array, sizeArray, "input.txt")) {
        std::cout << "Array saved successfully" << std::endl;
    } else {
        std::cout << "Failed to save array" << std::endl;
        delete[] array;
        return 1;
    }
    
    // Проверяем содержимое файла
    std::cout << "\n=== Checking file content ===" << std::endl;
    showFileContent("input.txt");
    
    delete[] array;  // Освобождаем память
    
    // 3. ЗАГРУЖАЕМ МАССИВ ИЗ ФАЙЛА
    std::cout << "\n=== Loading array from file ===" << std::endl;
    int* loadedArray = new int[sizeArray];
    
    // Инициализируем массив нулями
    for(int i = 0; i < sizeArray; i++) {
        loadedArray[i] = 0;
    }
    
    if (loadArrayFromFile(loadedArray, sizeArray, "input.txt")) {
        std::cout << "Loaded array: ";
        printArr(loadedArray, sizeArray);
        
        // 4. СОРТИРУЕМ ЗАГРУЖЕННЫЙ МАССИВ
        std::cout << "\n=== Sorting loaded array ===" << std::endl;
        shellSort(loadedArray, sizeArray);
        std::cout << "Sorted array: ";
        printArr(loadedArray, sizeArray);
        
        // 5. СОХРАНЯЕМ ОТСОРТИРОВАННЫЙ МАССИВ
        saveArrayToFile(loadedArray, sizeArray, "output.txt");
        showFileContent("output.txt");
    } else {
        std::cout << "Failed to load array from file" << std::endl;
        // Выводим текущую директорию
        system("pwd");
        // Выводим список файлов
        system("ls -la");
    }
    
    delete[] loadedArray;
    
    return 0;
}