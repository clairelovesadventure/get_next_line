#include <stdlib.h>
#include <stdio.h>

void functionA() {
    static int count = 0;
    count++;
    printf("Count: %d\n", count);
}

void functionB() {
    printf("FunctionB called\n");
}

int main() {
    functionA(); // Output: Count: 1
    functionB(); // Output: FunctionB called
    functionA(); // Output: Count: 2
    functionB(); // Output: FunctionB called
    functionA(); // Output: Count: 3
    return 0;
}
