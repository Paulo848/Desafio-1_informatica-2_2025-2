#include <iostream>
#include <utilidades.h>

using namespace std;

int main()
{

    const unsigned char entrada[] = "quisierayoqueestelibrofueraelmashermoso";
    int len_in = (int)sizeof(entrada) - 1;

    comprimirLZ78(entrada, len_in);

    cout << '\n';
    return 0;

}
