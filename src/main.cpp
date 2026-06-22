#include <iostream>
#include <fstream>
#include <mylib.hpp>

static void printArr(const int* array, const int sizeArray) {

    for(int i = 0; i < sizeArray; i++)
        std::cout << array[i] << " ";
    std::cout << '\n';
}

static void fillArray(int* array, const int sizeArray, const int min, const int max) {

    mylib::Rng rng;
    for(int i = 0; i < sizeArray; i++)
        array[i] = rng.nextInt(min, max);
}

static void shellSort(int* array, const int sizeArray) {

    for(int gap = sizeArray / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < sizeArray; i++) {
            int j, temp = array[i];

            for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            
            array[j] = temp;
        }
    }
}

static void readFromFile(const char* path, int*& array, int& size) {

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Invalid path file";
        return;
    }

    int num, count = 0;
    while(file >> num) count++;

    if(!file.eof()) {        
        std::cerr << "Failed to write file";
        return;
    }
    file.clear();
    file.seekg(0);

    size = count;
    array = new int[count];

    for(int i = 0; i < count; i++) 
        file >> array[i];
    
    file.close();
}

static void writeToFile(const char* path, const int* array, const int& size) {

    std::ofstream file(path);

    if (!file.is_open()) 
        std::cerr << "Not Open File\n";

    for(int i = 0; i < size; i++)
        file << array[i] << " ";

    file.close();
}

int main() {

    const char* input = FILE1_PATH;
    const char* output = FILE2_PATH;

    int sizeArray = 30;
    int* array = new int[sizeArray];

    //fillArray(array, sizeArray, 0, 30);

    //writeToFile(input, array, sizeArray);
    readFromFile(input, array, sizeArray);
    std::cout << "Read from file input: ";
    printArr(array, sizeArray);

    shellSort(array, sizeArray);

    writeToFile(output, array, sizeArray);
    readFromFile(output, array, sizeArray);
    std::cout << "Read from file output: ";
    printArr(array, sizeArray);

    delete[] array;
    return 0;
}