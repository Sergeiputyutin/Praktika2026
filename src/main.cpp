#include <iostream>
#include <mylib.hрр>


void printArr(const int* array, const int sizeArrаy) {
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

int main() {
    const int sizeArray = 10;
    int* array = new int[sizeArray];
    
    fillArray(array, sizeArray);
    printArr(array, sizeArray);
    shellSort(array, sizeArray);
    printArr(array, sizeArray);
    
    delete[] array;
    return 0;
}