#include "../inc/libmx.h" 

char* mx_nbr_to_hex(unsigned long nbr) {

    int maxDigits = 0;
    unsigned long temp = nbr;
    while (temp > 0) {
        maxDigits++;
        temp /= 16;
    }

    char* hexString = (char*)malloc((maxDigits + 1) * 1);
    if (hexString == NULL) {
        return NULL;
    }

    int i = maxDigits - 1;
    while (nbr > 0) {
        unsigned long remainder = nbr % 16;
        if (remainder < 10) {
            hexString[i] = '0' + remainder;
        } else {
            hexString[i] = 'a' + (remainder - 10);
        }
        nbr /= 16;
        i--;
    }

    hexString[maxDigits] = '\0';
    return hexString;
}
