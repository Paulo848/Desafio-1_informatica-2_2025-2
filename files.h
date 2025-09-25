#ifndef FILES_H
#define FILES_H

void get_N_Encrip_Pista (unsigned char*& encriptado, int &len_encrip, unsigned char*& pista, int &len_pist, int &N);

void leerArchivoEncriptado_N(char*& out, int N, int &len_enc);
void leerArchivoPista_N(char*& out, int N, int &len_pist);

void leerArchivo(char*& out, const char* nombreArchivo, int &tamano);
void escribirArchivo(const char* in, const char* nombreArachivo, int len);

void escribir_cadena_original(const unsigned char* in, int N, int len_in);
void escribirArchivo(const unsigned char* in, const char* nombreArachivo, int len_in);

#endif // FILES_H
