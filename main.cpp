#include <iostream>
#include <funciones.h>
using namespace std;

bool buscar_patron(const unsigned char* text, int text_len,
                   const unsigned char* pat, int pat_len,
                   int* pos) {
    if (pat_len > text_len) return false;
    for (int i = 0; i <= text_len - pat_len; ++i) {
        bool ok = true;
        for (int j = 0; j < pat_len; ++j) {
            if (text[i + j] != pat[j]) { ok = false; break; }
        }
        if (ok) { *pos = i; return true; }
    }
    return false;
}

/*
  Busca rotacion (0..7) y key (0..255) tal que, al aplicar:
    tmp = (enc[i] XOR key) rotado_right(rot)
  el arreglo tmp contenga 'pista' como subsecuencia contigua.
  Devuelve true si encontró alguna combinación. Si sí, escribe rot, key e index.
*/


int main() {
    unsigned char original[16] = { 'H','E','L','L','O','H','E','L','L','O','H','E','L','L','O','s' };
    int n = 16;

    unsigned char cifrado[16];
    for (int i = 0; i < n; ++i) {
        unsigned char rotleft3 = (unsigned char)(((original[i] << 3) & 0xFFu) | (original[i] >> (8 - 3)));
        cifrado[i] = (unsigned char)(rotleft3 ^ 0x5A);
    }
    unsigned char pista[3] = { 'H','E','L' };

    int found_rot = -1, found_key = -1, found_index = -1;
    bool ok = encontrar_rot_y_key(cifrado, n, pista, 3, &found_rot, &found_key, &found_index);

    if (ok) {
        cout << "Encontrado! rot = " << found_rot
             << ", key = " << found_key
             << ", index = " << found_index << '\n';
        unsigned char buffer[5];
        aplicar_xor_y_rotar(cifrado, buffer, n, found_key, found_rot);
        cout << "Contenido tras desencriptar (decimal): ";
        for (int i = 0; i < n; ++i) cout << (int)buffer[i] << ' ';
        cout << '\n';

        cout << "Contenido tras desencriptar (chars) : ";
        for (int i = 0; i < n; ++i) cout << (char)buffer[i];
        cout << '\n';
    } else {
        cout << "No se encontró ninguna combinacion rot/key que contenga la pista.\n";
    }
    return 0;
}



