#ifndef UTILIDADES_H
#define UTILIDADES_H


int comprimirRLE(const char* entrada, int len, char* salida, int* len_out);
void comprimirLZ78(const unsigned char* entrada, int len_in);
void convert_int_doble_char (int n, unsigned char* c1, unsigned char* c2);
static inline void set_len(unsigned char* p, int LT);
static inline int len_(const unsigned char* p);
void rotar_derecha  (unsigned char* in, int bits, unsigned char* out, int size);
void rotar_izquierda(unsigned char* in, int bits, unsigned char* out, int size);
void aplicar_xor(unsigned char* in, unsigned char mask, unsigned char* out, int size);
char* int_to_arr (const int n, int* len_out);

#endif // UTILIDADES_H
