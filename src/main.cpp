#include <iostream>
#include <fstream>
#include <mylib.hpp>
#include <string>
#include <locale>
#include <sstream>
#include <vector>

// Устанавливаем локаль для поддержки русского языка
void setRussianLocale() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());
    std::cerr.imbue(std::locale());
}

void printArr(const int* array, const int sizeArray) {
    for(int i = 0; i < sizeArray; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}

void fillArray(int* array, int sizeArray) {
    mylib::Rng rng;
    
    for(int i = 0; i < sizeArray; i++) {
        array[i] = rng.nextInt(1, 10);
    }
}

void shellSort(int* array, int sizeArray) {
    for(int gap = sizeArray / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < sizeArray; i += 1) {
            int temp = array[i];
            int j;

            for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
        }
    }
}

// Функция для записи массива в файл (без размера)
void writeArrayToFile(const int* array, int sizeArray, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << " для записи!" << std::endl;
        return;
    }
    
    for(int i = 0; i < sizeArray; i++) {
        outFile << array[i] << " ";
    }
    outFile << std::endl;
    
    outFile.close();
    std::cout << "Массив записан в файл: " << filename << std::endl;
}

// Функция для чтения массива из файла (первое число - элемент, а не размер)
int* readArrayFromFile(const std::string& filename, int& sizeArray) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << " для чтения!" << std::endl;
        return nullptr;
    }
    
    // Проверяем, пустой ли файл
    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0) {
        std::cerr << "Ошибка: Файл " << filename << " пуст!" << std::endl;
        inFile.close();
        return nullptr;
    }
    inFile.seekg(0, std::ios::beg);
    
    // Читаем все числа из файла в вектор
    std::vector<int> numbers;
    int temp;
    while (inFile >> temp) {
        numbers.push_back(temp);
    }
    inFile.close();
    
    if (numbers.empty()) {
        std::cerr << "Ошибка: В файле " << filename << " нет чисел!" << std::endl;
        return nullptr;
    }
    
    // Размер массива = количество прочитанных чисел
    sizeArray = numbers.size();
    std::cout << "Прочитано " << sizeArray << " чисел из файла" << std::endl;
    
    // Копируем числа в массив
    int* array = new int[sizeArray];
    for (int i = 0; i < sizeArray; i++) {
        array[i] = numbers[i];
    }
    
    return array;
}

// Функция для добавления результата в output файл
void appendResultToFile(const int* array, int sizeArray, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << " для записи!" << std::endl;
        return;
    }
    
    outFile << "Отсортированный массив: ";
    for(int i = 0; i < sizeArray; i++) {
        outFile << array[i] << " ";
    }
    outFile << std::endl << "------------------------" << std::endl;
    
    outFile.close();
    std::cout << "Результат сохранён в " << filename << std::endl;
}

// Функция для отображения содержимого файла
void showFileContent(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Файл " << filename << " не существует или не может быть открыт" << std::endl;
        return;
    }
    
    std::cout << "Содержимое файла " << filename << ":" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    inFile.close();
}

// Функция для подсчёта элементов в файле
int countNumbersInFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return 0;
    }
    
    int count = 0;
    int temp;
    while (inFile >> temp) {
        count++;
    }
    inFile.close();
    return count;
}

int main(int argc, char* argv[]) {
    // Устанавливаем русскую локаль
    setRussianLocale();

    // Проверяем аргументы командной строки
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";
    
    if (argc >= 2) {
        inputFile = argv[1];
    }
    if (argc >= 3) {
        outputFile = argv[2];
    }
    
    std::cout << "Входной файл: " << inputFile << std::endl;
    std::cout << "Выходной файл: " << outputFile << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    // Показываем содержимое входного файла (если существует)
    std::ifstream testFile(inputFile);
    if (testFile.good()) {
        testFile.close();
        std::cout << "Файл " << inputFile << " существует." << std::endl;
        showFileContent(inputFile);
        
        // Подсчитываем количество чисел в файле
        int numCount = countNumbersInFile(inputFile);
        std::cout << "Количество чисел в файле: " << numCount << std::endl;
    } else {
        std::cout << "Файл " << inputFile << " не существует." << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    
    // Пытаемся прочитать массив из файла
    int sizeArray = 0;
    int* array = readArrayFromFile(inputFile, sizeArray);
    
    // Если не удалось прочитать - генерируем новый массив
    if (array == nullptr) {
        std::cout << "Не удалось прочитать массив из файла." << std::endl;
        std::cout << "Генерируем новый массив..." << std::endl;
        sizeArray = 10;
        array = new int[sizeArray];
        fillArray(array, sizeArray);
        
        // Сохраняем сгенерированный массив в input файл
        writeArrayToFile(array, sizeArray, inputFile);
        std::cout << "Сгенерированный массив записан в " << inputFile << std::endl;
    } else {
        std::cout << "Массив успешно прочитан из файла. Размер: " << sizeArray << std::endl;
    }
    
    // Выводим массив на экран
    std::cout << "Исходный массив: ";
    printArr(array, sizeArray);
    
    // Сортируем
    std::cout << "Выполняем сортировку Шелла..." << std::endl;
    shellSort(array, sizeArray);
    
    // Выводим результат на экран
    std::cout << "Отсортированный массив: ";
    printArr(array, sizeArray);
    
    // Записываем результат в output файл
    appendResultToFile(array, sizeArray, outputFile);
    
    delete[] array;
    return 0;
}