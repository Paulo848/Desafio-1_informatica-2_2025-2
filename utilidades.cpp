#include "utilidades.h"
#include <iostream>

int comprimirRLE(const char* entrada, int len, char* out, int* len_out)
{

    int k = 0;

    for (int i = 0; i < len; )
    {
        char actual = entrada[i];
        int count = 1;

        while (i + count < len && entrada[i + count] == actual) count++;

        int larg_count;
        char* buffer = int_to_arr(count, &larg_count);

        if(k+larg_count > len){
            //cout << "i = " << i << " k = " << k << " learg_co = " << larg_cont << " len = " << len;
            delete[] buffer;
            return 1;
        }

        for (int j = 0; j < larg_count; j++) out[k++] = buffer[j];

        delete[] buffer;

        out[k++] = actual;

        i += count;
    }

    *len_out = k;

    return 0;

}

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

void comprimirLZ78(const unsigned char* entrada, int len_in){

    if (!entrada || len_in <= 0) return;

    int len_clv = 0;
    unsigned char* prefijo;

    unsigned char** clave = new unsigned char*[len_in*3+1];

    int* pos_ini = new int[len_in*3+1];
    pos_ini[0] = 0;

    clave[len_clv] = new unsigned char[2];

    set_len(clave[len_clv],0);

    ++len_clv;

    prefijo = clave[0];

    for(int i = 0; i < len_in; i++)
    {

        unsigned char actual = entrada[i];

        bool find = false;

        int len = len_(prefijo);

        int len_n = len + 1;

        int indx_found = -1;

        for(int aux = 0; (aux < len_clv) && (!find); aux++)
        {

            unsigned char* str_ac = clave[aux];

            int len_string = len_(str_ac);

            if (len_string >= len_n){

                int cont = 0;

                while( cont < len && str_ac[cont+2] == prefijo[cont+2] )++cont;

                if (cont == len && str_ac[cont+2] == actual) {   find = true; indx_found = aux; }

            }
        }

        if (find){ prefijo = clave[indx_found];  continue;  }

        int start = (i - len) + 1;
        pos_ini[len_clv] = start;

        int idx_pref = 0;

        for (int j = 0; j < len_clv; ++j)
        {
            if (clave[j] == prefijo) { idx_pref = j; break; }
        }

        // cout << pos_ini[idx_pref] << ":" << (char)actual << "|";


        clave[len_clv] = new unsigned char[len_n+2];

        set_len(clave[len_clv],len_n);

        for(int k = 0; k<len; k++){
            clave[len_clv][k+2] = prefijo[k+2];
        }
        clave[len_clv][len+2] = actual;

        prefijo = clave[0];

        len_clv++;

    }

    if (len_(prefijo) > 0)
    {
        int idx_pref = 0;
        for (int j = 0; j < len_clv; ++j) { if (clave[j] == prefijo) { idx_pref = j; break; } }

        // cout << pos_ini[idx_pref];

    }

    // cout << endl;

    for(int k_ = 0; k_ < len_clv ; k_++){

        int large = len_(clave[k_]);

        // cout << pos_ini[k_] << "-" << k_ << " : ";

        for(int i_ = 0; i_ < large; i_++ ){
            // cout << clave[k_][i_+2];
        }

        // cout << endl;

    }



    for(int ixd = 0; ixd < len_clv; ixd++)delete[] clave[ixd];

    delete[] clave;

}


void convert_int_doble_char (int n, unsigned char* c1, unsigned char* c2)
{
    *c1 = 0x00;
    *c2 = 0x00;

    int count = 0;
    while (n > 0)
    {
        int rest = n % 2;
        n /= 2;

        if (rest)
        {
            if (count < 8)
                *c2 |= (unsigned char)(0x1 << count);    // byte bajo
            else
                *c1 |= (unsigned char)(0x1 << (count - 8)); // byte alto
        }
        count++;
    }
}

static inline int len_(const unsigned char* p) {
    return (int)((p[0] << 8) | p[1]);
}

static inline void set_len(unsigned char* p, int LT) {
    unsigned char hi, lo;
    convert_int_doble_char(LT, &hi, &lo);
    p[0] = hi; p[1] = lo;
}


void rotar_derecha(unsigned char* in, int bits, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = (in[i] >> bits) | (in[i] << (8 - bits));
    }
}

void rotar_izquierda(unsigned char* in, int bits, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = (in[i] << bits) | (in[i] >> (8 - bits));
    }
}

void aplicar_xor(unsigned char* in, unsigned char mask, unsigned char* out, int size) {
    for (int i = 0; i < size; ++i)
    {
        out[i] = in[i] ^ mask;
    }
}
