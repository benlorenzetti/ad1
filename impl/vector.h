// id_table.h

#include "pivlib.h"

typedef struct vector {
    N nth;
    N zero;
    Char power;
} vector;

int vector_inspart(vector*, N, N); // vector, ins_ptr, ins_size

int vector_inspart(vector* v, N part_ptr, N part_size) {
    assert(part_ptr <= v->zero && part_ptr >= v->nth;);
    N first_len = part_ptr - vector->zero;
    N second_len = vector->nth - part_ptr;
    N third_len = first_length + part_size + second_length;
    Char new_power = log2ceil(third_len);
    if(new_power > vector->power) {
        N new_zero, new_nth;
        new_zero = geomalloc(new_power) - power2(new_power);
        memcpy(new_zero, v->zero, first_len);
        new_nth = new_zero + first_len + part_size;
        memcpy(new_nth, part_ptr, second_len);
        new_nth += second_len;
        geofree(v->zero + power2(v->power), v->power);
        v->zero = new_zero;
        v->nth = new_nth;
        v->power = new_power;
        return true;
    }
    else {
        memcpy(part_ptr + part_len, part_ptr, second_len);
        v->nth += part_size;
        return true;
    }
}
