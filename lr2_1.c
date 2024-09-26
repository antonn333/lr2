#include <stdio.h>
#include <limits.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end; // объявляем переменные для определения времени выполнения

    int i, j, r;
    int n = 4000; // размер матрицы

    // динамическое выделение памяти для матриц
    int** a = (int**)malloc(n * sizeof(int*));
    int** b = (int**)malloc(n * sizeof(int*));
    int** c = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
        c[i] = (int*)malloc(n * sizeof(int));
    }

    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
        }
    }

    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
        }
    }

    start = clock(); // начало измерения времени
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int elem_c = 0;
            for (r = 0; r < n; r++) {
                elem_c = elem_c + a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }
    end = clock(); // конец измерения времени

    float t = (float)(end - start) / (float)(CLOCKS_PER_SEC);
    printf("time: %f\n", t);

    // освобождение выделенной памяти
    for (i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    getchar();
    return 0;
}