#include <iostream>

void print(const char c[20][5], int n) {
    
    for (int i = 0; i < n; i++) {
        char a[30] = "dddd";
        strcat_s(a, c[i]);
        printf("%s\n", a);
    };
}

int main(int argv, char** args) {
    char a[20][5] = { "abc", "bbb", "ccc", "ddd", ""};
    print(a, 3);
    return 0;
}

