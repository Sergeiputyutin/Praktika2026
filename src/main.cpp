#include <iostream>
#include <chrono>
#include "array.hpp"

using namespace std;

// Вывод информации об авторах
void showAuthorsInfo() {
    cout << "====================================" << endl;
    cout << "       Сортировка Шелла" << endl;
    cout << "====================================" << endl;
    cout << "Выполнили работу:" << endl;
    cout << "1. Марушкин Данила" << endl;
    cout << "2. Путютин Сергей" << endl;
    cout << "3. Хмельков Максим" << endl;
    cout << "Группа: 24ВВВ1" << endl;
    cout << "Бригада: №2" << endl;
    cout << "====================================" << endl << endl;
}

// Функция для безопасного ввода числа
template<typename T>
T getInput(const char* prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите корректное число!" << endl;
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    const char* inputFilename = FILE1_PATH;
    const char* outputFilename = FILE2_PATH;
    
    Array<int> arr;  // пустой массив
    
    showAuthorsInfo();

    while (true) {
        cout << "\n============ МЕНЮ ============" << endl;
        cout << "1. Ввести массив вручную" << endl;
        cout << "2. Сгенерировать случайный массив" << endl;
        cout << "3. Загрузить массив из файла" << endl;
        cout << "4. Сохранить массив в файл" << endl;
        cout << "5. Отсортировать массив (Шелла)" << endl;
        cout << "6. Показать массив" << endl;
        cout << "7. Выход" << endl;
        cout << "===============================" << endl;
        cout << "Выберите действие: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int size = getInput<int>("Введите количество элементов: ");
                
                if (size <= 0) {
                    cout << "Ошибка: размер массива должен быть больше 0!" << endl;
                    break;
                }
                
                int* tempArray = new int[size];
                cout << "Введите элементы: ";
                for (int i = 0; i < size; i++) {
                    cin >> tempArray[i];
                }
                
                arr.setArray(tempArray, size);
                delete[] tempArray;
                
                cout << "Массив успешно создан. Размер: " << arr.getSize() << endl;
                cout << "Содержимое массива: ";
                arr.printArray();
                
                // Сохраняем в файл
                arr.writeFile(inputFilename);
                cout << "Массив сохранен в файл: " << inputFilename << endl;
                break;
            }
            
            case 2: {
                int size = getInput<int>("Введите размер массива: ");
                int minVal = getInput<int>("Введите минимальное значение: ");
                int maxVal = getInput<int>("Введите максимальное значение: ");
                
                if (minVal > maxVal) {
                    cout << "Ошибка: минимальное значение больше максимального!" << endl;
                    break;
                }
                
                if (size <= 0) {
                    cout << "Ошибка: размер массива должен быть больше 0!" << endl;
                    break;
                }
                
                arr.fillRnd(size, minVal, maxVal);
                cout << "Случайный массив создан. Размер: " << arr.getSize() << endl;
                cout << "Содержимое массива: ";
                arr.printArray();
                
                arr.writeFile(inputFilename);
                cout << "Случайный массив сохранен в файл: " << inputFilename << endl;
                break;
            }
            
            case 3: {
                arr.readFile(inputFilename);
                if (arr.getSize() > 0) {
                    cout << "Массив успешно загружен из файла: " << inputFilename << endl;
                    cout << "Загруженный массив (размер " << arr.getSize() << "): ";
                    arr.printArray();
                } else {
                    cout << "Не удалось загрузить массив из файла или файл пуст!" << endl;
                }
                break;
            }
            
            case 4: {
                if (arr.getSize() == 0) {
                    cout << "Ошибка: массив пуст! Сначала создайте массив." << endl;
                } else {
                    arr.writeFile(outputFilename);
                    cout << "Массив сохранен в файл: " << outputFilename << endl;
                }
                break;
            }
            
            case 5: {
                if (arr.getSize() == 0) {
                    cout << "Ошибка: массив пуст! Сначала создайте массив." << endl;
                    break;
                }
                
                cout << "Исходный массив (размер " << arr.getSize() << "): ";
                arr.printArray();
                
                // Создаем копию массива для сортировки
                Array<int> tempArr = arr;
                
                // Измерение времени с помощью chrono в миллисекундах
                auto start = chrono::high_resolution_clock::now();
                tempArr.shellSort();
                auto end = chrono::high_resolution_clock::now();
                
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                
                cout << "\n=== Результат сортировки Шелла ===" << endl;
                cout << "Отсортированный массив (размер " << tempArr.getSize() << "): ";
                tempArr.printArray();
                cout << "Время сортировки: " << duration.count() << " миллисекунд" << endl;
                cout << "===================================" << endl;
                
                // Сохраняем отсортированный массив
                tempArr.writeFile(outputFilename);
                cout << "Отсортированный массив сохранен в файл: " << outputFilename << endl;
                
                // Обновляем основной массив
                arr = tempArr;
                break;
            }
            
            case 6: {
                if (arr.getSize() == 0) {
                    cout << "Массив пуст!" << endl;
                } else {
                    cout << "Текущий массив (размер " << arr.getSize() << "): ";
                    arr.printArray();
                }
                break;
            }
            
            case 7: {
                cout << "Выход из программы..." << endl;
                return 0;
            }
            
            default: {
                cout << "Неверный выбор! Пожалуйста, выберите пункт от 1 до 7." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
        }
    }

    return 0;
}