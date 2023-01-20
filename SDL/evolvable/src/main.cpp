#include <iostream>

int main(int argv, char** args) {
    int* a = new int[10];
    for (int i = 0; i < 10; i++) {
        a[i] = i * 5;
    }
    printf("%d\n", a[5]);
    printf("%p\n", a);
    delete[] a;
    a = NULL;
    a = new int[10];
    printf("%p\n", a);
    for (int i = 0; i < 10; i++) {
        a[i] = i * 5;
    }
    printf("%d\n", a[5]);
    printf("%p\n", a);
}
