#include "utilidades.h"
#include <iostream>

void comprimirRLE(const unsigned char* entrada, int len, unsigned char*& out, int& len_out)
{
    out = new unsigned char[2*len+1];

    len_out = 0;

    for (int i = 0; i < len; )
    {
        unsigned char actual = entrada[i];
        int count = 1;

        while (i + count < len && entrada[i + count] == actual) count++;

        out[len_out++] = static_cast<unsigned char>(count);
        out[len_out++] = actual;

        i += count;
    }

    out[len_out] = '\0';

}

void descomprimirRLE(const unsigned char* entrada, int len, unsigned char*& out, int& len_out){

    len_out = 0;

    for(int idx_ = 0; idx_ < len; idx_ += 2 )len_out += static_cast<int>(entrada[idx_]);

    out = new unsigned char[len_out];

    len_out++;

    int index_out = 0;

    for(int idx = 0; idx < len; idx += 2 ){

        unsigned char letter = entrada[idx + 1];
        int n_letters = (static_cast<int>(entrada[idx]));

        while(n_letters--) out[index_out++] = letter;

    }

    out[index_out] = '\0';

}

void comprimirLZ78(const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out){

    // comprobacion de entrada no nula
    if (!entrada || len_in <= 0) return;

    /*
     * declaracion de len_dic, que sera la longitud real variable del diccionario en cada iteracion
     * declaracion de len_max_dic, que sera la longitud maxima estimada del diccionario y por la cual aremos la reserva de memoria
     * declacarion y reserva de memoria para el diccionario
    */
    int len_dic = 0;
    int len_max_dic = len_in*3+1;
    unsigned char** dic = new unsigned char*[len_max_dic];

    int* dic_pos_ini = new int[len_max_dic];

    len_out = 0;
    int len_max_out = 3 * (len_in + 1);
    out = new unsigned char[len_max_out];

    /*
     * se inician los valores base para la compresion:
     * la primera posicion del diccionario es el valor nulo, si longitud es 0 y no almacena ningun caracter
     * se le asigna la longitud a el valor nuelo igual a cero
     * se declara el prefijo inicial para cualquier cadena que va ser el valor nulo
    */
    dic[len_dic] = new unsigned char[2];
    set_len(dic[len_dic],0);
    dic_pos_ini[0] = 0;

    ++len_dic;
    unsigned char* prefijo = dic[0];

    /*
     * se recorren todos los caracteres de la entrada con un for
     * en el proceso se van hallando las cadenas y almacenandolas en el diccionario
    */
    for(int idx = 0; idx < len_in; idx++)
    {

        unsigned char actual = entrada[idx];
        bool found = false;
        int indx_found = -1;

        int len_prefi = len_of(prefijo);
        int len_nxt_str = len_prefi + 1;

        for(int i= 0  ;(i < len_dic)  &&  (!found);  i++){

            unsigned char* str_ac = dic[i];
            int len_string = len_of(str_ac);

            if (len_string == len_nxt_str ){

                int cont = 0;

                while( cont < len_prefi && str_ac[cont+2] == prefijo[cont+2] )  ++cont;

                if (cont == len_prefi && str_ac[cont+2] == actual) {   found = true; indx_found = i; }

            }
        }

        if (found){ prefijo = dic[indx_found];  continue;  }

        int idx_pref = 0;

        bool found_pref = false;
        for ( int j = 0; j < len_dic && !found_pref; ++j)  if (dic[j] == prefijo) { idx_pref = j; found_pref = true; }

        int n = dic_pos_ini[idx_pref];
        unsigned char c1 ;
        unsigned char c2 ;
        convert_int_doble_char ( n , &c1, &c2);
        out[len_out++] = c1;
        out[len_out++] = c2;
        out[len_out++] = actual;

        //std :: cout << dic_pos_ini[idx_pref] << ":" << (char)actual << "|";

        if(len_dic < len_max_dic){

            int start = (idx - len_prefi) + 1;
            dic_pos_ini[len_dic] = start;

            dic[len_dic] = new unsigned char[len_nxt_str+2];
            set_len(dic[len_dic],len_nxt_str);
            for(int k = 0 ; k < len_prefi;  k++)  dic[len_dic][k+2] = prefijo[k+2];
            dic[len_dic][len_prefi+2] = actual;

            len_dic++;
            prefijo = dic[0];
        }
    }

    if (len_of(prefijo) > 0)
    {
        int idx_pref = 0;
        for (int j = 0; j < len_dic; ++j) {
            if (dic[j] == prefijo) { idx_pref = j; break; }
        }

        int n = dic_pos_ini[idx_pref];
        unsigned char c1, c2;
        convert_int_doble_char(n, &c1, &c2);

        unsigned char eof = 0;

        out[len_out++] = c1;
        out[len_out++] = c2;
        out[len_out++] = eof;

        // Para debug: imprimir tanto índice como carácter
        // std::cout << dic_pos_ini[idx_pref] << ":" << (char)entrada[len_in - 1] << "|";
    }

    // cout << endl;


    for(int k_ = 0; k_ < len_dic ; k_++){

        int large = len_of(dic[k_]);

        std :: cout << dic_pos_ini[k_] << "-" << k_ << " : ";

        for(int i_ = 0; i_ < large; i_++ ){
             std :: cout << dic[k_][i_+2];
        }

        std :: cout << std :: endl;

    }




    for(int ixd = 0; ixd < len_dic; ixd++)delete[] dic[ixd];

    std :: cout << "longitud dic : " << len_dic << "-";
    delete[] dic;
    delete[] dic_pos_ini;

}

void descomprimirLZ78(const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out){

    int idx_dic = -1;
    int len_dic = (len_in/3)+1;
    unsigned char ** dic_rec = new unsigned char*[len_dic];

    int* dic_pos_ini = new int[len_dic];

    dic_rec[++idx_dic] = new unsigned char[2];
    set_len(dic_rec[idx_dic],0);
    dic_pos_ini[0] = 0;

    int posic_string = 0;
    int sum_strings = 0;

    for(int idx = 0; idx < len_in ; idx+=3){

        int pocision = (int)((entrada[idx] << 8) | entrada[idx+1]);
        unsigned char carct = entrada[idx+2];

        int aux_idx_dic = -1;
        for(int i = 0; i < idx_dic+1; i++) { if(dic_pos_ini[i] == pocision) aux_idx_dic = i; }

        //std :: cout << " aux id dic : " << aux_idx_dic << std :: endl;
        unsigned char* prefijo = dic_rec[aux_idx_dic];

        int len_pref = len_of(prefijo);
        int len_nxt = len_pref+1;
        int inx_string = 2;


        sum_strings += len_nxt;

        dic_rec[++idx_dic] = new unsigned char[len_nxt+2];

        set_len(dic_rec[idx_dic], len_nxt);

        //std :: cout << "bandera -----------------len pref : " << len_pref << " len of dic idx : " << len_of(dic_rec[idx_dic]) << std :: endl;

        for( int idx_pre = 0; idx_pre < len_pref; idx_pre++ ) dic_rec[idx_dic][inx_string++] = prefijo[idx_pre+2]; //std :: cout << "entramos al  pref";}
        dic_rec[idx_dic][inx_string] = carct;

        //std :: cout << dic_rec[idx_dic][]

        dic_pos_ini[idx_dic] = sum_strings-len_pref;

    }

    sum_strings--;

    // std :: cout << "idx dic : " << idx_dic << "- " << std :: endl;


    for(int k_ = 0; k_ < idx_dic+1 ; k_++){

        int large = len_of(dic_rec[k_]);

        std :: cout << dic_pos_ini[k_] << "-" << k_ << " : ";

        for(int i_ = 0; i_ < large; i_++ ){
            std :: cout << dic_rec[k_][i_+2];
        }

        std :: cout << std :: endl;

    }

    // std :: cout << "la suma es = " << sum_strings << std :: endl;

    len_out = sum_strings;
    int idx_out = -1;
    out = new unsigned char[sum_strings];

    for (int idx_in = 0; idx_in < len_in; idx_in+=3){

        int pocision = (int)((entrada[idx_in] << 8) | entrada[idx_in+1]);
        unsigned char carct = entrada[idx_in+2];

        int aux_idx_dic = -1;
        for(int i = 0; i < idx_dic+1; i++) { if(dic_pos_ini[i] == pocision) aux_idx_dic = i; }

        unsigned char* prefijo = dic_rec[aux_idx_dic];

        int len_pref = len_of(prefijo);

        for( int idx_pre = 0; idx_pre < len_pref; idx_pre++ ) out[++idx_out] = prefijo[idx_pre+2]; //std :: cout << "entramos al  pref";}
        out[++idx_out] = carct;

    }

    for(int ixd = 0; ixd < len_dic; ixd++)delete[] dic_rec[ixd];

    delete[] dic_rec;
    delete[] dic_pos_ini;

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

static inline int len_of(const unsigned char* p) {
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
