#include <iostream>
#include <utilidades.h>
#include <files.h>


int main()
{
    int n_archivos;

    std :: cout << "Ingrese la cantidad de archivos a desencriptar y descomprimir : " << std :: endl;
    std :: cin >> n_archivos;

    for(int n = 1; n <= n_archivos; n++){

        int len_encrip = 0;
        unsigned char* encriptado = nullptr;
        int len_pist = 0;
        unsigned char* pista = nullptr;

        get_N_Encrip_Pista(encriptado, len_encrip, pista, len_pist, n);

        //if(pista != nullptr) print_arr(pista,len_pist);
        //if(encriptado != nullptr) print_arr(encriptado,len_encrip);

        std :: cout << "................................... Lectura de archivo " << n << "..................................." << std :: endl;

        /*
        int len_compri_rle = 0;
        unsigned char* compri_rle = nullptr;
        comprimirRLE( encriptado, len_encrip, compri_rle, len_compri_rle);
        print_arr_RLE(compri_rle,len_compri_rle);

        int len_descom_rle = 0;
        unsigned char* descom_rle = nullptr;
        descomprimirRLE( compri_rle, len_compri_rle, descom_rle, len_descom_rle );
        print_arr(descom_rle,len_descom_rle);

        int len_compro_lz = 0;
        unsigned char* compro_lz = nullptr;
        comprimirLZ78(encriptado, len_encrip, compro_lz, len_compro_lz);
        print_arr_LZ(compro_lz,len_compro_lz);

        unsigned char* descom_lz = nullptr;
        int len_descom_lz = 0;
        descomprimirLZ78(compro_lz, len_compro_lz, descom_lz, len_descom_lz);
        print_arr(descom_lz,len_descom_lz);

        escribir_cadena_original(descom_lz, n, len_descom_lz);

        */

        unsigned char* out = nullptr;
        int len_out = -1;
        desencriptar_descomprimir(pista, len_pist , encriptado, len_encrip, out, len_out , n );

    }

    std :: cout << "................................... final ..................................." << std :: endl;

    return 0;

}
