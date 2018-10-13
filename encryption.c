#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "variables.h"
#include "main.h"
#include "menu.h"
#include "encryption.h"
#include "decryption.h"
#include "setupkey.h"


#define INHOA ChuyenInHoa(&kytu);

void ChuyenInHoa(char *kytu) {
    if (*kytu >= 'a' && *kytu <= 'z') *kytu+= 'A' - 'a';
}

char Encryption_Monoalphabetic(char kytu)
{
    INHOA
    // tra bảng
    if (kytu >= 'A' && kytu <= 'Z') kytu = Key_Monoalphabetic[kytu-'A'];
    return kytu;
}

char Encryption_Additive(char kytu)
{
    INHOA
    // cộng thêm, lấy dư
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu-'A') + Key_Additive)%26 + 'A';
    return kytu;
}

char Encryption_Multiplicative(char kytu)
{
    INHOA
    // nhân lên, lấy dư
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu - 'A')*Key_Multiplicative)%26 + 'A';
    return kytu;
}

char Encryption_Afine(char kytu)
{   // không cần INHOA vì đã gọi hàm kia rồi.
    // kết hợp của 2 hàm.
    kytu = Encryption_Additive(Encryption_Multiplicative(kytu));
    return kytu;
}

char Encryption_Vigenere(char kytu, int p)
{
    INHOA
    // cộng thêm 1 lượng là key_vegenere[p]
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu - 'A') + (Key_Vigenere[p] - 'A'))%26 + 'A';
    return kytu;
}

char Encryption_OneTimePad(char kytu, FILE *file_key)
{
    INHOA
    const int MAX = 25, MIN = 0;
    // tạo key random
    char random = (rand()%(MAX - MIN + 1) + MIN);
    // cộng thêm ký random
    if (kytu >= 'A' && kytu <= 'Z') kytu = ((kytu-'A') + random)%26 + 'A';
    // lưu lại key
    fputc((random + 'A'), file_key);
    return kytu;
}


