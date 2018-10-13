#ifndef DEF_DECRYPTION
#define DEF_DECRYPTION

char Decryption_Monoalphabetic(char kytu, char *key);

char Decryption_Additive(char kytu, char *key);

char Decryption_Multiplicative(char kytu, char *key);

char Decryption_Afine(char kytu, char *key);

char Decryption_Vigenere(char kytu, int p);

char Decryption_OneTimePad(char kytu, char kytukey);

#endif


