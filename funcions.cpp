#include <iostream>
#include <funciones.h>
using namespace std;
/*void rotar_right_bytes(const unsigned char* src, unsigned char* dst, int len, int k) {
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

}*/

// rota a la derecha k bits un byte
unsigned char rotar_right_byte(unsigned char b, int k) {
    k &= 7; // normaliza
    if (k == 0) return b;
    int lk = 8 - k;
    unsigned int ub = (unsigned int)b;
    unsigned int r = ((ub >> k) | ((ub << lk) & 0xFFu)) & 0xFFu;
    return (unsigned char)r;
}

// Aplica XOR con key y luego rota a la derecha r bits para el buffer
void aplicar_xor_y_rotar(const unsigned char* enc, unsigned char* out, int len, int key, int rot) {
    for (int i = 0; i < len; ++i) {
        unsigned char t = (unsigned char)(enc[i] ^ (unsigned char)key);
        out[i] = rotar_right_byte(t, rot);
    }
}


//buscar pista en un arreglo
int buscar_exacta(const unsigned char* text, int n,
                  const unsigned char* pat,  int m)
{
    if (!text || !pat || n <= 0 || m <= 0 || m > n) return -1;

    for (int s = 0; s <= n - m; ++s) {
        int i = 0;
        while (i < m && text[s + i] == pat[i]) ++i;
        if (i == m) return s;
    }
    return -1;
}

bool encontrar_rot_y_key(const unsigned char* enc, int enc_len,
                         const unsigned char* pista, int pista_len,
                         int* rot_out, int* key_out, int* index_out) {
    unsigned char buffer[1024];
    if (enc_len > (int)sizeof(buffer)) return false;

    for (int rot = 0; rot < 8; ++rot) {
        for (int key = 0; key < 256; ++key) {
            aplicar_xor_y_rotar(enc, buffer, enc_len, key, rot);
            int pos;
            if (buscar_patron(buffer, enc_len, pista, pista_len, &pos)) {
                *rot_out = rot;
                *key_out = key;
                *index_out = pos;
                return true;
            }
        }
    }
    return false;
}

//BUSCADOR POR SIMILITUD
static inline int similitud_en(const unsigned char* text, int n,
                               const unsigned char* pat,  int m,
                               int start)
{
    int matches = 0;
    for (int i = 0; i < m; ++i) {
        if (text[start + i] == pat[i]) ++matches;
    }
    return matches;
}

//posiciones
void mejor_similitud(const unsigned char* text, int n,
                     const unsigned char* pat,  int m,
                     int& pos_mejor, int& coincidencias_mejor)
{
    pos_mejor = -1; coincidencias_mejor = -1;
    if (!text || !pat || n <= 0 || m <= 0 || m > n) return;

    int best_pos = -1, best_hits = -1;

    for (int s = 0; s <= n - m; ++s) {
        int hits = similitud_en(text, n, pat, m, s);
        if (hits > best_hits) {
            best_hits = hits;
            best_pos  = s;
            if (best_hits == m) break;
        }
    }
    pos_mejor = best_pos;
    coincidencias_mejor = best_hits;
}

bool imprimible_basico(unsigned char c) {
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= '0' && c <= '9') return true;
    if (c == ' ' || c == '.' || c == ',' || c == '_' || c == '-') return true;
    return false;
}

void print_buffer_imprimible(const unsigned char* buf, int len) {
    for (int i = 0; i < len; ++i) {
        cout << (imprimible_basico(buf[i]) ? (char)buf[i] : '#');
    }
    cout << "\n";
}

void encontrar_pistaencad() {
    //const unsigned char decomp[] = "abcxyyyyzzzza123xyyyyzxyzfin";
    //const int len_decomp = (int)(sizeof(decomp) - 1);

    //const unsigned char pista[] = "xyyyyzzzza";
    //const int len_pista = (int)(sizeof(pista) - 1);

    int idx = buscar_exacta(decomp, len_decomp, pista, len_pista);
    if (idx >= 0) {
        cout << "encontrado en pos: " << idx << "\n";
    } else {
        cout << "no encontrado.\n";
    }

    int pos_mejor = -1, hits = -1;
    mejor_similitud(decomp, len_decomp, pista, len_pista, pos_mejor, hits);
    if (pos_mejor >= 0) {
        double score = (double)hits / (double)len_pista;
        cout << "mejor pos: " << pos_mejor
                  << "aciertos: " << hits << "/" << len_pista
                  << "score: " << score << "\n";
    } else {
        cout << "no aplica.\n";
    }
    return 0;
}
