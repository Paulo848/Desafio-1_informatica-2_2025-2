#ifndef UTILS_H
#define UTILS_H

// Conversión numérica (caller debe delete[] del char* devuelto)
char* int_to_arr(int n, int* len_out);

// Validación de carácter “imprimible”
bool imprimible(unsigned char un_car);

// Debug/impresión (opcionales)
void print_arr(const unsigned char* in, int len);
void print_arr_RLE(const unsigned char* in, int len);
void print_arr_LZ(const unsigned char* in, int len);

bool buscar_patron(const unsigned char* text, int n,
                   const unsigned char* pista,  int m,
                   int* pos_out);

#endif // UTILS_H
