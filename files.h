#ifndef FILES_H
#define FILES_H

void get_N_Encrip_Pista (unsigned char*& encriptado, int &len_encrip, unsigned char*& pista, int &len_pist, int &N);

void leerArchivoEncriptado_N(char*& out, int N, int &len_enc);
void leerArchivoPista_N(char*& out, int N, int &len_pist);

void leerArchivo(char*& out, const char* nombreArchivo, int &tamano);

#endif // FILES_H
