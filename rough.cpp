#include <iostream>

int main() {
    int size = 10;
    int** pointerToIntPointer = new int*[size];
  
    for(int index = 0; index < size; index++) {
        pointerToIntPointer[index] = NULL;
        printf("%p\n", pointerToIntPointer[index]);
    }
}