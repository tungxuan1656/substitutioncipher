#include <stdio.h>
#include <stdlib.h>

#include "variables.h"
#include "main.h"
#include "menu.h"
#include "encryption.h"
#include "decryption.h"
#include "setupkey.h"

char Decryption_Monoalphabetic(char kytu, char *key)
{
    INHOA
    // dùng bảng truy ngược
    if (kytu >= 'A' && kytu <= 'Z') kytu = key[kytu - 'A'];
    return kytu;
}

char Decryption_Additive(char kytu, char *key)
{
    INHOA
    // có công thức truy hồi, nhưng thôi dùng bảng
    if (kytu >= 'A' && kytu <= 'Z') kytu = key[kytu - 'A'];
    return kytu;
}

char Decryption_Multiplicative(char kytu, char *key)
{
    INHOA
    // không có công thức truy ngược, dùng bảng
    if (kytu >= 'A' && kytu <= 'Z') kytu = key[kytu - 'A'];
    return kytu;
}

char Decryption_Afine(char kytu, char *key)
{
    INHOA
    // không có công thức truy ngược
    if (kytu >= 'A' && kytu <= 'Z') kytu = key[kytu - 'A'];
    return kytu;
}

char Decryption_Vigenere(char kytu, int p)
{
    INHOA
    // sử dụng công thức truy ngược
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu - 'A') - (Key_Vigenere[p] - 'A') + 26)%26 + 'A';
    return kytu;
}

char Decryption_OneTimePad(char kytu, char kytukey)
{
    INHOA
    // sử dụng công thức truy ngược
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu - 'A') - (kytukey - 'A') + 26)%26 + 'A';
    return kytu;
}



