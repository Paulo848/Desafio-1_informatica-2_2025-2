#include "pipeline_desencriptar_descomprimir.h"  // prototipos propios
#include "codecs_rle.h"                          // descomprimirRLE
#include "codecs_lz78.h"                         // descomprimirLZ78
#include "crypto_xor_rot.h"                      // aplicar_xor, rotar_derecha, aplicar_xor_y_rotar
#include "utils.h"                               // print_arr, print_arr_LZ, imprimible (si lo usas)
#include "files.h"
#include <iostream>                              // std::cout en tus logs


int procesar_lote_archivos() {
    int n_archivos = 0;
    std::cout << "Ingrese la cantidad de archivos a desencriptar y descomprimir :\n";
    std::cin  >> n_archivos;

    for (int n = 1; n <= n_archivos; ++n) {

        int len_encrip = 0, len_pista = 0;
        unsigned char* encriptado = nullptr;
        unsigned char* pista      = nullptr;

        get_N_Encrip_Pista(encriptado, len_encrip, pista, len_pista, n);

        if(pista == nullptr || encriptado == nullptr) std :: cerr << "Fallo al leer el archivo : " << n << std :: endl; std :: cout << "................................... Lectura de archivo " << n << "..................................." << std :: endl;

        std::cout << "................................... Lectura de archivo " << n
                  << " ...................................\n";

        unsigned char* out = nullptr;
        int len_out = 0;

        char* metodo_comp = nullptr;
        unsigned char key = 0;
        int rot = 0;

        desencriptar_descomprimir(pista, len_pista,
                                  encriptado, len_encrip,
                                  out, len_out, n,
                                  metodo_comp, key, rot);

        if (out && len_out > 0) {
            escribir_cadena_original(out, n, len_out, metodo_comp, key, rot);

            delete[] out;
        } else {
            std::cerr << "Fallo al desencriptar/descomprimir archivo : " << n << "\n";
        }

        // liberar entradas leídas del dataset
        delete[] encriptado;
        delete[] pista;
    }

    std::cout << "................................... final ...................................\n";
    return 0;
}

void desencriptar_descomprimir(const unsigned char* pista, int len_pista,
                               const unsigned char* encriptado, int len_encrip,
                               unsigned char*& out, int& len_out, int n,
                               char*& metodo_compresion_out,
                               unsigned char& key_out, int& rot_out){

    /*
     * buscar las combinaciones de XOR, ROT,
     * verificar formato para descomprimir RLE y LZ78.
     * aplicar algoritmo de descompresion y aplicar algoritmo de busqueda para encontrar la pista
     */

    unsigned char key = 0x0;
    int rotl = 0;

    char* metodo_comp = nullptr;

    int index_pos;
    bool REL = false;
    bool LZ78 = false;

    encontrar_rot_y_key(encriptado, len_encrip, pista, len_pista, rotl, key, index_pos, REL,LZ78);

    unsigned char* desencriptado_xor = new unsigned char[len_encrip];
    aplicar_xor(encriptado,key,desencriptado_xor,len_encrip);
    unsigned char* desencriptado_rot = new unsigned char[len_encrip];
    rotar_derecha(desencriptado_xor,rotl,desencriptado_rot,len_encrip);

    delete[] desencriptado_xor;

    if(REL){

        metodo_comp = "RLE";

        std :: cout << "................................... Para el desencripatdo " << n << " : ................................... " << std :: endl;
        print_arr_LZ(desencriptado_rot,len_encrip);
        std :: cout << "................................... Para la descompresion " << n << " con impresion sin procesar y descompresion con RLE : ................................... " << std :: endl;

        unsigned char* descom = nullptr;
        int len_desc = 0;
        descomprimirRLE(desencriptado_rot,len_encrip, descom,len_desc);
        print_arr(descom, len_desc);

        if (!descom || len_desc <= 0) {
            out = nullptr;
            len_out = 0;
        } else {
            len_out = len_desc;
            out = descom;
            descom = nullptr;
        }

        std :: cout << std :: endl;
        std :: cout << std :: endl;
        std :: cout << std :: endl;
        std :: cout << std :: endl;
    }
    else if (LZ78){

        metodo_comp = "LZ78";

        std :: cout << "................................... Para el desencripatdo " << n << " : ................................... " << std :: endl;
        print_arr_LZ(desencriptado_rot,len_encrip);
        std :: cout << "................................... Para la descompresion " << n << " con impresion sin procesar y descompresion con LZ78 : ................................... " << std :: endl;

        unsigned char* descom = nullptr;
        int len_desc = 0;
        descomprimirLZ78(desencriptado_rot,len_encrip, descom,len_desc);
        print_arr(descom, len_desc);

        if (!descom || len_desc <= 0) {
            out = nullptr;
            len_out = 0;
        } else {
            len_out = len_desc;
            out = descom;
            descom = nullptr;
        }

        std :: cout << std :: endl;
        std :: cout << std :: endl;
        std :: cout << std :: endl;
        std :: cout << std :: endl;
    }
    else{
        std :: cout << "Fallo al desencriptar y descomprimir el archivo : " << n << std :: endl;
    }

    metodo_compresion_out = metodo_comp;
    key_out = key;
    rot_out = rotl;

    delete[] desencriptado_rot;

    std :: cout << std :: endl;
    std :: cout << std :: endl;
    std :: cout << std :: endl;
    std :: cout << std :: endl;


}


bool encontrar_rot_y_key(const unsigned char* encriptado, int len_encrip,
                         const unsigned char* pista, int len_pista,
                         int& rot_out, unsigned char& key_out, int& index_out,
                         bool &RLE, bool &LZ78) {
    unsigned char* buffer = new unsigned char[len_encrip];
    RLE = false;
    LZ78 = false;

    for (int ind = 0; ind < 256; ++ind){
        for (int rot = 0; rot < 8; ++rot) {


            unsigned char key = static_cast<unsigned char>(ind);
            aplicar_xor_y_rotar(encriptado, len_encrip, buffer, key, rot);


            int len_descomp_RLE;
            unsigned char* descomp_RLE = nullptr;

            descomprimirRLE(buffer,len_encrip, descomp_RLE,len_descomp_RLE);
            int pos = 0;
            if (descomp_RLE && len_descomp_RLE > 0 && buscar_patron(descomp_RLE, len_descomp_RLE, pista, len_pista, &pos)) {
                rot_out = rot;
                key_out = key;
                index_out = pos;
                RLE = true;
                delete[] buffer;
                delete[] descomp_RLE;
                return true;
            }
            delete[] descomp_RLE;

            int len_descm_LZ;
            unsigned char* descomp_LZ = nullptr;
            descomprimirLZ78(buffer,len_encrip,descomp_LZ,len_descm_LZ);
            if (descomp_LZ  && len_descm_LZ  > 0 && buscar_patron(descomp_LZ, len_descm_LZ, pista, len_pista, &pos)) {
                rot_out = rot;
                key_out = key;
                index_out = pos;
                LZ78 = true;
                delete[] buffer;
                delete[] descomp_LZ;
                return true;
            }
            delete[] descomp_LZ;

        }
    }
    delete[] buffer;
    return false;
}

