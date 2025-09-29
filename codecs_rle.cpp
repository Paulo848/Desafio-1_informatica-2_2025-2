#include "codecs_rle.h"
#include "utils.h"   // imprimible()

void descomprimirRLE(const unsigned char* entrada, int len_in, unsigned char*& out, int& len_out){

    if (len_in % 3 != 0 || entrada == nullptr || len_in == 0) { out = nullptr; len_out = 0; return; }

    len_out = 0;
    bool input_valid = true;
    for(int idx_ = 0; idx_ < len_in && input_valid; idx_ += 3 ){
        unsigned char carct = entrada[idx_+2];
        len_out += static_cast<int>(entrada[idx_+1]);
        if(!imprimible(carct))input_valid = false;
    }

    if(!input_valid){
        out = nullptr;
        len_out = 0;
        return;
    }

    out = new unsigned char[len_out];

    int index_out = -1;
    for(int idx = 0; idx < len_in; idx += 3 ){

        unsigned char letter = entrada[idx + 2];
        int n_letters = (static_cast<int>(entrada[idx+1]));

        while(n_letters-- && (index_out+1) < len_out) out[++index_out] = letter;

    }

}

