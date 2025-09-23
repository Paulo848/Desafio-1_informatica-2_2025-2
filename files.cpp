#include "files.h"
#include "utilidades.h"
#include <fstream>
#include <iostream>

void get_N_Encrip_Pista (char*& encriptado, int &len_encrip, char*& pista, int &len_pist, int &N){

    leerArchivoEncriptado_N(encriptado, N, len_encrip);
    leerArchivoPista_N(pista, N, len_pist);

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

