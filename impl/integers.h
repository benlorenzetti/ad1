#include <cstdint>
#include <iostream>
using namespace std;


class W_m;
class W_2m;

char* str(W_m);  
char* left_right_fix(char*);

class W_m {
    public:
    unsigned char datum;
    W_m operator+(W_m);
    W_m operator-(W_m);
    W_m operator*(W_m);
    W_m operator/(W_m);
    W_m operator%(W_m);
    W_m operator<<(unsigned char);
};

W_m upperhalf(W_m);
W_m lowerhalf(W_m);

class W_mxm {
    public:
    W_m datum[2];
    W_mxm(W_m, W_m);
};

W_m upperhalf(W_mxm);
W_m lowerhalf(W_mxm);

W_m upperhalf(W_mxm w) {
    return w.datum[1];
}

W_m lowerhalf(W_mxm w) {
    return w.datum[0];
}

W_mxm::W_mxm(W_m base, W_m scalar) {
    W_m w1, w2, w3, w4, upper, inner, lower;
    w1 = upperhalf(base);
    w2 = lowerhalf(base);
    w3 = upperhalf(scalar);
    w4 = lowerhalf(scalar);
    upper = w1 * w3;
    inner = w1*w4 + w2*w3;
    lower = w2 * w4;
    datum[1] = upper + upperhalf(inner);
    datum[0] = lower + (lowerhalf(inner) << (sizeof(W_m) << 2));
}

W_m W_m::operator*(W_m w2) {
    W_m result = {datum};
    result.datum *= w2.datum;
    return result;
}

W_m W_m::operator/(W_m w2) {
    W_m result = {datum};
    result.datum /= w2.datum;
    return result;
}

W_m W_m::operator%(W_m w2) {
    W_m result = {datum};
    result.datum %= w2.datum;
    return result;
}

W_m W_m:: operator<<(unsigned char dist) {
    W_m result = {datum};
    result.datum <<= dist;
    return result;
}

W_m W_m::operator+(W_m w2) {
    W_m result;
    result.datum = datum + w2.datum;
    return result;
}

W_m W_m::operator-(W_m w2) {
    W_m result;
    result.datum = datum - w2.datum;
    return result;
}

W_m upperhalf(W_m w) {
    w.datum >>= (sizeof(W_m) << 2);
    return w;
}

W_m lowerhalf(W_m w) {
    uintptr_t MASK = 1;
    MASK <<= sizeof(W_m) << 2;
    MASK -= 1;
    w.datum = w.datum & MASK;
    return w;
}

char* str(W_m w) {
    static char string[1 + sizeof(W_m) / 3];
    int i = 0;
    do {
        string[i] = '0' + w.datum % 10;
        w.datum /= 10;
        i++;
    } while (w.datum);
    string[i] = 0;
    left_right_fix(string);
    return string;   
}

char* left_right_fix(char* str) {
    int len = 0;
    while(str[len])
        len++;
    int i = 0;
    char tmp;
    while(len > i) {
        len--;
        tmp = str[len];
        str[len] = str[i];
        str[i] = tmp;
        i++;
    }
    return str;
}
/*
class W_2m {
    public:
    uintptr_t datum[2];  
};

class Nat {
    public:
    uintptr_t datum;
    Nat(unsigned int uint) { uintptr_t w = uint; datum = -w; }
    Nat() { datum = 0; }
    unsigned int touint() { return (unsigned int)(-datum); }
    Nat operator+(Nat n2) { 
        Nat result;
        result.datum = datum + n2.datum;
        return result;
    }
    Nat operator-(Nat n2) {
        Nat result;
        result.datum = datum - n2.datum;
        return result;
    }
//    Nat operator+(Whol w2) { return datum-w2.datum; }
//    Nat operator-(Whol w2) { return datum+w2.datum; }
    Natsquared operator*(Nat n2) {
        Natsquared result;
        result.datum[0] = -(datum * n2.datum);
        return result;
    }
    Nat operator/(Nat n2) {
        Nat result;
        result.datum = datum / (-n2.datum) + (UINTPTR_MAX >> 1) + 1;
        return result;
    }
};

*/
