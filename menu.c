#include <stdio.h>
#include <stdlib.h>

#include "variables.h"
#include "main.h"
#include "menu.h"
#include "encryption.h"
#include "decryption.h"
#include "setupkey.h"

// menu chọn hành động
int Menu1()
{
    printf("Menu:\n");
    printf("1. Tao mat ma\n");
    printf("2. Giai mat ma\n");
    printf("3. Cai dat khoa Key\n");
    printf("===================\n");
    printf("0. Thoat\n");

    int k;
    do {
        printf("Lua chon hanh dong: ");
        scanf("%d", &k);
        if (k==0) exit(1);
    } while (k>3 || k<0);
    // đảm bảo người dùng nhập đúng 1 trong những thao tác chương trình có thể thực hiện
    printf("\n");
    return k;
}

// menu chọn loại mật mã
int Menu2()
{
    printf("Menu:\n");
    printf("1. Monoalphabetic Cipher\n");
    printf("2. Additive Cipher\n");
    printf("3. Multiplicative Cipher\n");
    printf("4. Afine Cipher\n");
    printf("5. Vigenere Cipher\n");
    printf("6. Vernam Cipher\n");
    printf("===================\n");
    printf("0. Thoat\n");
    printf("9. Quay lai\n");

    int k;

    do {
        printf("Lua chon loai ma: ");
        scanf("%d", &k);
        if (k==0) exit(1);
    } while ((k>6 && k!=9) || k<0);
    // đảm bảo người dùng nhập đúng 1 trong những thao tác chương trình có thể thực hiện
    printf("\n");
    return k;
}

// In ra lựa chọn của người dùng đã chọn
void InRaLuaChon(int hanhdong, int loaima)
{
    system("cls");

    switch(hanhdong) {
        case 1: printf("Tao mat ma ");
            break;
        case 2: printf("Giai mat ma ");
            break;
        case 3: printf("Cai dat Key ");
            break;
    }

    switch(loaima) {
        case 1: printf("Monoalphabetic Cipher - Mat ma Mot Bang The.\n");
            break;
        case 2: printf("Additive Cipher - Mat ma Cong.\n");
            break;
        case 3: printf("Multiplicative Cipher - Mat ma Nhan.\n");
            break;
        case 4: printf("Afine Cipher - Mat ma ket hop Cong va Nhan.\n");
            break;
        case 5: printf("Vigenere Cipher - Mot truong hop cua Mat ma Da Bang The.\n");
            break;
        case 6: printf("Vernam Cipher - Mat ma One-Time-Pad dam bao bi mat tuyet doi.\n");
            break;
    }
}


