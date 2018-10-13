#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variables.h"
#include "main.h"
#include "menu.h"
#include "encryption.h"
#include "decryption.h"
#include "setupkey.h"

void LoadKey()
{
    FILE *file_key = fopen("key.txt", "r");

    if (file_key == NULL) {
        printf("Khong tim thay file key. Hay kiem tra lai.\n");
        system("pause");
        exit(1);
    }

    fscanf(file_key, "%s\n%d\n%d\n%s", Key_Monoalphabetic, &Key_Additive, &Key_Multiplicative, Key_Vigenere);

//    int i;
//    for (i=0; i<26; i++) if(Key_Monoalphabetic[i]>='a' && Key_Monoalphabetic[i]<='z') Key_Monoalphabetic[i]+='A' - 'a';
//    for (i=0; i<strlen(Key_Vigenere); i++) if(Key_Vigenere[i]>='a' && Key_Vigenere[i]<='z') Key_Vigenere[i]+='A' - 'a';
    fclose(file_key);

}

void SaveKey()
{
    FILE *file_key = fopen("key.txt", "w");
    rewind(file_key);

    if (file_key == NULL) {
        printf("Khong tim thay file key. Hay kiem tra lai.\n");
        system("pause");
        exit(1);
    }
    fprintf(file_key, "%s\n%d\n%d\n%s", Key_Monoalphabetic, Key_Additive, Key_Multiplicative, Key_Vigenere);

    fclose(file_key);
}

void CaiDatKey(int loaima)
{
    switch(loaima) {
        // monoalphabetic
        case 1: SetKey_Monoalphabetic();
                SaveKey();
            break;
        // additive
        case 2: SetKey_Additive();
                SaveKey();
            break;
        // multiplicative
        case 3: SetKey_Multiplicative();
                SaveKey();
            break;
        // afine
        case 4: printf("\nKey Afine Cipher la ket hop cua Key Additive va Multiplicative (Y = k*X+Z)\n\n");
            break;
        // vigenere
        case 5: SetKey_Vigenere();
                SaveKey();
            break;
        // one-time-pad
        case 6: printf("\nChinh sua Key One-Time-Pad Cipher trong file KeyOneTimePad.txt!");
            break;
    }
}

void SetKey_Monoalphabetic()
{
    char s[26];
    int a[26] = {0};
    int kiemtra;
    int i;
    do {
        kiemtra = 1;
        printf("\nMoi ban nhap vao chuoi gom 26 ky tu bang chu cai lien nhau viet in hoa:\n");
        scanf("%s", s);
        // chuyển thành IN HOA
        // đánh dấu ký tự đã xuất hiện
        for (i=0; i<26; i++) {
            if (s[i] >= 'a' && s[i] <= 'z') s[i] += 'A' - 'a';
            a[s[i] - 'A'] = 1;
        }
        // kiểm tra chữ nào chưa xuất hiện
        for (i=0; i<26; i++) {
            if (a[i]==0) {
                printf("Thieu chu cai %c.\n", 'A' + i);
                kiemtra = 0;
            }
        }
    } while (kiemtra==0);
    for (i=0; i<26; i++) Key_Monoalphabetic[i] = s[i]; // phù hợp thì gán
}

void SetKey_Additive()
{
    int temp = 0;
    do {
        printf("\nMoi ban nhap key Additive (mot so tu 1->25): ");
        scanf("%d", &temp);
    } while(temp<1 || temp>25); // key chỉ từ 1->25
    Key_Additive = temp;
}

void SetKey_Multiplicative()
{
    int k = 0;
    do {
        printf("\nMoi ban nhap key Additive (key thuoc {1,3,5,7,9,11,15,17,19,21,23,25}): ");
        scanf("%d", &k);
    }while(k!=1 && k!=3 && k!=5 && k!=7 && k!=9 && k!=11 && k!=15 && k!=17 && k!=19 && k!=21 && k!=23 && k!=25);
    // key phải nằm trong list trên
    Key_Multiplicative = k;
}

void SetKey_Vigenere()
{
    char a[1000]; // tối đa 1000 ký tự
    int kiemtra;
    int i=0;
    do {
        kiemtra=1;
        printf("\nMoi nhap key Vigenere (1 doan text lien nhau): ");
        scanf("%s", a);
        // kiểm tra xem có kí tự ngoài bảng chữ cái
        for (i=0; i< strlen(a); i++) {
            if (!(a[i]>='a' && a[i]<='z' || a[i]>='A' && a[i]<='Z')) kiemtra = 0;
        }
    } while (kiemtra==0); // không thể có ký tự khác ngoài ký tự trong bảng chữ cái
    // gán key
    for (i=0; i<strlen(a); i++){
        if (a[i]>='a' && a[i]<='z') a[i] += 'A'- 'a';
        Key_Vigenere[i] = a[i];
    }
    Key_Vigenere[i] = '\0';
}


