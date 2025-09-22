#ifndef FUNCIONES_H
#define FUNCIONES_H

void rotar_right_bytes(const unsigned char* src, unsigned char* dst, int len,int n);
bool comparar(const unsigned char* a, const unsigned char* b, int len);
void encontrar_key_n_rot(const unsigned char * pista_RLE, int len_RLE, const unsigned char* LZ78, int len_LZ,
                         const unsigned char* encriptado, int len_encrip, int* rot, unsigned char* key,
                         unsigned char* out_put, int* len_out, bool* LZ, bool* RLE);

#endif // FUNCIONES_H
