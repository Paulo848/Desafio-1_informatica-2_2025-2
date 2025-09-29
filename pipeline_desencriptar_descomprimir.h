#ifndef PIPELINE_DESENCRIPTAR_DESCOMPRIMIR_H
#define PIPELINE_DESENCRIPTAR_DESCOMPRIMIR_H

int procesar_lote_archivos();

bool encontrar_rot_y_key(const unsigned char* encriptado, int len_encrip,
                         const unsigned char* pista, int len_pista,
                         int& rot_out, unsigned char& key_out, int& index_out,
                         bool& RLE, bool& LZ78);

void desencriptar_descomprimir(const unsigned char* pista, int len_pista,
                               const unsigned char* encriptado, int len_encrip,
                               unsigned char*& out, int& len_out, int n,
                               char*& metodo_compresion_out,
                               unsigned char& key_out, int& rot_out);

#endif // PIPELINE_DESENCRIPTAR_DESCOMPRIMIR_H
