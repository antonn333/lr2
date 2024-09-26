#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

int medianOfThree(int* items, int left, int right) {
    int mid = (left + right) / 2;
    if (items[left] > items[mid]) {
        int temp = items[left];
        items[left] = items[mid];
        items[mid] = temp;
    }
    if (items[left] > items[right]) {
        int temp = items[left];
        items[left] = items[right];
        items[right] = temp;
    }
    if (items[mid] > items[right]) {
        int temp = items[mid];
        items[mid] = items[right];
        items[right] = temp;
    }
    return mid;
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    if (left < right) {
        int pivotIndex = medianOfThree(items, left, right);
        x = items[pivotIndex];

        i = left; j = right;

        do {
            while ((items[i] < x) && (i < right)) i++;
            while ((x < items[j]) && (j > left)) j--;

            if (i <= j) {
                y = items[i];
                items[i] = items[j];
                items[j] = y;
                i++; j--;
            }
        } while (i <= j);

        if (left < j) qs(items, left, j);
        if (i < right) qs(items, i, right);
    }
}

int main() {
    int count = 100000; // размер массива
    int* items = (int*)malloc(count * sizeof(int));
    int i;

    // генерация массива, одна половина которого возрастающая, а другая убывающая
    for (i = 0; i < count / 2; i++) {
        items[i] = i;
    }
    for (i = count / 2; i < count; i++) {
        items[i] = count - i - 1;
    }

    // копирование массива для сортировки Шелла
    int* items_shell = (int*)malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        items_shell[i] = items[i];
    }

    // копирование массива для быстрой сортировки
    int* items_qs = (int*)malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        items_qs[i] = items[i];
    }

    // измерение времени для сортировки Шелла
    clock_t start_shell = clock();
    shell(items_shell, count);
    clock_t end_shell = clock();
    float time_shell = (float)(end_shell - start_shell) / (float)(CLOCKS_PER_SEC);

    // измерение времени для быстрой сортировки
    clock_t start_qs = clock();
    qs(items_qs, 0, count - 1);
    clock_t end_qs = clock();
    float time_qs = (float)(end_qs - start_qs) / (float)(CLOCKS_PER_SEC);

    // Вывод результатов
    printf("time_shell_sort: %f\n", time_shell);
    printf("time_quick_sort: %f\n", time_qs);

    // освобождение памяти
    free(items);
    free(items_shell);
    free(items_qs);

    getchar();
    return 0;
}