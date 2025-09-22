#include <iostream>
using namespace std;

// rota a la derecha k bits cada byte
void rotar_right_bytes(const unsigned char* src, unsigned char* dst, int len, int k) {
    k &= 7;
    if (k == 0) {
        for (int i = 0; i < len; i++) dst[i] = src[i];
        return;
    }
    int lk = 8 - k;
    for (int i = 0; i < len; i++) {
        unsigned int b = src[i];
        unsigned int r = ((b >> k) | ((b << lk) & 0xFFu)) & 0xFFu;
        dst[i] = (unsigned char)r;
    }
}

// compara dos cadenas/arreglos de tamaño len
bool comparar(const unsigned char* a, const unsigned char* b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}
