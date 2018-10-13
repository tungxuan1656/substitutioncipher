#ifndef DEF_ENCRYPTION
#define DEF_ENCRYPTION

#define INHOA ChuyenInHoa(&kytu);

void ChuyenInHoa(char *kytu);

char Encryption_Monoalphabetic(char kytu);

char Encryption_Additive(char kytu);

char Encryption_Multiplicative(char kytu);

char Encryption_Afine(char kytu);

char Encryption_Vigenere(char kytu, int p);

char Encryption_OneTimePad(char kytu, FILE *file_key);

#endif


