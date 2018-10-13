#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "variables.h"
#include "main.h"
#include "menu.h"
#include "encryption.h"
#include "decryption.h"
#include "setupkey.h"

int main()
{   // đặt giá trị cho các key
    srand(time(NULL)); // phục vụ cho rand() one-time-pad

    // load các key từ dưới file lên, trừ key one-time-pad
    LoadKey();

    // Lựa chọn hành động và loại mật mã
    LuaChon();

    // In ra lựa chọn của người dùng
    InRaLuaChon(hanhdong, loaima);

    // Xử lý hành động
    XuLy();

    return 0;
}

void LuaChon()
{
    do {
        system("cls");
        hanhdong = Menu1(); // chọn hành động
        system("cls");
        loaima = Menu2(); // chọn loại mật mã
    } while (loaima == 9); // 9 là khi quay lại chọn lại hành động.
}

void XuLy()
{
    // nếu hành động là cài đặt key
    if (hanhdong == 3) {
        CaiDatKey(loaima);
    }
    // nếu không
    else {
        // mở file input, output
        FILE *file_input = fopen("input.txt", "r");
        FILE *file_output = fopen("output.txt", "w+");
        // kiểm tra file
        if (file_input == NULL || file_output == NULL) {
            printf("Khong the doc duoc file. Hay kiem tra va thu lai!");
            system("pause");
            exit(1);
        }
        // in kết quả ra màn hình cùng lúc với việc xử lý
        printf("\nKet qua: \n\n");
        // xử lý plaintext trong file Input.txt trả về kết quả ra màn hình và file Output.txt
        XuLyText(file_input, file_output);

        printf("\n\nKet qua da duoc luu tai file output.txt!\n\n");
        printf("\nKey cua mat ma nam trong file key.txt\n");
        printf("Dong 1: key monoalphabetic\nDong 2: key additive\nDong 3: key multiplicative\nDong 4: key vigenere\n");
        printf("Key onetimepad trong file keyonetimepad.txt.\n\n");
        // đóng file
        fclose(file_output);
        fclose(file_input);
    }
}

void XuLyText(FILE *file_input, FILE *file_output)
{
    char kytubandau = fgetc(file_input), kytudaxuly; // ký tự đọc từ plaintext và ký tự được xử lý
    // mã hoá
    if(hanhdong == 1) {
        // Monoalphabetic Cipher
        if (loaima == 1) {
            while(kytubandau != EOF) {
                // ghi luôn vào file_output, từng ký tự
                kytudaxuly = Encryption_Monoalphabetic(kytubandau); // đã được qua hàm biến đổi

                // ghi vào file, in ra màn hình
                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                // từ tiếp theo
                kytubandau = fgetc(file_input);
            }
        }
        // Additive Cipher
        else if (loaima == 2) {
            while(kytubandau != EOF) {
                kytudaxuly = Encryption_Additive(kytubandau);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Multiplicative Cipher
        else if (loaima == 3) {
            while(kytubandau != EOF) {
                kytudaxuly = Encryption_Multiplicative(kytubandau);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Afine Cipher
        else if (loaima == 4) {
            while(kytubandau != EOF) {
                kytudaxuly = Encryption_Afine(kytubandau);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Vigenere Cipher
        else if (loaima == 5) {
            int chuky = strlen(Key_Vigenere), p=0;
            while(kytubandau != EOF) {
                // p là ký tự của key vigenere khi đến vị trí tương ứng
                kytudaxuly = Encryption_Vigenere(kytubandau, p);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
                p = (p+1)%chuky; // tăng p lên và quay lại nếu hết key
            }
        }
        // One-Time-Pad Cipher
        else {
            // file chứa key one-time-pad
            FILE *file_key = fopen("keyonetimepad.txt", "w+");
            if (file_key == NULL) {
                printf("Khong the mo file \"keyonetimepad.txt\". Hay kiem tra lai.\n");
                system("pause");
                exit(1);
            }
            while(kytubandau != EOF) { // truyền vào file_key để lưu lại key sau khi sinh ngẫu nhiên
                kytudaxuly = Encryption_OneTimePad(kytubandau, file_key);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
            fclose(file_key);
        }
    }
    // giải mã
    else if (hanhdong == 2) {
        char key[26];
        int i;
        // Monoalphabetic Cipher
        if (loaima == 1) {
                // mảng key truy ngược.
            for (i=0; i<26; i++) key[Encryption_Monoalphabetic(i+'A')-'A'] = i+'A';

            while(kytubandau != EOF) {
                // ghi luôn vào file_output, từng ký tự
                // truyền vào hàm truy ngược để giải mã cho hiệu suất
                kytudaxuly = Decryption_Monoalphabetic(kytubandau, key);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Additive Cipher
        else if (loaima == 2) {
                // cũng dùng mảng truy ngược
            for (i=0; i<26; i++) key[Encryption_Additive(i+'A')-'A'] = i+'A';

            while(kytubandau != EOF) {
                kytudaxuly = Decryption_Additive(kytubandau, key);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Multiplicative Cipher
        else if (loaima == 3) {
            // tạo bảng thay thế ngược
            for (i=0; i<26; i++) key[Encryption_Multiplicative(i+'A')-'A'] = i+'A';

            while(kytubandau != EOF) {
                kytudaxuly = Decryption_Multiplicative(kytubandau, key);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
            }
        }
        // Afine Cipher
        else if (loaima == 4) {
            // tạo bảng thay thế ngược.
            for (i=0; i<26; i++) key[Encryption_Afine(i+'A')-'A'] = i+'A';

            while(kytubandau != EOF) {
                kytudaxuly = Decryption_Afine(kytubandau, key);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);

            }
        }
        // Vigenere Cipher
        else if (loaima == 5) {
            int chuky = strlen(Key_Vigenere), p=0;

            while(kytubandau != EOF) {
                    // có công thức truy vấn ngược
                kytudaxuly = Decryption_Vigenere(kytubandau, p);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
                p = (p+1)%chuky;
            }
        }
        // One-Time-Pad Cipher
        else {
            FILE *file_key = fopen("keyonetimepad.txt", "r");
            char kytukey = fgetc(file_key);
            if (kytukey >='a' && kytukey<='z') kytukey += 'A'-'a';
            if (file_key == NULL) {
                printf("Khong the mo file \"keyonetimepad.txt\". Hay kiem tra lai.\n");
                system("pause");
                exit(1);
            }
            while(kytubandau != EOF && kytukey != EOF) {
                    // có công thức truy vấn ngược
                kytudaxuly = Decryption_OneTimePad(kytubandau, kytukey);

                fputc(kytudaxuly, file_output);
                printf("%c", kytudaxuly);

                kytubandau = fgetc(file_input);
                kytukey = fgetc(file_key);
                if (kytukey >='a' && kytukey<='z') kytukey += 'A'-'a';
            }
            fclose(file_key);
        }
    }
}


