#include "edu_search.h"
#include "edu_cmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

size_t edu_linear_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    if (ptr == NULL || key == NULL || cmp == NULL || size == 0) {
        return count;
    }
    
    const char *base = (const char *)ptr;
    for (size_t i = 0; i < count; i++) {
        const void *current = base + i * size;
        if (cmp(current, key) == 0) {
            return i;
        }
    }
    
    return count;
}

size_t edu_binary_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    if (ptr == NULL || key == NULL || cmp == NULL || size == 0) {
        return count;
    }
    
    const char *base = (const char *)ptr;
    size_t left = 0;
    size_t right = count;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        const void *mid_element = base + mid * size;
        int comparison = cmp(mid_element, key);
        
        if (comparison == 0) {
            return mid;
        } else if (comparison < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return count;
}
