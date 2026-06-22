#include <iostream>
#include <mylib.hpp>
#include <fstream>
#include <locale>
#include <unistd.h>  // для getcwd

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

// ПРОВЕРКА СУЩЕСТВОВАНИЯ ФАЙЛА
bool fileExists(const char* filename) {
    std::ifstream file(filename);
    return file.good();
}

// СОХРАНЕНИЕ С ПОЛНЫМ ПУТЕМ
void saveArrayToFile(const int* array, int sizeArray, const char* filename) {
    // Получаем текущую директорию
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current directory: " << cwd << std::endl;
    }
    
    std::cout << "Saving to: " << filename << std::endl;
    
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open file for writing!" << std::endl;
        return;
    }
    
    // Записываем каждый элемент с новой строки
    for(int i = 0; i < sizeArray; i++) {
        file << array[i];
        if (i < sizeArray - 1) {
            file << "\n";  // Каждое число на новой строке!
        }
    }
    file << std::endl;
    
    file.close();
    std::cout << "Array saved to: " << filename << std::endl;
    
    // Проверяем, что файл создан
    if (fileExists(filename)) {
        std::cout << "File exists and is readable" << std::endl;
    } else {
        std::cout << "WARNING: File does not exist after save!" << std::endl;
    }
}

// ЗАГРУЗКА - ПОСТРОЧНО
bool loadArrayFromFile(int* array, int sizeArray, const char* filename) {
    std::cout << "Loading from: " << filename << std::endl;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: Cannot open file for reading!" << std::endl;
        return false;
    }
    
    // Читаем построчно
    int count = 0;
    std::string line;
    
    while (std::getline(file, line) && count < sizeArray) {
        // Пропускаем пустые строки
        if (line.empty()) continue;
        
        // Преобразуем строку в число
        int value = std::stoi(line);
        array[count] = value;
        std::cout << "Read line " << count << ": " << value << std::endl;
        count++;
    }
    
    file.close();
    
    if (count != sizeArray) {
        std::cout << "WARNING: Read " << count << " elements, expected " << sizeArray << std::endl;
        return false;
    }
    
    std::cout << "Array loaded successfully!" << std::endl;
    return true;
}

// ПОКАЗАТЬ СОДЕРЖИМОЕ ФАЙЛА
void showFileContent(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return;
    }
    
    std::cout << "\n=== Content of " << filename << " ===" << std::endl;
    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        std::cout << "Line " << lineNum++ << ": '" << line << "'" << std::endl;
    }
    std::cout << "=== End of file ===" << std::endl;
    file.close();
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    // ПОКАЗЫВАЕМ ТЕКУЩУЮ ДИРЕКТОРИЮ
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Working directory: " << cwd << std::endl;
    }
    
    // 1. СОЗДАЕМ МАССИВ
    fillArray(array, sizeArray);
    std::cout << "\nGenerated array: ";
    printArr(array, sizeArray);
    
    // 2. СОХРАНЯЕМ
    saveArrayToFile(array, sizeArray, "input.txt");
    
    // 3. ПОКАЗЫВАЕМ СОДЕРЖИМОЕ ФАЙЛА
    showFileContent("input.txt");
    
    // 4. ОЧИЩАЕМ МАССИВ
    for(int i = 0; i < sizeArray; i++) {
        array[i] = 0;
    }
    std::cout << "\nCleared array: ";
    printArr(array, sizeArray);
    
    // 5. ЗАГРУЖАЕМ
    if (loadArrayFromFile(array, sizeArray, "input.txt")) {
        std::cout << "\nLoaded array: ";
        printArr(array, sizeArray);
        
        // 6. СОРТИРУЕМ
        shellSort(array, sizeArray);
        std::cout << "\nSorted array: ";
        printArr(array, sizeArray);
        
        // 7. СОХРАНЯЕМ РЕЗУЛЬТАТ
        saveArrayToFile(array, sizeArray, "output.txt");
    } else {
        std::cout << "Failed to load array!" << std::endl;
    }
    
    delete[] array;
    return 0;
}