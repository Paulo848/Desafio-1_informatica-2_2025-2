#include <iostream>
#include <utilidades.h>
#include <files.h>
#include <cstring>


int main()
{
    int n_archivos;

    std :: cout << "Ingrese la cantidad de archivos a desencriptar y descomprimir : " << std :: endl;
    std :: cin >> n_archivos;

    for(int n = 1; n <= n_archivos; n++){

        int len_encrip = 0;
        char* encriptado = nullptr;
        int len_pist = 0;
        char* pista = nullptr;

        get_N_Encrip_Pista(encriptado, len_encrip, pista, len_pist, n);

        reinterpret_cast<unsigned char*>(encriptado);
        reinterpret_cast<unsigned char*>(pista);

        if(pista != nullptr) {

            for(int i = 0; i < len_pist; i++) std :: cout << static_cast<int>(pista[i]) ;

            std :: cout << std :: endl;
        }
        if(encriptado != nullptr) {

            for(int i = 0; i < len_encrip; i++) std :: cout << static_cast<int>(encriptado[i]) ;

            std :: cout << std :: endl;
        }

        std :: cout << "final " << n << ".........................................................................." << std :: endl;

    }

    std :: cout << "final ..." << std :: endl;

    return 0;

}
