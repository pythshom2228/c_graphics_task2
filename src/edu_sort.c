#include "edu_sort.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

static void edu_swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void edu_bubble_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    int edu_swapped = 1;

    while (edu_swapped) {
        edu_swapped = 0;
        for (size_t i = 0; i < count - 1; ++i) {
            void *val1 = (char *) ptr + i * size;
            void *val2 = (char *) ptr + (i + 1) * size;
            if (cmp(val1, val2) > 0) {
                edu_swap(val1, val2, size);
                edu_swapped = 1;
            }
        }
        --count;
    }
}
void edu_selection_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || cmp == NULL || count == 0 || size == 0) return;
    
    char *base = (char *)ptr;
    for (size_t i = 0; i < count - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < count; j++) {
            if (cmp(base + j * size, base + min_idx * size) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            edu_swap(base + i * size, base + min_idx * size, size);
        }
    }
}

void edu_insertion_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || cmp == NULL || count == 0 || size == 0) return;
    
    char *base = (char *)ptr;
    for (size_t i = 1; i < count; i++) {
        size_t j = i;
        while (j > 0 && cmp(base + j * size, base + (j - 1) * size) < 0) {
            edu_swap(base + j * size, base + (j - 1) * size, size);
            j--;
        }
    }
}

void edu_shell_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || cmp == NULL || count == 0 || size == 0) return;
    
    char *base = (char *)ptr;
    
    size_t gap = 1;
    while (gap < count / 3) {
        gap = gap * 3 + 1;
    }
    
    while (gap > 0) {
        for (size_t i = gap; i < count; i++) {
            size_t j = i;
            while (j >= gap && cmp(base + j * size, base + (j - gap) * size) < 0) {
                edu_swap(base + j * size, base + (j - gap) * size, size);
                j -= gap;
            }
        }
        gap /= 3;
    }
}

static size_t partition(void *ptr, size_t low, size_t high, size_t size, edu_cmp cmp) {
    char *base = (char *)ptr;
    void *pivot = base + high * size;
    size_t i = low;
    
    for (size_t j = low; j < high; j++) {
        if (cmp(base + j * size, pivot) <= 0) {
            edu_swap(base + i * size, base + j * size, size);
            i++;
        }
    }
    edu_swap(base + i * size, base + high * size, size);
    return i;
}

static void quick_sort_recursive(void *ptr, size_t low, size_t high, size_t size, edu_cmp cmp) {
    if (low < high) {
        size_t pi = partition(ptr, low, high, size, cmp);
        if (pi > 0) { // предотвращение underflow
            quick_sort_recursive(ptr, low, pi - 1, size, cmp);
        }
        quick_sort_recursive(ptr, pi + 1, high, size, cmp);
    }
}

void edu_quick_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || cmp == NULL || count == 0 || size == 0) return;
    quick_sort_recursive(ptr, 0, count - 1, size, cmp);
}

static void heapify(void *ptr, size_t count, size_t size, edu_cmp cmp, size_t root) {
    char *base = (char *)ptr;
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;
    
    if (left < count && cmp(base + left * size, base + largest * size) > 0) {
        largest = left;
    }
    
    if (right < count && cmp(base + right * size, base + largest * size) > 0) {
        largest = right;
    }
    
    if (largest != root) {
        edu_swap(base + root * size, base + largest * size, size);
        heapify(ptr, count, size, cmp, largest);
    }
}

void edu_heap_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || cmp == NULL || count == 0 || size == 0) return;
    
    char *base = (char *)ptr;
    
    for (size_t i = count / 2; i > 0; i--) {
        heapify(ptr, count, size, cmp, i - 1);
    }
    
    for (size_t i = count - 1; i > 0; i--) {
        edu_swap(base, base + i * size, size);
        heapify(ptr, i, size, cmp, 0);
    }
}

void edu_counting_sort(void *ptr, size_t count, size_t size, edu_counting_sort_order_e order) {
    if (ptr == NULL || count == 0 || size == 0) return;
    
    if (size != sizeof(int) && size != sizeof(unsigned int)) {
        return; // Неподдерживаемый тип
    }
    
    char *base = (char *)ptr;
    
    int min = INT_MAX, max = INT_MIN;
    for (size_t i = 0; i < count; i++) {
        int value = *(int *)(base + i * size);
        if (value < min) min = value;
        if (value > max) max = value;
    }
    
    size_t range = max - min + 1;
    size_t *count_arr = (size_t *)calloc(range, sizeof(size_t));
    if (count_arr == NULL) return;
    
    for (size_t i = 0; i < count; i++) {
        int value = *(int *)(base + i * size);
        count_arr[value - min]++;
    }
    
    size_t index = 0;
    if (order == EDU_COUNTING_SORT_ASC) {
        for (size_t i = 0; i < range; i++) {
            while (count_arr[i] > 0) {
                *(int *)(base + index * size) = (int)(i + min);
                count_arr[i]--;
                index++;
            }
        }
    } else { // EDU_COUNTING_SORT_DESC
        for (size_t i = range; i > 0; i--) {
            while (count_arr[i - 1] > 0) {
                *(int *)(base + index * size) = (int)((i - 1) + min);
                count_arr[i - 1]--;
                index++;
            }
        }
    }
    
    free(count_arr);
}
