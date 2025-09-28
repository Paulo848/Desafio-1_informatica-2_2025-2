#ifndef FUNCIONES_H
#define FUNCIONES_H

void rotar_right_bytes(const unsigned char* src,int n);
bool comparar(const unsigned char* a, const unsigned char* b, int len);
void aplicar_xor_y_rotar(const unsigned char* enc, unsigned char* out, int len, int key, int rot);
int buscar_exacta(const unsigned char* text, int n,
                  const unsigned char* pat,  int m);
static inline int similitud_en(const unsigned char* text, int n,
                               const unsigned char* pat,  int m,
                               int start);
void mejor_similitud(const unsigned char* text, int n,
                     const unsigned char* pat,  int m,
                     int& pos_mejor, int& coincidencias_mejor);
bool imprimible_basico(unsigned char c);
void print_buffer_imprimible(const unsigned char* buf, int len);
void encontrar_pistaencad();
bool encontrar_rot_y_key(const unsigned char* enc, int enc_len,
                         const unsigned char* pista, int pista_len,
                         int* rot_out, int* key_out, int* index_out);
#endif // FUNCIONES_H
