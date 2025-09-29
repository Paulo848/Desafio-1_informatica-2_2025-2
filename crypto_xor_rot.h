#ifndef CRYPTO_XOR_ROT_H
#define CRYPTO_XOR_ROT_H

void aplicar_xor(const unsigned char* in, unsigned char mask,
                 unsigned char* out, int size);

void rotar_derecha(unsigned char* in, int bits,
                   unsigned char* out, int size);

void rotar_izquierda(unsigned char* in, int bits,
                     unsigned char* out, int size);

// Utilizada por el buscador de rot/key
void aplicar_xor_y_rotar(const unsigned char* entrada, int len_in,
                         unsigned char* out, unsigned char key, int rot);

// Byte-rotate (por si se usa fuera)
unsigned char rotar_right_byte(unsigned char b, int k);

#endif // CRYPTO_XOR_ROT_H
