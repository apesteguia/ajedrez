#include "vec.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vec_init(Vec *v, size_t size) {
    v->size = size;
    v->len = 0;
    v->cap = 0;
    v->array = NULL;
}

Vec *vec_new(size_t size) {
    Vec *v;

    v = (Vec *)malloc(sizeof(Vec));
    v->array = NULL;
    v->cap = 0;
    v->len = 0;
    v->size = size;

    return v;
}

int vec_push(Vec *v, void *elem) {
    if (v->len == 0) {
        v->cap = INITIAL_CAP;
        v->array = malloc(v->cap * v->size);
        if (v->array == NULL) {
            return -1;
        }
    }

    if (v->len == v->cap) {
        v->cap *= 2;
        void *temp = realloc(v->array, v->cap * v->size);
        if (temp == NULL) {
            return -1;
        }
        v->array = temp;
    }

    memcpy((char *)v->array + (v->len * v->size), elem, v->size);

    v->len++;

    return 0;
}

void *vec_pop(Vec *v) {
    if (vec_empty(v)) {
        return NULL;
    }

    v->len--;

    void *return_value = malloc(v->size);
    if (return_value == NULL) {
        return NULL;
    }

    memcpy(return_value, (char *)v->array + (v->len * v->size), v->size);

    return return_value;
}

bool vec_empty(const Vec *v) {
    return (v == NULL || v->len == 0 || v->array == NULL);
}

size_t vec_capacity(const Vec *v) { return v->cap; }

size_t vec_len(const Vec *v) { return v->len; }

void vec_free(Vec *v) {
    free(v->array);
    free(v);
}

void *vec_get(Vec *v, size_t index) {
    if (vec_empty(v) || index >= v->len)
        return NULL;

    void *value = (void *)malloc(v->size);
    if (value == NULL)
        return NULL;

    memcpy(value, (char *)v->array + (v->size * v->len), v->size);

    return value;
}

int vec_insert(Vec *v, void *elem, size_t index) {
    if (index > v->len) {
        return -1;
    }

    if (v->len == v->cap) {
        v->cap = v->cap > 0 ? v->cap * 2 : INITIAL_CAP;
        void *temp = realloc(v->array, v->cap * v->size);
        if (temp == NULL) {
            return -1;
        }
        v->array = temp;
    }

    for (size_t i = v->len; i > index; i--) {
        memcpy((char *)v->array + (v->size * i),
               (char *)v->array + (v->size * (i - 1)), v->size);
    }
    memcpy((char *)v->array + (v->size * index), elem, v->size);

    v->len++;

    return 0;
}

int vec_remove(Vec *v, size_t index) {
    if (vec_empty(v) || index > v->len)
        return -1;

    if (v->len == 1)
        v->len = 0;
    else if (v->len == index)
        v->len--;
    else {
        for (int i = index; i < v->len; i++) {
            memcpy((char *)v->array + (v->size * i),
                   (char *)v->array + (v->size * i + 1), v->size);
        }
        v->len--;
    }

    return 0;
}

void vec_clear(Vec *v) {
    if (v) {
        v->len = 0;
    }
}

int vec_resize(Vec *v, size_t cap) {
    if (v->cap == cap)
        return 0;

    void *tmp = (void *)realloc(v->array, cap * v->size);
    if (tmp == NULL)
        return -1;

    v->array = tmp;
    v->cap = cap;

    return 0;
}

void vec_foreach(Vec *v, void (*f)(void *)) {
    if (vec_empty(v))
        return;

    for (size_t i = 0; i < v->len; i++) {
        f((char *)v->array + (v->size * i));
    }
}

// EXAMPLE FOR INT
static void foreach_example(void *elem) { printf("%d\n", *(int *)elem); }

int vec_find(Vec *v, void *elem, bool (*f)(void *, void *)) {
    if (vec_empty(v))
        return -1;

    for (size_t i = 0; i < v->len; i++) {
        if (f((char *)v->array + (v->size * i), elem)) {
            return i;
        }
    }

    return -1;
}

// EXAMPLE FOR INT
static bool find_example(void *list_element, void *my_element) {
    return *(int *)list_element == *(int *)my_element;
}

void dbg_print(const Vec *v) {
    printf("%p\n", &v->array[10]);
    printf("%p\n", (char *)v->array + (v->size * 10));
}
