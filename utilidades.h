#ifndef UTILIDADES_H
#define UTILIDADES_H

//void desencriptar_descomprimir(const unsigned char* pista, int len_pista , const unsigned char* encriptado, int len_encrip, unsigned char* &out, int &len_out );
void desencriptar_descomprimir(const unsigned char* pista, int len_pista , const unsigned char* encriptado, int len_encrip, unsigned char* &out, int &len_out , int N );

void comprimirRLE    (const unsigned char* entrada, int len, unsigned char*& out, int& len_out);
void descomprimirRLE (const unsigned char* entrada, int len, unsigned char*& out, int& len_out);
void comprimirLZ78   (const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out);
void descomprimirLZ78(const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out);
void convert_int_doble_char (int n, unsigned char* c1, unsigned char* c2);
static inline void set_len(unsigned char* p, int LT);
static inline int len_of(const unsigned char* p);
void rotar_derecha  (unsigned char* in, int bits, unsigned char* out, int size);
void rotar_izquierda(unsigned char* in, int bits, unsigned char* out, int size);
void aplicar_xor(const unsigned char* in, unsigned char mask, unsigned char* out, int size);
char* int_to_arr (const int n, int* len_out);

void print_arr(const unsigned char* in, int len);
void print_arr_RLE(const unsigned char* in, int len);
void print_arr_LZ(const unsigned char* in, int len);

bool inmprimible(unsigned char un_car);

#endif // UTILIDADES_H
