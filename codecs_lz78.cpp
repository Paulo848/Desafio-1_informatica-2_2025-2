#include "codecs_lz78.h"
#include "utils.h"   // imprimible()

void descomprimirLZ78(const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out){

    if (len_in % 3 != 0 || entrada == nullptr || len_in == 0) { out = nullptr; len_out = 0; return; }

    int idx_dic = -1;
    int len_dic = (len_in/3)+1;
    unsigned char ** dic_rec = new unsigned char*[len_dic];



    dic_rec[++idx_dic] = new unsigned char[2];
    set_len(dic_rec[idx_dic],0);

    int sum_strings = 0;

    bool input_valid = true;

    for(int idx = 0; idx < len_in && input_valid ; idx+=3){


        int posicion = (int)((entrada[idx] << 8) | entrada[idx+1]);
        unsigned char carct = entrada[idx+2];

        if(!imprimible(carct) || posicion > idx_dic){  input_valid = false; continue; }

        unsigned char* prefijo = dic_rec[posicion];

        int len_pref = len_of(prefijo);

        int len_nxt = len_pref+1;
        int inx_string = 2;

        sum_strings += len_nxt;

        dic_rec[++idx_dic] = new unsigned char[len_nxt+2];

        set_len(dic_rec[idx_dic], len_nxt);



        for( int idx_pre = 0; idx_pre < len_pref; idx_pre++ ) dic_rec[idx_dic][inx_string++] = prefijo[idx_pre+2]; //std :: cout << "entramos al  pref";}
        dic_rec[idx_dic][inx_string] = carct;



    }

    if(!input_valid){
        out = nullptr;
        len_out = 0;
        for(int i = 0; i < idx_dic+1; i++ ) delete[] dic_rec[i];
        delete[] dic_rec;
        return;
    }

    len_out = sum_strings;
    int idx_out = -1;
    out = new unsigned char[sum_strings];

    for (int idx_in = 0; idx_in < len_in; idx_in+=3){

        int posicion = (int)((entrada[idx_in] << 8) | entrada[idx_in+1]);
        unsigned char carct = entrada[idx_in+2];


        unsigned char* prefijo = dic_rec[posicion];

        int len_pref = len_of(prefijo);

        for( int idx_pre = 0; idx_pre < len_pref; idx_pre++ ) out[++idx_out] = prefijo[idx_pre+2]; //std :: cout << "entramos al  pref";}
        out[++idx_out] = carct;

    }

    for (int ixd = 0; ixd <= idx_dic; ++ixd)  // o ixd < idx_dic+1
        delete[] dic_rec[ixd];
    delete[] dic_rec;

}

static inline int len_of(const unsigned char* p) {
    return (int)((p[0] << 8) | p[1]);
}

static inline void convert_int_doble_char (int n, unsigned char* c1, unsigned char* c2)
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

static inline void set_len(unsigned char* p, int LT) {
    unsigned char hi, lo;
    convert_int_doble_char(LT, &hi, &lo);
    p[0] = hi; p[1] = lo;
}
