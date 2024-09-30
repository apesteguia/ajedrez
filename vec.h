#ifndef MAG_VEC
#define MAG_VEC

#include <stdbool.h>
#include <stdio.h>

#define INITIAL_CAP 4

typedef struct {
    void *array;
    size_t cap;
    size_t len;
    size_t size;
} Vec;

void vec_init(Vec *, size_t);
Vec *vec_new(size_t);
int vec_push(Vec *, void *);
size_t vec_capacity(const Vec *);
size_t vec_len(const Vec *);
bool vec_empty(const Vec *);
void vec_free(Vec *);
void *vec_pop(Vec *);
void *vec_get(Vec *v, size_t index);
int vec_insert(Vec *, void *, size_t);
void vec_clear(Vec *);
int vec_resize(Vec *, size_t);
int vec_remove(Vec *, size_t);
void vec_foreach(Vec *, void (*)(void *));
int vec_find(Vec *, void *, bool (*)(void *, void *));
void dbg_print(const Vec*);

#endif
