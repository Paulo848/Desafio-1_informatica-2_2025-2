#include "files.h"
#include "utilidades.h"
#include <fstream>
#include <iostream>

void get_N_Encrip_Pista (unsigned char*& encriptado, int &len_encrip, unsigned char*& pista, int &len_pist, int &N){

    char* pista_char;
    char* encriptado_char;

    leerArchivoEncriptado_N(encriptado_char, N, len_encrip);
    leerArchivoPista_N(pista_char, N, len_pist);

    encriptado = new unsigned char[len_encrip];
    for(int idx_encriptado = 0; idx_encriptado < len_encrip; idx_encriptado++ ) encriptado[idx_encriptado] = static_cast<unsigned char>(encriptado_char[idx_encriptado]);

    pista = new unsigned char[len_pist];
    for(int idx_pista = 0; idx_pista < len_pist; idx_pista++ ) pista[idx_pista] = static_cast<unsigned char>(pista_char[idx_pista]);

}

 void leerArchivoEncriptado_N(char*& out, int N, int &len_enc){

    char part_1[] = "Encriptado";
    char part_3[] = ".txt";
    int len_p1 = 0;

    while(part_1[len_p1] != '\0') len_p1++;

    int len_n;
    char* n = int_to_arr(N,&len_n);

    int len_name = len_p1+len_n+4;

    char* name = new char[len_name+1];

    int i = 0;
    int i_1 = 0;
    while(i_1 < len_p1)  name[i++] = part_1[i_1++];
    int i_2 = 0;
    while(i_2 < len_n)   name[i++] = n[i_2++];
    int i_3 = 0;
    while(i_3 < 4)       name[i++] = part_3[i_3++];

    name[i] = '\0';

    delete[] n;

    leerArchivo(out, name, len_enc);

    delete[] name;


}
 void leerArchivoPista_N(char*& out, int N, int &len_pist){

    char part_1[] = "pista";
    char part_3[] = ".txt";
    int len_p1 = 0;

    while(part_1[len_p1] != '\0') len_p1++;

    int len_n;
    char* n = int_to_arr(N,&len_n);

    int len_name = len_p1+len_n+4;

    char* name = new char[len_name+1];

    int i = 0;
    int i_1 = 0;
    while(i_1 < len_p1)  name[i++] = part_1[i_1++];
    int i_2 = 0;
    while(i_2 < len_n)   name[i++] = n[i_2++];
    int i_3 = 0;
    while(i_3 < 4)       name[i++] = part_3[i_3++];

    name[i] = '\0';

    delete[] n;

    leerArchivo(out, name, len_pist);

    delete[] name;


}

 void leerArchivo(char*& out, const char* nombreArchivo, int &tamano)
{
    std :: ifstream archivo(nombreArchivo, std :: ios :: binary);
    if (!archivo.is_open())
    {
        std :: cout << "Error al abrir el archivo : " << nombreArchivo << std :: endl;
        tamano = 0;
        out = nullptr;
        return ;
    }

    archivo.seekg(0, std :: ios::end);
    tamano = archivo.tellg();
    archivo.seekg(0, std :: ios :: beg);

    out = new char[tamano + 1];

    archivo.read(out, tamano);
    out[tamano] = '\0';

    archivo.close();
}

void escribir_cadena_original(const unsigned char* in, int N, int len_in){

    char part_1[] = "original";
    char part_3[] = ".txt";
    int len_p1 = 0;

    while(part_1[len_p1] != '\0') len_p1++;

    int len_n;
    char* n = int_to_arr(N,&len_n);

    int len_name = len_p1+len_n+4;

    char* name = new char[len_name+1];

    int i = 0;
    int i_1 = 0;
    while(i_1 < len_p1)  name[i++] = part_1[i_1++];
    int i_2 = 0;
    while(i_2 < len_n)   name[i++] = n[i_2++];
    int i_3 = 0;
    while(i_3 < 4)       name[i++] = part_3[i_3++];

    name[i] = '\0';

    //char* in_char = new char[len_in];

    //for(int idx_in = 0; idx_in < len_in; idx_in++) in_char[idx_in] = static_cast<char>(in[idx_in]);

    //escribirArchivo(in_char, name, len_in);
    escribirArchivo(in, name, len_in);

    //delete[] in_char;
    delete[] name;

}

void escribirArchivo(const unsigned char* in, const char* nombreArachivo, int len_in){

    std::ofstream file;

    file.open(nombreArachivo);

    for( int idx_in = 0; idx_in < len_in ; idx_in++ ){

        if(file)
            file << in[idx_in];
    }

}

void escribirArchivo(const char* in, const char* nombreArachivo, int len_in){

    std::ofstream file;

    file.open(nombreArachivo);

    for( int idx_in = 0; idx_in < len_in ; idx_in++ ){

        if(file)
            file << in[idx_in];
    }

}
