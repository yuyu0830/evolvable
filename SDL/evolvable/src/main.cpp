#include <iostream>

const int SIZE = 10;

void reverse(int* arr, int num);
void print(int* arr, int num);

int main(int argv, char** args) {
    int a[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    reverse(a, SIZE);
    print(a, SIZE);
}

void reverse(int* arr, int num) {
    int tmp = 0;
    for (int i = 0; i < num / 2; i++) {
        tmp = arr[i];
        arr[i] = arr[num - i - 1];
        arr[num - i - 1] = tmp;
    }
}

void print(int* arr, int num) {
    for (int i = 0; i < num; i++) {
        printf("%d  ", arr[i]);
    }
}