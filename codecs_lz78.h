#ifndef CODECS_LZ78_H
#define CODECS_LZ78_H

void descomprimirLZ78(const unsigned char* entrada, int len_in,
                      unsigned char*& out, int& len_out);

// Helpers internos (si el .cpp los necesita en línea; no usar fuera del módulo)
static inline int len_of(const unsigned char* p);
static inline void convert_int_doble_char (int n, unsigned char* c1, unsigned char* c2);
static inline void set_len(unsigned char* p, int LT);

#endif // CODECS_LZ78_H
