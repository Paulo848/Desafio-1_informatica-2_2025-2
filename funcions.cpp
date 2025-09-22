#include <iostream>
#include "funciones.h"
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

void encontrar_key_n_rot(const unsigned char * pista_RLE, int len_RLE, const unsigned char* pista_LZ, int len_LZ,
                         const unsigned char* encriptado, int len_encrip, int* rot, unsigned char* key,
                         unsigned char* out_put, int* len_out, bool* LZ, bool* RLE){
    /* comparar RLE desencriptado con pista comprimida enetregada, en RlE se probaran todas las posibles rotaciones hacia la
     derecha.
    const unsigned char* pista_RLE: pista comprimida para comparar parentezco
    int len_RLE: longitud de la cadena de RLE
    const unsigned char* LZ78: pista comprimida para comparar parentezco
    int len_LZ78: longitud de la cadena de LZ78
    ########################################################################
    ENTREGAR UNA CADENA CON LA DESENCRIPTACION HECHA Y ENCONTRADA
    const unsigned char* encriptado: no se que es
    int len_encrip: tamaño de la cadena de encriptado:
    int* rot:
    unsigned char* key
    unsigned char* out_put
    int* len_out
    bool* LZ
    bool* RLE
|   */
    *LZ = false;
    *RLE = false;
    //rotar_right_bytes(const unsigned char *pista_RLE)
    unsigned char rotado[len_encrip];
    for (int n = 0; n < 8; n++) {
        rotar_right_bytes(encriptado, rotado, len_encrip, n);
        bool compa_RLE = comparar(rotado, pista_RLE,len_RLE);
        if(compa_RLE){
            *LZ = true;
        }
        bool compa_LZ = comparar(rotado, pista_LZ, len_LZ);
        if(compa_LZ){
            *RLE = true;
        }
    }
}
