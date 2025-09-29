#include "crypto_xor_rot.h"

void rotar_derecha(unsigned char* in, int bits, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = (in[i] >> bits) | (in[i] << (8 - bits));
    }
}

void rotar_izquierda(unsigned char* in, int bits, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = (in[i] << bits) | (in[i] >> (8 - bits));
    }
}

void aplicar_xor(const unsigned char* in, unsigned char mask, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = in[i] ^ mask;
    }
}

void aplicar_xor_y_rotar(const unsigned char* entrada, int len_in, unsigned char* out, unsigned char key, int rot) {
    for (int i = 0; i < len_in; ++i) {
        unsigned char i_xor = entrada[i] ^ key;
        out[i] = rotar_right_byte(i_xor, rot);
    }
}

unsigned char rotar_right_byte(unsigned char b, int k) {
    k &= 7;
    if (k == 0) return b;
    int lk = 8 - k;
    unsigned int ub = (unsigned int)b;
    unsigned int r = ((ub >> k) | ((ub << lk) & 0xFFu)) & 0xFFu;
    return (unsigned char)r;
}
