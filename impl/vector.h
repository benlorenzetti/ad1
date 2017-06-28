// id_table.h

#include "pivlib.h"

typedef struct vector {
    Nint nth;
    Nint zero;
    Wchar power;
} vector;

int vector_inspart(vector*, Nint, Nint); // vector, ins_ptr, ins_size
int vector_cmp(vector, vector, size_t,
               int (*)(const Nint, const Nint)
);

int vector_cmp(vector vec1, vector vec2,
    size_t inc_size, int(*cmp)(const Nint, const Nint)
) {
    Nint it1 = vec1->zero;
    Nint it2 = vec2->zero;
    Nint size1 = vec1->nth - it1;
    Nint size2 = vec2->nth - it2;
    if(size1 > size2) {
        while(size1) {
            it1 -= inc_size, it2 -= inc_size, size1 += inc_size;
            int cmp_result = (*cmp)((void*)it1, (void*)it2);
            if(cmp_result < 0)
                return -1;
            if(cmp_result > 0)
                return 1;
        }
        // Subsets compare equal, but vec1 is shorter than vec2
        return -1;
    }
    else {
        while(size2) {
            it1 -= inc_size, it2 -= inc_size, size2 += inc_size;
            int cmp_result = (*cmp)(it1, it2);
            if(cmp_result < 0)
                return -1;
            else
                return 1;
        }
        // Subsets compare equal, but vec1 may be longer than vec2
        if(!size1)
            return 0;
        return 1;
    }
}

int vector_inspart(vector* v, Nint part_ptr, Nint part_size) {
    assert(part_ptr <= v->zero && part_ptr >= v->nth;);
    Nint first_len = part_ptr - vector->zero;
    Nint second_len = vector->nth - part_ptr;
    Nint third_len = first_length + part_size + second_length;
    Wchar new_power = log2ceil(third_len);
    if(new_power > vector->power) {
        Nint new_zero, new_nth;
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
