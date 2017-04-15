#include <stdio.h>
#include <stdlib.h>

#define bad_alloc 1
#define ok 0

typedef struct vector {
    long long *array;
    int real_size;
    int buffer_size;
} Vector;

//Конструктор вектора
int init(Vector *vector) {
    vector->real_size = 0;
    vector->buffer_size = 3;
    vector->array = (long long *) malloc (vector->buffer_size * sizeof(long long));
    if (!vector->array) return bad_alloc;
    return ok;
}

//Деструктор вектора
void destroy(Vector *vector) {
    free(vector->array);
}

// Увеличение буфера
int grow(Vector *vector) {
    int new_buffer_size = vector->buffer_size * 2;
    long long *new_array = (long long *) malloc (new_buffer_size * sizeof(long long));
    if (!new_array) return bad_alloc;
    for (int i = 0; i < vector->real_size; i++) new_array[i] = vector->array[i];
    free(vector->array);
    vector->array = new_array;
    vector->buffer_size = new_buffer_size;
    return ok;
}

// Добавление еще одной размерности в векторе.
int add_dimension(Vector *vector, long long value) {
    int error = ok;
    if (vector->real_size == vector->buffer_size) error = grow(vector);
    if (error != ok) return error;
    vector->array[vector->real_size] = value;
    vector->real_size++;
    return error;
}

Vector* addition(Vector *vector1, Vector *vector2) {
    Vector *result = (Vector *) malloc(sizeof(Vector));
    if (!result) return NULL;
    if (init(result) != ok) return NULL;
        if (vector1->real_size > vector2->real_size) {
            for (int i = 0; i < vector2->real_size; i++)
                if (add_dimension(result, vector1->array[i] + vector2->array[i]) != ok) {
                    destroy(result);
                    return NULL;
                }
            for (int i = vector2->real_size; i < vector1->real_size; i++)
                if (add_dimension(result, vector1->array[i]) != ok) {
                    destroy(result);
                    return NULL;
                }
        }
        else {
            for (int i = 0; i < vector1->real_size; i++)
                if (add_dimension(result, vector1->array[i] + vector2->array[i]) != ok) {
                    destroy(result);
                    return NULL;
                }
            for (int i = vector1->real_size; i < vector2->real_size; i++)
                if (add_dimension(result, vector2->array[i]) != ok) {
                    destroy(result);
                    return NULL;
                }
        }
    return result;
}

Vector* subtraction(Vector *vector1, Vector *vector2) {
    Vector *result = (Vector *) malloc(sizeof(Vector));
    if (!result) return NULL;
    if (init(result) != ok) return NULL;
    if (vector1->real_size > vector2->real_size) {
        for (int i = 0; i < vector2->real_size; i++)
            if (add_dimension(result, vector1->array[i] - vector2->array[i]) != ok) {
                destroy(result);
                return NULL;
            }
        for (int i = vector2->real_size; i < vector1->real_size; i++)
            if (add_dimension(result, vector1->array[i]) != ok) {
                destroy(result);
                return NULL;
            }
    }
    else {
        for (int i = 0; i < vector1->real_size; i++)
            if (add_dimension(result, vector1->array[i] - vector2->array[i]) != ok) {
                destroy(result);
                return NULL;
            }
        for (int i = vector1->real_size; i < vector2->real_size; i++)
            if (add_dimension(result, -vector2->array[i]) != ok) {
                destroy(result);
                return NULL;
            }
    }
    return result;
}

Vector* multiplication(Vector *vector1, Vector *vector2) {
    Vector *result = (Vector *) malloc(sizeof(Vector));
    if (!result) return NULL;
    if (init(result) != ok) return NULL;
    if (vector1->real_size < vector2->real_size) {
        for (int i = 0; i < vector2->real_size; i++)
            if (add_dimension(result, vector2->array[i] * vector1->array[0]) != ok) {
                destroy(result);
                return NULL;
            }
    }
    else {
        for (int i = 0; i < vector1->real_size; i++)
            if (add_dimension(result, vector1->array[i] * vector2->array[0]) != ok) {
                destroy(result);
                return NULL;
            }
    }
    return result;
}

int main() {
    Vector *vector1 = (Vector *) malloc(sizeof(Vector)),
            *vector2 = (Vector *) malloc(sizeof(Vector));
    if (init(vector1) != ok) {
        printf("[error]");
        return 0;
    }
    if (init(vector2) != ok) {
        printf("[error]");
        return 0;
    }
    for (int i = 0; i < 8; i++) add_dimension(vector1, i);
    for (int i = 0; i < 3; i++) add_dimension(vector2, i);
//    for (int i = 0; i < 8; i++) printf("%lli ", vector1.array[i]);
//    Vector vector3;
//    init(&vector3);
//    add_dimension(&vector3, 2);
//    multiplication(&vector3, &vector1);

    for (int i = 0; i < vector1->real_size; i++) printf("%lli ", vector1->array[i]);
    printf("\n");
//    for (int i = 0; i < vector2->real_size; i++) printf("%lli ", vector2->array[i]);
//    printf("\n");
//    Vector *vector3 = addition(vector2, vector1);
//    Vector *vector3 = subtraction(vector2, vector1);
//    for (int i = 0; i < vector3->real_size; i++) printf("%lli ", vector3->array[i]);
//    printf("\n");
    Vector *vector3 = (Vector *) malloc(sizeof(Vector));
    init(vector3);
    add_dimension(vector3, 3);
    Vector *vector4 = multiplication(vector3, vector1);
    for (int i = 0; i < vector4->real_size; i++) printf("%lli ", vector4->array[i]);
    printf("\n");


    destroy(vector1);
    destroy(vector2);
    destroy(vector3);
    destroy(vector4);
    return 0;
}