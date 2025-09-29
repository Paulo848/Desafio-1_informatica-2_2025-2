#ifndef CODECS_RLE_H
#define CODECS_RLE_H

void descomprimirRLE(const unsigned char* entrada, int len_in,
                     unsigned char*& out, int& len_out);

#endif // CODECS_RLE_H
