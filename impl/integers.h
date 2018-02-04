#include <cstdint>
#include <iostream>
using namespace std;


class W_m;
class W_mxm;
class N_m;
class N_mxm;

char* str(W_m);  
char* left_right_fix(char*);

class W_m {
    public:
    unsigned char datum;
    W_m();
    W_m(unsigned int); 
    W_m operator+(W_m);
    W_m operator-(W_m);
    W_mxm operator*(W_m);
    W_m operator%(W_m);
    W_m operator<<(unsigned char);
    W_m operator>>(unsigned char);
    W_m operator~();
    bool operator==(W_m);
};

W_m uhalf(W_m);
W_m lhalf(W_m);
W_m uhalf(W_mxm);
W_m lhalf(W_mxm);
N_m uhalf(N_mxm);
N_m lhalf(N_mxm);
W_m toW_m(N_m);

class W_mxm {
    public:
    W_m datum[2];
};

class N_m {
    public:
    W_m datum;
    N_m(W_m);
    N_m(unsigned int);
    N_m operator+(N_m);
    N_m operator-(N_m);
    N_mxm operator*(N_m);
};

class N_mxm {
    public:
    N_m datum[2];  
};

N_m::N_m(W_m w) {
    datum = w;
}

N_m N_m::operator+(N_m n2) {
    N_m result = {datum};
    result.datum = result.datum + n2.datum;
    return result;
}

N_m N_m::operator-(N_m n2) {
    N_m result = {datum};
    result.datum = result.datum - n2.datum;
    return result;
}

N_m uhalf(N_mxm n) {
    N_m result(n.datum[1]);
    return result;
}

N_m lhalf(N_mxm n) {
    N_m result(n.datum[0]);
    return result;
}

W_m toW_m(N_m n) {
    return ~n.datum + W_m(1);
}

W_m uhalf(W_mxm w) {
    return w.datum[1];
}

W_m lhalf(W_mxm w) {
    return w.datum[0];
}

W_mxm W_m::operator*(W_m scalar) {
    W_m w1, w2, w3, w4, upper, inner, lower;
    W_mxm result;
    w1 = uhalf(*this);
    w2 = lhalf(*this);
    w3 = uhalf(scalar);
    w4 = lhalf(scalar);
    upper.datum = w1.datum * w3.datum;
    inner.datum = w1.datum*w4.datum + w2.datum*w3.datum;
    lower.datum = w2.datum * w4.datum;
    result.datum[1] = upper + uhalf(inner);
    result.datum[0] = lower + (lhalf(inner) << (sizeof(W_m) << 2));
    return result;
}

W_m::W_m() {
    datum = 0;
}

W_m::W_m(unsigned int w) {
    datum = w;
}

W_m W_m::operator~() {
    W_m result = {datum};
    result.datum = ~result.datum;
    return result;
}

bool W_m::operator==(W_m w2) {
    return (datum == w2.datum);
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

W_m W_m:: operator>>(unsigned char dist) {
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

W_m uhalf(W_m w) {
    w.datum >>= (sizeof(W_m) << 2);
    return w;
}

W_m lhalf(W_m w) {
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
