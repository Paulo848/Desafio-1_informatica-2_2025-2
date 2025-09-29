#include "utils.h"
#include <iostream>

char* int_to_arr (const int n, int* len_out){

    char* out;

    int n_digits = 0;
    int aux = n;

    while(aux > 0){
        aux/=10;
        n_digits++;
    }

    if(n_digits > 0){

        out = new char[n_digits+1];

        int n_copy = n;
        for(int r = n_digits-1; r >= 0; r--){
            out[r] = '0'+(n_copy % 10);
            n_copy /= 10;
        }

        out[n_digits] = '\0';

    }else{
        out = new char[2];
        out[0] = '0';
        out[1] = '\0';
    }

    *len_out = n_digits;

    return out;

}

bool imprimible(unsigned char un_car){

    char car = static_cast<char>(un_car);
    if(car >= 'A' && car <= 'Z') return true;
    if(car >= 'a' && car <= 'z') return true;
    if(car >= '0' && car <= '9') return true;
    return false;
}

void print_arr(const unsigned char* in, int len){
    for(int i = 0;
         i < len; i++){
        if(imprimible(in[i]))std :: cout << static_cast<char>(in[i]);
        else std :: cout << "#";
    }
    std :: cout << std :: endl;
}

void print_arr_RLE(const unsigned char* in, int len){
    for(int i = 0; i < len; i+=2){
        std :: cout << static_cast<int>(in[i]);
        if(imprimible(in[i+1]))std :: cout << static_cast<char>(in[i+1]);
        else std :: cout << "#";
    }
    std :: cout << std :: endl;
}
void print_arr_LZ(const unsigned char* in, int len){
    for(int i = 0; i < len; i += 3){
        std :: cout << (int)((in[i] << 8) | in[i+1]);
        if(imprimible(in[i+2]))std :: cout << static_cast<char>(in[i+2]);
        else std :: cout << "#";
    }
    std :: cout << std :: endl;
}

bool buscar_patron(const unsigned char* text, int n,
                   const unsigned char* pista,  int m,
                   int* pos_out){

    if (!text || !pista || n <= 0 || m <= 0 || m > n) return false;

    for (int s = 0; s <= n - m; ++s) {

        int i = 0;
        while (i < m && text[s + i] == pista[i]) ++i;

        if (i == m) {  *pos_out = s;  return true;  }
    }
    return false;
}
