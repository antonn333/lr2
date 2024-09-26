#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void test_qsort(int* items, int count) {
    // копирование массива для стандартной функции qsort
    int* items_qsort = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        items_qsort[i] = items[i];
    }

    // измерение времени для стандартной функции qsort
    clock_t start_qsort = clock();
    qsort(items_qsort, count, sizeof(int), compare);
    clock_t end_qsort = clock();
    float time_qsort = (float)(end_qsort - start_qsort) / (float)(CLOCKS_PER_SEC);

    // Вывод результатов
    printf("time_qsort: %f\n", time_qsort);

    // освобождение памяти
    free(items_qsort);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int count = 100000; // размер массива
    int* items = (int*)malloc(count * sizeof(int));
    int i;

    // случайный массив
    srand(time(NULL));
    for (i = 0; i < count; i++) {
        items[i] = rand();
    }
    printf("случайный массив:\n");
    test_qsort(items, count);

    // возрастающий массив
    for (i = 0; i < count; i++) {
        items[i] = i;
    }
    printf("\nвозрастающий массив:\n");
    test_qsort(items, count);

    // убывающий массив
    for (i = 0; i < count; i++) {
        items[i] = count - i - 1;
    }
    printf("\nубывающий массив:\n");
    test_qsort(items, count);

    // массив, одна половина которого возрастающая, а другая убывающая
    for (i = 0; i < count / 2; i++) {
        items[i] = i;
    }
    for (i = count / 2; i < count; i++) {
        items[i] = count - i - 1;
    }
    printf("\nмассив, одна половина которого возрастающая, а другая убывающая:\n");
    test_qsort(items, count);

    // освобождение памяти
    free(items);

    getchar();
    return 0;
}
