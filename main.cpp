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

        if(pista != nullptr) {

            for(int i = 0; i < len_pist; i++) std :: cout << static_cast<int>(pista[i]) ;

            std :: cout << std :: endl;
        }
        if(encriptado != nullptr) {

            for(int i = 0; i < len_encrip; i++) std :: cout << static_cast<char>(encriptado[i]) ;

            std :: cout << "longitud input : " << len_encrip << "-";

            std :: cout << std :: endl;
        }

        std :: cout << "final " << n << ".........................................................................." << std :: endl;

        int len_compri_rle = 0;
        unsigned char* compri_rle = nullptr;
        comprimirRLE( encriptado, len_encrip, compri_rle, len_compri_rle);
        for(int index = 0; index < len_compri_rle; index +=2){ std :: cout << static_cast<int>(compri_rle[index]); std :: cout << static_cast<char>(compri_rle[index+1]); }

        std :: cout << std :: endl << "Desencriptador : " << std :: endl;

        int len_descom_rle = 0;
        unsigned char* descom_rle = nullptr;
        descomprimirRLE( compri_rle, len_compri_rle, descom_rle, len_descom_rle );
        for(int idxasda = 0; idxasda < len_descom_rle; idxasda++) std :: cout << static_cast<char>(descom_rle[idxasda]);
        std :: cout << std :: endl;

        int len_compro_lz = 0;
        unsigned char* compro_lz = nullptr;
        comprimirLZ78(encriptado, len_encrip, compro_lz, len_compro_lz);
        for(int idxpar = 0; idxpar < len_compro_lz; idxpar += 3){
            std :: cout << (int)((compro_lz[idxpar] << 8) | compro_lz[idxpar+1]);
            std :: cout << static_cast<char>(compro_lz[idxpar+2]);
        }

        std :: cout << "longitud lz : " << len_compro_lz;

        std :: cout << std :: endl;

        unsigned char* descom_lz = nullptr;
        int len_descom_lz = 0;
        descomprimirLZ78(compro_lz, len_compro_lz, descom_lz, len_descom_lz);
        for(int i = 0; i < len_descom_lz; i++) std :: cout << static_cast<char>(descom_lz[i]) ;


    }

    std :: cout << "final ..." << std :: endl;

    return 0;

}
