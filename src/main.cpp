#include <iostream>
#include "array.hpp"

int main() {

    Array<int> arr(nullptr, 0);  // пустой массив

    // заполнить случайными числами и вывести
    arr.fillRnd(30, 0, 30);
    std::cout << "Before sort: ";
    arr.printArray();

    // записать в input.txt
    arr.writeFile(FILE1_PATH);

    // прочитать из input.txt
    arr.readFile(FILE1_PATH);
    std::cout << "Read from file: ";
    arr.printArray();

    // отсортировать и записать в output.txt
    arr.shellSort();
    arr.writeFile(FILE2_PATH);

    std::cout << "After sort: ";
    arr.printArray();

    return 0;
}